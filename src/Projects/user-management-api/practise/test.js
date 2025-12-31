const express = require("express");
const mongoose = require("mongoose");
const path = require("path");
const app = express();
const bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));

mongoose.connect("mongodb://127.0.0.1:27017/productDB");

const productSchema = new mongoose.Schema({
    PID: String,
    name: String,
    product_pic: String,
    product_type:String,
    manufacturing_year: String,
});

const Product = mongoose.model("Product", productSchema);

app.get('/', (req, res) => {
    res.sendFile(__dirname + "/index.html");
});

app.post('/add', async (req, res) => {
    await Product.insertOne({ 
        PID: req.body.PID, 
        name: req.body.name, 
        product_pic: req.body.product_pic, 
        product_type: req.body.product_type, 
        manufacturing_year: req.body.manufacturing_year
    });
    res.sendFile(path.join(__dirname, "/index.html"));
});

app.post('/delete', async (req, res) => {
    await Product.deleteOne({ PID: req.body.PID });
    res.sendFile(path.join(__dirname, "/index.html"));
});

app.post("/update", async (req, res) => {
    await Product.updateOne({ PID: req.body.PID }, { 
        $set: {
            name: req.body.name,
            product_pic: req.body.product_pic,
            product_type: req.body.product_type,
            manufacturing_year: req.body.manufacturing_year
        }
    });
    res.sendFile(__dirname + "/index.html");
});

app.get("/show", async (req, res) => {
    const data = await Product.find();
    res.json(data);
});

app.listen(3004, () => {
    console.log("http://127.0.0.1:3004/");
});