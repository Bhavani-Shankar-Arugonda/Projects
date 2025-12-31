const express = require('express');
const mongoose = require('mongoose');
const bodyParser= require ('body-parser');
const path=require('path');
const app = express();
app.use(bodyParser.urlencoded({extended : flase}));

mongoose.connect("mongodb:/127.0.0.1:27017/productsDB");

const schema = new mongoose.schema({
    PID:String,
    name:String,
    product_pic: String,
    product_type:String,
    manufacturing_year: String,
});

const product = mongoose.model("prosuct",schema);

app.get("/",(req,res)=>{
    res.sendFile(__dirname+"/index.html");
})

app.post("/add",async (req,res)=>{
    await product.insertOne({
        PID: req.body.PID, 
        name: req.body.name, 
        product_pic: req.body.product_pic, 
        product_type: req.body.product_type, 
        manufacturing_year: req.body.manufacturing_year
    });
    res.sendFile(path.join(__dirname, "/index.html"));
})

app.post("/update",async(req,res)=>{
    
})