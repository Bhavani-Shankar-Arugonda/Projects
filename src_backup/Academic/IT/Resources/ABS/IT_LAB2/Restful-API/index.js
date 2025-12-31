var express=require('express');
var app= express();
var fs=require('fs');
app.use(express.json());
app.use(express.static('/home/kali/Documents/ABS/IT_LAB/todolist'));


app.get('/',(req,res)=>{
    // fs.readFile(__dirname+"/"+"users.json",'utf8',(err,data)=>{
    //     var users=JSON.parse(data);
    //     var user=users["user"+req.params.id]
    //     res.sendFile(__dirname+'/'+"users.json");
    //     // res.end(JSON.stringify(user));
    // });
    var filepath="/home/kali/Documents/ABS/IT_LAB/todolist/todolist.html";
    res.sendFile(filepath);
})



/*app.post("/",(req,res)=>{
    fs.readFile(__dirname+"/"+"users.json",'utf8',(err,data)=>{
        var users=JSON.parse(data);
        
        res.end(JSON.stringify(users));
    });
})*/
// app.post('/', function (req, res) {
//     fs.readFile( __dirname + "/" + "users.json", 'utf8', function (err, data) {
//     var users = JSON.parse( data );
//     var user = {
//         name: "Aneesh",
//         profession: "Engineer",
//         age: 26
//     };
//     users["user"+4] = user;
//     fs.writeFile(__dirname+'/'+"users.json",JSON.stringify(users),"utf8",(err)=>{});
//     console.log(JSON.stringify(users));
//     res.end(JSON.stringify(users));
//     });
//     })

// app.delete('/:id',(req,res)=>{
//     fs.readFile(__dirname+'/'+'users.json','utf8',function(err,data){
//         data=JSON.parse(data);
//         var id="user"+req.params.id;
//         var user=data[id];
//         delete data[id];
//         fs.writeFile(__dirname+'/'+"users.json",JSON.stringify(data),"utf8",(err)=>{});
//         res.end(JSON.stringify(data));
//     });
// })



var server = app.listen(5000, function () {
    console.log("Express App running at http://127.0.0.1:5000/");
    })