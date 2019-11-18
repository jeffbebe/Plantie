async function push_to_database(data) {
 try {
  const response = await fetch("/readings", {
   method: "post",
   headers: {
    "Content-Type": "application/json"
   },
   body: JSON.stringify({ action: data })
  });
  console.log(response);
 } catch (err) {
  console.error(`Error: ${err}`);
 }
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
  $("#Soil_moisture").text(response.Soil_Moisture + "%");
  $("#Air_temperature").text(response.Air_Temperature + "°");
  $("#Brightness_level").text(response.Brightness_Level + "%");
  $("#Water_tank_level").text(response.Water_Tank_Level + "%");
 } catch (err) {
  console.error(`Error: ${err}`);
  $("#Soil_moisture").text("null");
  $("#Air_temperature").text("null");
  $("#Brightness_level").text("null");
  $("#Water_tank_level").text("null");
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

window.onload = init;
