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
*/

var express = require('express');
var path = require('path');
var app = express();
var port = 8080;

//Getiing css file
app.use('/views/css',express.static(__dirname + '/views/css'));


//Getting html file
app.get('/',function(req,resp)
{
  resp.sendFile('index.html', {root: path.join(__dirname, './views')});
})

//bootstrap usage?
//app.use('/views/css', express.static(__dirname + '/node_modules/bootstrap/dist/css'));

//Listening on port
app.listen(port,function()
{
  console.log('Listening at port ' + port);
})
