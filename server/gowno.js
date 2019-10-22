const express = require('express');
const path = require('path');
const app = express();

const views = path.join(__dirname, '/views'); // parsuje sciezke do pliku, views jest sciezka
console.log(views); 

app.use(express.static('views'));

app.get('/', (req, res) => { // slash "/" sciezką do localhosta
    res.sendFile(path.join(views, 'index.html'));
})

app.get('/led_controller', (req, res) => {
    res.sendFile(path.join(views, 'led_controller.html'));
})

app.get('/test', (req, res) => {
    res.sendFile(path.join(views, 'website.html'));
})

app.listen(80, () => {
    console.log('http://localhost');
})