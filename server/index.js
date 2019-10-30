/*
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
app.listen(3000, '157.158.201.193' || 'localhost', function() {
    console.log('Application worker ' + process.pid + ' started...');
});