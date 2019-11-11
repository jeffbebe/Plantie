async function push_to_database(data) {
  try {
    const response = await fetch("/control", {
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
    console.log("Completed!", response);
    document.getElementById("Soil_moisture").innerText =
      response.Soil_Moisture + "%";
    document.getElementById("Air_temperature").innerText =
      response.Air_Temperature + "°";
    document.getElementById("Brightness_level").innerText =
      response.Brightness_Level + "%";
    document.getElementById("Water_tank_level").innerText =
      response.Water_Tank_Level + "%";
  } catch (err) {
    console.error(`Error: ${err}`);
  }
}
