# Realtime Chat (Socket.IO)

## Overview
A backend service for a real-time chat application built with **Node.js**, **Express**, and **Socket.IO**. It supports real-time messaging, rooms, and MongoDB integration.

## Features
- **Real-Time Communication**: Powered by Socket.IO.
- **Room Support**: Users can join specific chat and broadcast messages.
- **Scalable Architecture**: usage of `http` server wrapper for WebSocket support.

## Dependencies
- `express`: Web framework.
- `socket.io`: Real-time engine.
- `mongoose`: MongoDB object modeling (setup required).
- `dotenv`: Environment variable management.

## Setup
1. **Install Dependencies**:
   ```bash
   npm install
   ```
2. **Environment**:
   Create a `.env` file (optional for basic run):
   ```env
   PORT=5000
   MONGO_URI=mongodb://localhost:27017/chat_app
   ```
3. **Start Server**:
   ```bash
   node index.js
   ```
