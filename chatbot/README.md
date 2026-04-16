# RAG-Powered AI Chatbot

A full-stack conversational AI application built with **FastAPI** and **React** that supports multi-turn memory, real-time streaming, document-aware answers via RAG, and a configurable system persona — powered by the **Google Gemini 2.0 Flash** API (free tier).

---

## Features

- **Multi-turn conversation memory** — maintains full session history per user so the model remembers context across the conversation
- **Real-time token streaming** — responses stream token-by-token over Server-Sent Events (SSE) for an instant, responsive feel
- **RAG (Retrieval-Augmented Generation)** — upload PDF or TXT files; the chatbot chunks, embeds, and retrieves relevant content to ground answers in your documents
- **System prompt / persona** — a configurable instruction injected at inference time defines the assistant's personality and behaviour
- **REST API with CORS** — clean endpoints for session management, chat, and document upload

---

## Tech Stack

| Layer       | Technology                                   |
| ----------- | -------------------------------------------- |
| Backend     | Python, FastAPI, Uvicorn                     |
| Frontend    | React, Vite                                  |
| LLM         | Google Gemini 2.0 Flash (`google-genai`)   |
| Vector DB   | ChromaDB                                     |
| Embeddings  | sentence-transformers (`all-MiniLM-L6-v2`) |
| PDF parsing | pypdf                                        |
| Streaming   | Server-Sent Events (SSE)                     |

---

## Project Structure

```
chatbot/
├── backend/
│   ├── main.py          # FastAPI app — all routes and logic
│   ├── .env             # API key (not committed)
│   └── requirements.txt
└── frontend/
    ├── src/
    │   └── App.jsx      # Chat UI, streaming reader, file upload
    ├── index.html
    └── package.json
```

---

## Getting Started

### Prerequisites

- Python 3.9+
- Node.js 18+
- A free Gemini API key from [aistudio.google.com](https://aistudio.google.com)

---

### Backend Setup

```bash
cd chatbot/backend

# Create and activate virtual environment
python -m venv venv
source venv/bin/activate        # Windows: venv\Scripts\activate

# Install dependencies
pip install fastapi uvicorn google-genai chromadb pypdf \
            sentence-transformers python-dotenv
```

Create a `.env` file in the `backend/` directory:

```
GEMINI_API_KEY=AIza_your_key_here
```

Start the server:

```bash
uvicorn main:app --reload
```

The API will be available at `http://localhost:8000`.

---

### Frontend Setup

```bash
cd chatbot/frontend

npm install
npm run dev
```

The app will be available at `http://localhost:5173`.

---

## API Endpoints

| Method   | Endpoint     | Description                                                |
| -------- | ------------ | ---------------------------------------------------------- |
| `GET`  | `/session` | Creates a new session, returns a UUID                      |
| `POST` | `/chat`    | Accepts `session_id` + `message`, streams SSE response |
| `POST` | `/upload`  | Accepts a PDF or TXT file, chunks and indexes it           |

### Example chat request

```bash
curl -X POST http://localhost:8000/chat \
  -H "Content-Type: application/json" \
  -d '{"session_id": "your-uuid", "message": "Hello!"}'
```

### Example upload request

```bash
curl -X POST http://localhost:8000/upload \
  -F "file=@document.pdf"
```

---

## How RAG Works in This Project

1. User uploads a PDF or TXT file via the frontend
2. Backend extracts text and splits it into 500-character chunks (with 50-char overlap)
3. Each chunk is embedded using `all-MiniLM-L6-v2` and stored in ChromaDB
4. On every chat message, the top 3 most semantically similar chunks are retrieved
5. Retrieved chunks are appended to the user's message as context before being sent to Gemini
6. Gemini answers using both the conversation history and the retrieved document context

---

## How Streaming Works

FastAPI returns a `StreamingResponse` with `media_type="text/event-stream"`. Each token from Gemini is yielded as an SSE frame (`data: <token>\n\n`). The React frontend reads the stream using the Fetch API's `ReadableStream`, decodes each chunk, and appends tokens to the last message bubble in real time. A `[DONE]` sentinel signals the end of the stream.

---

## Configuration

You can modify the following in `main.py`:

| Variable              | Default              | Description                          |
| --------------------- | -------------------- | ------------------------------------ |
| `MODEL`             | `gemini-2.0-flash` | Gemini model name                    |
| `SYSTEM_PROMPT`     | Helpful assistant    | Assistant persona and instructions   |
| `size` (chunk size) | `500`              | Characters per document chunk        |
| `overlap`           | `50`               | Overlap between chunks               |
| History trim          | `20`               | Max turns kept in memory per session |

---

## Limitations & Future Improvements

- **Session persistence** — sessions are stored in-memory and reset on server restart; a production version would use Redis or a database
- **Authentication** — no auth layer; all sessions are currently accessible by session ID
- **Persistent vector store** — ChromaDB is in-memory; replacing with pgvector or a hosted Chroma instance would make document indexes permanent
- **Evaluation** — no quality metrics on answers; tools like LangSmith or Braintrust would be the next step
- **Error handling** — basic error handling; a production app would need retry logic, rate limit handling, and user-facing error messages

---

## License

MIT
