function currentTime() {
    let date = new Date(); 
    let hh = date.getHours();
    let mm = date.getMinutes();
    let ss = date.getSeconds();
    let session = "AM";
  
    if (hh == 0) {
        hh = 12;
    }
    if (hh > 12) {
        hh = hh - 12;
        session = "PM";
    }
  
    hh = (hh < 10) ? "0" + hh : hh;
    mm = (mm < 10) ? "0" + mm : mm;
    ss = (ss < 10) ? "0" + ss : ss;
      
    let time = hh + ":" + mm + ":" + ss + " " + session;
  
    document.getElementById("clock").innerText = time; 
}

// Use setInterval for accurate time updates every second
setInterval(currentTime, 1000);

// Add an event listener to the dropdown
document.getElementById('dropdown_container').addEventListener('change', function () {
    // Get the selected value from the dropdown
    var dropdownValue = this.value;

    // Create an object to send as JSON data
    var num;
    
    if (dropdownValue === 'productivity') {
        num = 101010330
        //'0/0/102/0/51/0/255/255/0' 
        var formData = {
            dropdown: num
        };
        
    } else if (dropdownValue === 'day_cycle') {
        num = 313330321301011
        //255/103/255/255/255/0/255/178/102/255/0/127/0/102/51/;
        var formData = {
            dropdown: num
        };
    }
    fetch('/submit', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(formData)
    })
    
});
