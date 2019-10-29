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

/*
var http = require('http');
var fs   = require('fs');
var express = require('express');
var app = express();
app.use('/static', express.static('static'))

http.createServer(function (req, res) {
    fs.readFile('index.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data);
    res.end();
  });
}).listen(8080);


For node express usage (in project folder - cmd)

npm install express --save

For bootstrap usage

npm install --save bootstrap
*/

var express = require('express');
var path = require('path');
var app = express();
var port = 8080;

//Getiing css file
//app.use('/views/css',express.static(__dirname + '/views/css'));
app.use(express.static(path.join(__dirname, 'views')));




//Getting html file
app.get('/', function(req, resp) {
    resp.sendFile('index.html', { root: path.join(__dirname, './views') });
})

//bootstrap usage?
//app.use('/views/css', express.static(__dirname + '/node_modules/bootstrap/dist/css'));

//Listening on port
//opening on phone/laptop - 192.168.1.61:3000 - device ipv4 address
app.listen(3000, '192.168.1.61' || 'localhost', function() {
    console.log('Application worker ' + process.pid + ' started...');
});