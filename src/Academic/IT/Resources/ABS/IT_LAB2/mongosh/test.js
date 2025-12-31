const express = require("express");
const mongoose = require("mongoose");
const bodyParser = require("body-parser");

const app = express();
app.use(bodyParser.json());

mongoose.connect("mongodb://localhost:27017/todoDB", {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

const db = mongoose.connection;
db.on("error", console.error.bind(console, "Connection error:"));
db.once("open", () => console.log("Connected to MongoDB"));

// Define Schema
const todoSchema = new mongoose.Schema({
  task: String,
  completed: Boolean,
});

// Register Model Correctly
const Todo = mongoose.model("Todo", todoSchema); // ✅ FIXED

// Create a new Todo (POST)
app.post("/todos", async (req, res) => {
  try {
    const todo = new Todo(req.body);
    await todo.save();
    res.status(201).send(todo);
  } catch (err) {
    res.status(400).send(err);
  }
});

// Get all Todos (GET)
app.get("/todos", async (req, res) => {
  try {
    const todos = await Todo.find();
    res.status(200).json(todos);
  } catch (err) {
    res.status(400).send(err);
  }
});

// Delete a Todo (DELETE)
app.delete("/todos/:id", async (req, res) => {
  try {
    await Todo.findByIdAndDelete(req.params.id);
    res.status(204).send();
  } catch (err) { // ✅ FIXED
    res.status(500).send(err);
  }
});

// Start Server
app.listen(3000, () => console.log("Server running on port 3000"));
