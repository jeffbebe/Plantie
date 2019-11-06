/*
For node express usage (in project folder - cmd)

npm install express --save

For bootstrap usage

npm install --save bootstrap
*/

var express = require("express");
var path = require("path");
var mysql = require("mysql");
var app = express();
var Sequelize = require("sequelize");
var port = 3000;

// connecting to our database
var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "asder12345",
  database: "mydb"
});
// connecting via sequelize, sqlite file is required
const sequelize = new Sequelize({
  dialect: "sqlite",
  storage: "/database/baza.sqlite"
});

con.connect(function(err) {
  if (err) console.log("not Connected!"); //throw err;
  // console.log("Connected!");
  // that makes our new database
  /*  con.query("CREATE DATABASE mydb", function (err, result) {    
        if (err) throw err;
        console.log("Database created");
      }); */
});

// creating a new table, can be outside the con.connect
/*   var sql = "CREATE TABLE customers (name VARCHAR(255), address VARCHAR(255))";
  con.query(sql, function (err, result) {
    if (err) throw err;
    console.log("Table created");
  }); */

//Getting css file
//app.use('/views/css',express.static(__dirname + '/views/css'));
app.use(express.static(path.join(__dirname, "views")));

// used to parse request body
app.use(express.json());

//Getting html file
app.get("/", function(req, resp) {
  resp.sendFile("index.html", { root: path.join(__dirname, "./views") });
});

//make defined actions after a POST on /control website
app.post("/control", (req, res) => {
  let action = req.body.action; // let is sth like var
  console.log(action);
  /* var sql = "INSERT INTO requests (Water, Fertilise) VALUES ('1', '1')";
  con.query(sql, function(err, result) {
    if (err) throw err;
    console.log("Records inserted");
  }); */
});

//bootstrap usage?
//app.use('/views/css', express.static(__dirname + '/node_modules/bootstrap/dist/css'));

//Listening on port
//opening on phone/laptop - 192.168.1.61:3000 - device ipv4 address
app.listen(3000, "localhost", function() {
  console.log("Application worker " + process.pid + " started...");
});
