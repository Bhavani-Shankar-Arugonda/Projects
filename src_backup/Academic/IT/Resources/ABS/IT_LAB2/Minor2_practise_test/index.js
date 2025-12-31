const { json } = require('body-parser');
const express=require('express');
const mongoose=require('mongoose');
const app=express();
app.use(express.json());
app.use(express.urlencoded({extended:true}));
app.use(express.static(__dirname));

mongoose.connect('mongodb://localhost:27017/quotes')
.then(() => console.log('MongoDB connected'))
.catch(err => console.error(err));

const schema= new mongoose.Schema({
    name:String,
    quote:String,   
});

const quote=mongoose.model('quote',schema);

app.get('/add', async (req, res) => {
    try {
        const q = req.query;
        const newquote = new quote(q);
        await newquote.save();
        const allQuotes = await quote.find(); // Fetch all quotes
        res.send(RenderQuotesPage(allQuotes)); // Pass resolved quotes to RenderQuotesPage
    } catch (err) {
        res.status(500).send(err.message);
    }
});

app.post('/replace', async (req, res) => {
    try {
        const qt = req.body;
        await quote.findOneAndUpdate({}, qt, { new: true });
        const allQuotes = await quote.find(); // Fetch all quotes
        res.send(RenderQuotesPage(allQuotes)); // Pass resolved quotes to RenderQuotesPage
    } catch (err) {
        res.status(500).send(err.message);
    }
});

app.get('/delete', async (req, res) => {
    try {
        await quote.findOneAndDelete({ __v: 0 });
        const allQuotes = await quote.find(); // Fetch all quotes
        res.send(RenderQuotesPage(allQuotes)); // Pass resolved quotes to RenderQuotesPage
    } catch (err) {
        res.status(500).send(err.message);
    }
});

app.get('/', async (req, res) => {
    const allQuotes = await quote.find(); // Fetch all quotes from the database
    res.send(RenderQuotesPage(allQuotes)); // Render the quotes page
});


function RenderQuotesPage(quotes) {
    const quoteshtml=quotes
    .map((quote)=>`<p>${quote.name}:${quote.quote}</p>`)
    .join('');
    return`
    <!DOCTYPE html>
    <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <title>node&express</title>
            <link rel="stylesheet" href="style.css">
        </head>
    </html>

    <body>
        <div class="top"><h1>May Node and Express be with you.</h1></div>

        <div class="container">
            <div class="box">
                <h1>Add Quote</h1>
                <form action="/add" id="addquote" method="get">
                    <input type="text" name="name" placeholder="name" >
                    <input type="text" name="quote" placeholder="quote" >
                    <button type="submit">Submit</button>
                </form>
            </div>

            <div class="box">
                <h1>Replace</h1>
                <h2>Replace first quote.</h2>
                <form action="/replace" id="replace" method="post">
                    <input type="text" name="name" placeholder="name" >
                    <input type="text" name="quote" placeholder="quote" >
                    <button type="submit">Replace quote</button>
                </form>
            </div>

            <div class="box">
                <h3>Remove</h3>
                <h2>Delete one quote.</h2>
                <form action="/delete" id="delete" method="get">
                    <button>Delete quote</button>
                </form>
            </div>

        </div>

        <div class="quotes">
            <h1>Quotes</h1>
            <div id="display">${quoteshtml}</div>
        </div>
    </body>
    `;
}

app.listen(5000,()=>{
    console.log("Port is running at port 5000");
});