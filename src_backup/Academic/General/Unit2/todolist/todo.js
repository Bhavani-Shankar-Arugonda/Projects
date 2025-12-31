let lastlist[];
let completed[];
let due[];

document.getElementById("add").addEventListener("click",function(){
    let taksList=getElementById("tasklist");
    let taskInput=getElementById("task");
    let taskValue=taskInput.value.trim();

    if(taskValue==="")
    {
        alert("Please enter a task");
    }

    let li=document.createElement("li");
    li.textContent=taskValue;

    lastlist.push(taskValue);

    let completeButton  =document.createElement("button");
    completeButton.textContent="Done";
    completeBtn.onclick = function () {
        complete(taskValue, li);

    taksList.tex
});

function complete(task, li) {
    completed.push(task);
    li.style.textDecoration = "line-through";
}

function Due(task, li) {
    due.push(task);
    li.style.color = "red";
}