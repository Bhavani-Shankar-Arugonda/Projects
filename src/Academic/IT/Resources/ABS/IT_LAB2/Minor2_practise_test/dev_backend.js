const express = require('express');
const app = express();
app.use(express.json());
app.use(express.urlencoded({ extended : true}));

const mongoose = require('mongoose');
mongoose.connect("mongodb://127.0.0.1:27017/newdatabase")
.then(() => console.log("Succesfully Connected to Mongoshell"))
.catch(err => console.log("Error in connecting to mongoshell" + err));
   const quoteSchema = new mongoose.Schema({
      name : { type : String , required : true },
      quote : { type : String , required : true}
   });
   const NewUser = mongoose.model("User",quoteSchema);
app.post("/",async (req,res)=>{
    const user = new NewUser(req.body);
    await user.save();
    // const User = await NewUser.find();
    // res.json(User);
});
app.post("/Replace",async (req,res)=>{
    var students = await NewUser.findOneAndUpdate({__v : 0},{ $set : {quote : "Replaced Text"}});
    res.json(students);
})
app.get("/Remove",async (req,res) =>{
    var students = await NewUser.deleteOne({__v : 0});
    res.json(students);
});
app.listen(3000,()=>{ console.log("HI!!");
})
