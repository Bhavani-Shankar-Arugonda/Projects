# User Management API

## Overview
A robust Express.js REST API designed to manage user data, serving as the backend for the `todo-frontend-vanilla` application.

## Features
- **Static File Serving**: Serves the frontend application from `../todo-frontend-vanilla`.
- **User Management**: 
  - `GET /users`: Retrieve a list of all users.
  - `POST /users`: Create and store new user profiles.
- **Persistence**: Uses a local JSON-based data store (`users.json`).

## Setup
1. **Install Dependencies**:
   ```bash
   npm install
   ```
2. **Start Server**:
   ```bash
   node index.js
   ```
3. **Access Application**:
   Open [http://localhost:5000](http://localhost:5000) to view the integrated application.

## Architecture
- `index.js`: Main server entry point using Express middleware.
- `users.json`: Lightweight JSON database for user persistence.
