/*var http = require('http');
var fs = require('fs');

http.createServer(function (req, res) {
    fs.readFile('index.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'}); // adding http header,  200 is status code and means everything is ok
    res.write('Version 1.0.0'); // write a response to the client
    res.write('Hello World!'); // write a response to the client
    res.end(); // end the response
    })
}).listen(8080); // the server object listens on port 8080
*/


const express = require('express');
const path = require('path');
const app = express();

const views = path.join(__dirname, '/views'); // parsuje sciezke do pliku, views jest sciezka
//console.log(views); 

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

app.listen(8085, () => {
    console.log('http://localhost');
})