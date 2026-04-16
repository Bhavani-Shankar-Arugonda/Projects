import { useState, useEffect, useRef } from "react"

const API = "http://localhost:8000"

export default function App() {
  const [sessionId, setSessionId] = useState(null)
  const [messages, setMessages]   = useState([])
  const [input, setInput]         = useState("")
  const [streaming, setStreaming] = useState(false)
  const [uploadStatus, setUploadStatus] = useState("")
  const bottomRef = useRef(null)

  // Get a session on first load
  useEffect(() => {
    fetch(`${API}/session`)
      .then(r => r.json())
      .then(d => setSessionId(d.session_id))
  }, [])

  // Auto-scroll to bottom
  useEffect(() => {
    bottomRef.current?.scrollIntoView({ behavior: "smooth" })
  }, [messages])

  const sendMessage = async () => {
    if (!input.trim() || streaming) return
    const userMsg = input.trim()
    setInput("")
    setMessages(prev => [...prev, { role: "user", text: userMsg }])
    setStreaming(true)

    // Add empty assistant bubble to fill in
    setMessages(prev => [...prev, { role: "assistant", text: "" }])

    const res = await fetch(`${API}/chat`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ session_id: sessionId, message: userMsg }),
    })

    const reader = res.body.getReader()
    const decoder = new TextDecoder()

    while (true) {
      const { done, value } = await reader.read()
      if (done) break
      const chunk = decoder.decode(value)
      const lines = chunk.split("\n")
      for (const line of lines) {
        if (!line.startsWith("data: ")) continue
        const token = line.replace("data: ", "")
        if (token === "[DONE]") break
        // Append token to last assistant message
        setMessages(prev => {
          const updated = [...prev]
          updated[updated.length - 1] = {
            ...updated[updated.length - 1],
            text: updated[updated.length - 1].text + token,
          }
          return updated
        })
      }
    }
    setStreaming(false)
  }

  const uploadFile = async (e) => {
    const file = e.target.files[0]
    if (!file) return
    setUploadStatus("Uploading...")
    const form = new FormData()
    form.append("file", file)
    const res = await fetch(`${API}/upload`, { method: "POST", body: form })
    const data = await res.json()
    setUploadStatus(`Done — ${data.chunks_added} chunks indexed`)
    setTimeout(() => setUploadStatus(""), 3000)
  }

  return (
    <div style={{ maxWidth: 700, margin: "0 auto", padding: "20px",
                  fontFamily: "system-ui", height: "100vh",
                  display: "flex", flexDirection: "column" }}>

      {/* Header */}
      <div style={{ display: "flex", justifyContent: "space-between",
                    alignItems: "center", marginBottom: 16 }}>
        <h2 style={{ margin: 0, fontSize: 18 }}>My Chatbot</h2>
        <label style={{ cursor: "pointer", fontSize: 13,
                        padding: "6px 12px", border: "1px solid #ddd",
                        borderRadius: 8, background: "#f9f9f9" }}>
          {uploadStatus || "Upload doc (PDF/TXT)"}
          <input type="file" accept=".pdf,.txt"
                 onChange={uploadFile} style={{ display: "none" }} />
        </label>
      </div>

      {/* Messages */}
      <div style={{ flex: 1, overflowY: "auto", display: "flex",
                    flexDirection: "column", gap: 12, paddingBottom: 8 }}>
        {messages.map((m, i) => (
          <div key={i} style={{
            alignSelf: m.role === "user" ? "flex-end" : "flex-start",
            background: m.role === "user" ? "#7F77DD" : "#f0f0f0",
            color: m.role === "user" ? "#fff" : "#111",
            padding: "10px 14px", borderRadius: 12,
            maxWidth: "75%", fontSize: 14, lineHeight: 1.6,
            whiteSpace: "pre-wrap",
          }}>
            {m.text}
            {m.role === "assistant" && streaming &&
             i === messages.length - 1 && (
              <span style={{ opacity: 0.5 }}>▋</span>
            )}
          </div>
        ))}
        <div ref={bottomRef} />
      </div>

      {/* Input */}
      <div style={{ display: "flex", gap: 8, marginTop: 12 }}>
        <input
          value={input}
          onChange={e => setInput(e.target.value)}
          onKeyDown={e => e.key === "Enter" && sendMessage()}
          placeholder="Type a message..."
          style={{ flex: 1, padding: "10px 14px", borderRadius: 10,
                   border: "1px solid #ddd", fontSize: 14, outline: "none" }}
        />
        <button onClick={sendMessage} disabled={streaming}
          style={{ padding: "10px 20px", borderRadius: 10, border: "none",
                   background: streaming ? "#ccc" : "#7F77DD",
                   color: "#fff", cursor: streaming ? "default" : "pointer",
                   fontSize: 14, fontWeight: 500 }}>
          {streaming ? "..." : "Send"}
        </button>
      </div>
    </div>
  )
}