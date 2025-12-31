const express = require('express');
const mongoose = require('mongoose');
const bodyparser = require('body-parser');
const path = require('path');

const app = express();
app.use(bodyparser.urlencoded({extended : false}));

mongoose.connect("mongodb://127.0.0.1:27017/studentDB");

const schema= mongoose.Schema({
    name:String,
    email:String,
    date:Date,
    phone:String,
    password:String,
});

const student = mongoose.model("student",schema);

app.get("/",(req,res)=>
{
    res.sendFile(__dirname+"/index.html");
})

app.post("/add",async (req,res)=>{
    const data={
        name:req.body.name,
        email:req.body.email,
        date:req.body.dob,
        phone:req.body.phone,
        password:req.body.password,
    };
    await student.insertOne(data);
    res.sendFile(__dirname+"/index.html");
})

app.post("/update",async (req,res)=>{
    await student.updateOne({name : req.body.name},
        {$set: {
            email:req.body.email,
            date:req.body.dob,
            phone:req.body.phone,
            password:req.body.password,
        }}
    )
    res.sendFile(__dirname+"/index.html");
})

app.post("/delete",async(req,res)=>{
    await student.deleteOne({name:req.body.name});
    res.sendFile(__dirname+"/index.html");
})

app.get("/display",async(req,res)=>{
    const data = await student.find();
    res.json(data);
})

app.listen(5000,()=>{
    console.log("http://127.0.0.1:5000");
})