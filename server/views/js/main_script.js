var sock = new WebSocket("ws://localhost:3000");

async function push_to_database(data) {
  sock.send(data);
}

async function get_from_database() {
  try {
    let response = await fetch("/readings", {
      method: "get",
      headers: {
        "Content-Type": "application/json"
      }
    });
    response = await response.json();
    console.log("Got response!", response);
    $("#Soil_moisture").text(response[0].Soil_Moisture + "%");
    $("#Air_temperature").text(response[0].Air_Temperature + "°");
    $("#Brightness_level").text(response[0].Brightness_Level + "%");
    $("#Water_tank_level").text(response[0].Water_Tank_Level + "%");
    $("#Air_Humidity").text(response[0].Air_Humidity + "%");
    makeChart(response[1]);
  } catch (err) {
    console.error(`Error: ${err}`);
    $("#Soil_moisture").text("err");
    $("#Air_temperature").text("err");
    $("#Brightness_level").text("err");
    $("#Water_tank_level").text("err");
  }
}
var d, h, m, s, animate;

function init() {
  d = new Date();
  h = d.getHours();
  m = d.getMinutes();
  s = d.getSeconds();
  clock();
}

function clock() {
  s++;
  if (s == 60) {
    s = 0;
    m++;
    if (m == 60) {
      m = 0;
      h++;
      if (h == 24) {
        h = 0;
      }
    }
  }
  $("sec", s);
  $("min", m);
  $("hr", h);
  animate = setTimeout(clock, 1000);
}

function $(id, val) {
  if (val < 10) {
    val = "0" + val;
  }
  document.getElementById(id).innerHTML = val;
}

function makeChart(chartData) {
  var ctx = document.getElementById("myChart").getContext("2d");

  console.log(chartData[0]);
  var chart = new Chart(ctx, {
    // The type of chart we want to create
    type: "line",
    // The data for our dataset
    data: {
      labels: ["January", "February", "March", "April", "May", "June", "July"], // date
      datasets: [
        {
          label: "My First dataset",
          backgroundColor: "rgb(255, 99, 132)",
          borderColor: "rgb(255, 99, 132)",
          data: [0, 10, 5, 2, 20, 30, 45] // will be air or soil humidity
        }
      ]
    },
    // Configuration options go here
    options: {}
  });
}
window.onload = init;
