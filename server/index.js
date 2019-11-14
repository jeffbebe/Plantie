/*
For node express usage (in project folder - cmd)

npm install express --save

For bootstrap usage

npm install --save bootstrap
*/

var express = require("express");
var path = require("path");
var app = express();
var Sequelize = require("sequelize");
var port = 3000;

// connecting via sequelize, sqlite file is required
const sequelize = new Sequelize({
  dialect: "sqlite",
  storage: "database/baza.sqlite",
  //logging: (...msg) => console.log(msg), // tells what's going on in the database
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
    ID: {
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

// Some table display read from database
/* sequelize
  .getQueryInterface()
  .showAllSchemas()
  .then(tableObj => {
    console.log("// Tables in database", "==========================");
    console.log(tableObj);
  })
  .catch(err => {
    console.log("showAllSchemas ERROR", err);
  }); */

//getting current date for the table
/* var datetime = new Date();
console.log(datetime.toISOString()); */

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
    resp.send(JSON.stringify(data));
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
    console.log(Sensor_readings);
  });

  res.send("1");
});

//bootstrap usage?
//app.use('/views/css', express.static(__dirname + '/node_modules/bootstrap/dist/css'));

//Listening on port
//opening on phone/laptop - 192.168.1.61:3000 - device ipv4 address
app.listen(3000, "localhost", function() {
  console.log("Application worker " + process.pid + " started...");
});
