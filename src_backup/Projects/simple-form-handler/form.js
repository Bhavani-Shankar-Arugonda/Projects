const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = process.env.PORT || 5000;
const DATA_FILE = path.join(__dirname, 'data.json');

// Middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.static(__dirname)); // Serve static files like CSS

/**
 * GET /
 * Serve the main form.
 */
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'index.html'));
});

/**
 * POST /submit
 * Handle form submission and save to JSON.
 */
app.post('/submit', (req, res) => {
    // Construct safe response object
    const formData = {
        name: req.body.name || "Anonymous",
        address: req.body.Address || "Not Provided",
        gender: req.body.gender || "Not Specified",
        languages: [
            req.body.Telugu,
            req.body.English,
            req.body.Hindi,
            req.body.Other
        ].filter(Boolean).join(', ') || "None",
        otherLanguage: req.body.otherLanguage || "None",
        city: req.body.city || "Not Selected",
        phone: req.body.phone || "Not Provided",
        email: req.body.email || "Not Provided",
        submittedAt: new Date().toISOString()
    };

    console.log("Received Form Data:", formData);

    // Save to file
    fs.writeFile(DATA_FILE, JSON.stringify(formData, null, 2), (err) => {
        if (err) {
            console.error("Error writing to data.json:", err);
            return res.status(500).json({
                status: 'error',
                message: "Internal Server Error"
            });
        }
        res.json({
            status: 'success',
            data: formData
        });
    });
});

// Start Server
app.listen(PORT, () => {
    console.log(`Server running at http://127.0.0.1:${PORT}/`);
});
