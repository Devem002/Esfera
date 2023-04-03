import express from "express";
const app = express();
const port = process.env.PORT || 80;
app.set('port',process.env.PORT || 80);
app.set('json spaces', 2);
app.get('/movements', (req, res) => {    
    res.json(
        {
            "Movements": "[ADL]"
        }
    );
});
//app.get('/', (req, res) => {
//res.send('Hello World!');
//});
app.listen(port, () => {
console.log(`Example app listening at http://localhost:${port}`);
});
