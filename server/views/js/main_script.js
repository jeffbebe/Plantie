var sock = new WebSocket("ws://localhost:3000");

async function send_command(data) {
  sock.send(data);
}

async function update_database() {
  sock.send("<Update>");
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
    makeChart(response[1], response[2]); // response 1 is data for chart, response 2 is amount of data
  } catch (err) {
    console.error(`Error: ${err}`);
    $("#Soil_moisture").text("err");
    $("#Air_temperature").text("err");
    $("#Brightness_level").text("err");
    $("#Water_tank_level").text("err");
    $("#Air_Humidity").text("err");
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

function makeChart(chartData, count) {
  var ctx = document.getElementById("myChart").getContext("2d");
  var i;
  let dataset = [];
  let labels = [];
  for (i = 0; i < count; i++) {
    let date = new Date(chartData[i].Date);
    dataset[i] = { x: date.toISOString(), y: chartData[i].Soil_Moisture };
    labels.push(date.toISOString());
  }

  var chart = new Chart(ctx, {
    // The type of chart we want to create
    type: "line",
    // The data for our dataset
    data: {
      labels: labels,
      datasets: [
        {
          label: "Soil Moisture",
          data: dataset,
          backgroundColor: ["rgba(23, 96, 180, 0.5)"],
          borderColor: ["rgba(255,99,132,1)"],
          borderWidth: 1
        }
      ]
    },

    options: {
      scales: {
        xAxes: [
          {
            time: {
              unit: "day",
              displayFormats: {
                day: "DD.MM.YYYY HH:mm"
              }
            },

            type: "time",

            distribution: "series"
          }
        ],
        yAxes: [
          {
            display: true,
            ticks: {
              beginAtZero: true,
              steps: 10,
              stepValue: 5,
              max: 100
            }
          }
        ]
      },
      animation: {
        duration: 0 // general animation time
      },
      hover: {
        animationDuration: 0 // duration of animations when hovering an item
      },
      responsiveAnimationDuration: 0 // animation duration after a resize
    }
  });
}
window.onload = init;
