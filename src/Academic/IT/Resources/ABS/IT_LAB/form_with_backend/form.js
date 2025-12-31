var express = require('express');
var app = express();
var fs = require('fs');
app.use(express.urlencoded({ extended: true })); // Use urlencoded for form data

app.get('/', (req, res) => {
    res.sendFile(__dirname + "/Form.html");
});

app.post('/submit', (req, res) => { // Changed to app.post
    var response = {
        name: req.body.name,
        address: req.body.Address,
        gender: req.body.gender || "Not specified", // Corrected to use 'gender'
        languages: [
            req.body.Telugu,
            req.body.English,
            req.body.Hindi,
            req.body.Other
        ].filter(Boolean).join(', ') || "None", // Improved language handling
        otherLanguage: req.body.otherLanguage || "None", // Corrected to otherLanguage
        city: req.body.city || "Not selected",
        phone: req.body.phone || "Not provided",
        email: req.body.email || "Not provided"
    };

    console.log("Received Data:", response);
    fs.writeFile(__dirname + '/data.json', JSON.stringify(response, null, 2), (err) => { // Added formatting for readability
        if (err) {
            console.error("Error writing to data.json:", err);
            return res.status(500).send("Internal Server Error"); // Send error response
        }
        res.json(response);
    });
});

app.listen(5000, () => {
    console.log(`Server running at http://127.0.0.1:5000/`);
});
