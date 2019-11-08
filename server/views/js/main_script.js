function clock_visibiity() {
  document.getElementById("clock_id").style.visibility = "hidden";
}

/* function push_to_database(data) {
    try {
      const response = await fetch("/control", {
        method: "post",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify({ action: data })
      });
      console.log("Completed!", response);
    } catch (err) {
      console.error(`Error: ${err}`);
    }
} */
