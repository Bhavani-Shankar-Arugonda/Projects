const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 5000;

// Middleware
app.use(express.json());

// Serve static files from the associated ToDoList project or local public folder
// Adjusted to point to the relative location of the moved ToDoList project
const todoListPath = path.join(__dirname, '../todo-frontend-vanilla');
app.use(express.static(todoListPath));

/**
 * GET /
 * Serves the main ToDoList HTML file.
 */
app.get('/', (req, res) => {
    const filePath = path.join(todoListPath, 'todolist.html');
    res.sendFile(filePath, (err) => {
        if (err) {
            console.error('Error serving file:', err);
            res.status(500).send('Error loading application');
        }
    });
});

/**
 * GET /users
 * Returns list of users from local JSON file.
 */
app.get('/users', (req, res) => {
    fs.readFile(path.join(__dirname, 'users.json'), 'utf8', (err, data) => {
        if (err) {
            console.error(err);
            return res.status(500).json({ error: 'Failed to read data' });
        }
        res.json(JSON.parse(data));
    });
});

/**
 * POST /users
 * Adds a new user.
 */
app.post('/users', (req, res) => {
    fs.readFile(path.join(__dirname, 'users.json'), 'utf8', (err, data) => {
        if (err) {
            return res.status(500).json({ error: 'Failed to read data' });
        }

        let users;
        try {
            users = JSON.parse(data);
        } catch (e) {
            users = {};
        }

        // Example user object - in a real app, this would come from req.body
        const newUser = {
            name: req.body.name || "Anonymous",
            profession: req.body.profession || "Unknown",
            age: req.body.age || 0,
            id: Date.now()
        };

        // Simple ID generation for demo
        users[`user${newUser.id}`] = newUser;

        fs.writeFile(path.join(__dirname, 'users.json'), JSON.stringify(users, null, 4), 'utf8', (err) => {
            if (err) return res.status(500).json({ error: 'Failed to save data' });
            res.json(users);
        });
    });
});

// Start server
app.listen(PORT, () => {
    console.log(`Server running at http://127.0.0.1:${PORT}/`);
});