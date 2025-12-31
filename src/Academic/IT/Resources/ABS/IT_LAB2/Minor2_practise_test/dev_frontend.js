// document.getElementById("one").addEventListener("submit",(event)=>{
//     event.preventDefault();
// })
await fetch("http://127.0.0.1:3000/",{
    method : "POST",
    headers : {
        'Content-Type' : 'application/json'
    },
    body : JSON.stringify({name,quote})
});
await ShowQuotes()
async function ShowQuotes(){
    const response =  await fetch("http://127.0.0.1:3000/");
    const data = await response.json();
    var e = document.getElementById("q");
    data.forEach(element => {
        const p = document.createElement("p");
        p.textContent = `${element.name}: ${element.quote}`;
        e.appendChild(p);
    });
}

