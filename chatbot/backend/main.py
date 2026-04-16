import os, uuid, io
from fastapi import FastAPI, UploadFile, File
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import StreamingResponse
from pydantic import BaseModel
from dotenv import load_dotenv
import google.generativeai as genai
import chromadb
from chromadb.utils import embedding_functions
import pypdf

load_dotenv()

# ── SETUP ─────────────────────────────────────────────────────
app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:5173"],
    allow_methods=["*"],
    allow_headers=["*"],
)

genai.configure(api_key=os.getenv("GEMINI_API_KEY"))
model = genai.GenerativeModel(
    model_name="gemini-2.5-flash",
    system_instruction="""You are a helpful, friendly AI assistant.
When answering, if relevant context from uploaded documents is provided,
use it to give accurate answers. Always be concise and clear."""
)

# ── SESSION STORE ──────────────────────────────────────────────
sessions: dict = {}   # session_id -> list of {"role", "parts"}

# ── VECTOR DB (RAG) ────────────────────────────────────────────
chroma_client = chromadb.Client()
ef = embedding_functions.SentenceTransformerEmbeddingFunction(
    model_name="all-MiniLM-L6-v2"
)
collection = chroma_client.get_or_create_collection(
    name="docs", embedding_function=ef
)


# ── NEW SESSION ────────────────────────────────────────────────
@app.get("/session")
def new_session():
    sid = str(uuid.uuid4())
    sessions[sid] = []
    return {"session_id": sid}


# ── CHAT (streaming SSE) ───────────────────────────────────────
class ChatRequest(BaseModel):
    session_id: str
    message: str

@app.post("/chat")
async def chat(req: ChatRequest):
    history = sessions.get(req.session_id)
    if history is None:
        from fastapi import HTTPException
        raise HTTPException(status_code=400, detail="Invalid session")

    # RAG: retrieve relevant chunks
    rag_context = ""
    if collection.count() > 0:
        results = collection.query(query_texts=[req.message], n_results=3)
        chunks = results["documents"][0]
        if chunks:
            rag_context = "\n\nRelevant context from uploaded documents:\n"
            rag_context += "\n---\n".join(chunks)

    user_content = req.message + rag_context

    # Append user turn — Gemini uses "model" not "assistant"
    history.append({"role": "user", "parts": [user_content]})
    if len(history) > 20:
        history = history[-20:]
    sessions[req.session_id] = history

    def stream_response():
        full_reply = ""

        # Pass all turns except the latest as history,
        # then send the latest as the new message
        chat_session = model.start_chat(history=history[:-1])
        response = chat_session.send_message(user_content, stream=True)

        for chunk in response:
            token = chunk.text or ""
            if token:
                full_reply += token
                safe = token.replace("\n", "\\n")
                yield f"data: {safe}\n\n"

        sessions[req.session_id].append(
            {"role": "model", "parts": [full_reply]}
        )
        yield "data: [DONE]\n\n"

    return StreamingResponse(
        stream_response(),
        media_type="text/event-stream",
        headers={"Cache-Control": "no-cache", "X-Accel-Buffering": "no"},
    )


# ── UPLOAD (RAG ingestion) ─────────────────────────────────────
@app.post("/upload")
async def upload(file: UploadFile = File(...)):
    content = await file.read()

    if file.filename.endswith(".pdf"):
        reader = pypdf.PdfReader(io.BytesIO(content))
        text = " ".join(page.extract_text() for page in reader.pages)
    else:
        text = content.decode("utf-8")

    chunks, size, overlap = [], 500, 50
    for i in range(0, len(text), size - overlap):
        chunk = text[i : i + size].strip()
        if chunk:
            chunks.append(chunk)

    ids = [str(uuid.uuid4()) for _ in chunks]
    collection.add(documents=chunks, ids=ids)

    return {"status": "ok", "chunks_added": len(chunks)}