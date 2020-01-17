var express = require("express");
var path = require("path");
var http = require("http");
var app = express();
var Sequelize = require("sequelize");
var port = 3000;
var bodyParser = require("body-parser");

var moment = require("moment");
moment().format();

const server = http.createServer(app); //create a server

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

const WebSocket = require("ws");
const wsServer = new WebSocket.Server({ server });

// connecting via sequelize, sqlite file is required
const sequelize = new Sequelize({
  dialect: "sqlite",
  storage: "database/baza.sqlite",
  define: {
    timestamps: false,
    id: false
  }
});

const Model = Sequelize.Model;
const Op = Sequelize.Op; // used in "and", "or" operations
class Sensor_readings extends Model {}
Sensor_readings.init(
  {
    // attributes
    ID: {
      type: Sequelize.INTEGER,
      allowNull: false
    },
    Soil_Moisture: {
      type: Sequelize.INTEGER,
      allowNull: false
    },
    Air_Temperature: {
      type: Sequelize.INTEGER,
      allowNull: false
    },
    Brightness_Level: {
      type: Sequelize.INTEGER,
      allowNull: false
    },
    Water_Tank_Level: {
      type: Sequelize.INTEGER,
      allowNull: false
    },
    Air_Humidity: {
      type: Sequelize.INTEGER,
      allowNull: false
    },
    Date: {
      type: Sequelize.INTEGER,
      allowNull: false
    }
  },
  {
    sequelize // inherits from sequelize class
    //modelName: 'Sensor_readings'
    // options
  }
);

//Getting css file
//app.use('/views/css',express.static(__dirname + '/views/css'));
app.use(express.static(path.join(__dirname, "views")));

// used to parse request body
app.use(express.json());

//Getting html file
app.get("/", function(req, resp) {
  resp.sendFile("index.html", { root: path.join(__dirname, "./views") });
});

app.get("/readings", async function(req, resp) {
  try {
    let data = await Sensor_readings.findOne({
      raw: true,
      order: [["ID", "DESC"]]
    });
    let datachart = await Sensor_readings.findAll({
      raw: true,
      order: [["ID"]]
    }); // datachart is an array of arrays, we can use datachart[] to show them in console

    var resptable = [data, datachart, data.ID];
    resp.send(JSON.stringify(resptable));
  } catch (err) {
    resp.sendStatus(500);
  }
});

//make defined actions after a POST on /control website
app.post("/control", (req, res) => {
  let action = req.body.action; // let is sth like var
  var datetime = new Date(); // getting date
  console.log(datetime.toISOString()); // inner function is converting date to string
  console.log(action);

  Sensor_readings.findAll({ raw: true }).then(Sensor_readings => {
    //console.log(Sensor_readings);
  });

  res.send("1");
});

//bootstrap usage?
//app.use('/views/css', express.static(__dirname + '/node_modules/bootstrap/dist/css'));
require("dns").lookup(require("os").hostname(), function(err, localhost, fam) {
  console.log("addr: " + localhost);
});

wsServer.on("connection", function(ws, req) {
  /******* when server receives messsage from client trigger function with argument message *****/
  ws.on("message", function(message) {
    console.log("Received: " + message);
    //var message = "<airt:35;airh:20;soil:10;brig:15;wat:40;>";
    var n = message.length;
    var i = 0;
    var readingsArray = []; // array of read values
    var colonPosition, semicolonPosition, temp, temp2;
    var newMessage = message;
    for (i = 0; i < 5; i++) {
      colonPosition = newMessage.indexOf(":");
      semicolonPosition = newMessage.indexOf(";");
      temp = newMessage.substring(colonPosition + 1, semicolonPosition);
      temp2 = temp.valueOf();
      readingsArray.push(temp2);
      newMessage = newMessage.slice(semicolonPosition + 1, n);
    }
    let data = Sensor_readings.findOne({
      raw: true,
      order: [["ID", "DESC"]]
    });

    if (
      message[0] == "<" &&
      message[message.length - 1] == ">" &&
      message != "<Update>" &&
      message != "<Water>"
    ) {
      Sensor_readings.build({
        ID: data.ID + 1,
        Air_Temperature: readingsArray[0],
        Air_Humidity: readingsArray[1],
        Soil_Moisture: readingsArray[2],
        Brightness_Level: readingsArray[3],
        Water_Tank_Level: readingsArray[4],
        Date: new Date()
      })
        .save()
        .then(anotherTask => {
          Sensor_readings.reload();
        })
        .catch(error => {
          console.log("blad wpisu do bazy");
          console.log(error);
        });
    }
    wsServer.clients.forEach(function(client) {
      //broadcast incoming message to all clients (s.clients)
      if (client != ws && client.readyState) {
        //except to the same client (ws) that sent this message
        client.send("broadcast: " + message);
      }
    });

    //console.log(message); ify

    // ws.send("From Server only to sender: "+ message); //send to client where message is from
  });
  ws.on("close", function() {
    console.log("lost one client");
  });
  //ws.send("new client connected");
  console.log("new client connected");
});

//Listening on port
//opening on phone/laptop - 192.168.1.61:3000 - device ipv4 address
app.listen(3000, "localhost", function() {
  console.log("Application worker " + process.pid + " started...");
});
server.listen(3000);
