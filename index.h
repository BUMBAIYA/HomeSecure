const char webpage[] PROGMEM = R"=====(
<html charset=UTF-8>
    <head>
        <meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>
        <script src="/bootstrap.min.js"></script>
        <link href="/bootstrap.min.css" rel="stylesheet">
        <title>Smarthome and security</title>
    </head>
    <body>
        <div class='w-100'>
            <nav class='navbar navbar-light bg-primary'>
                <div class='container-fluid'>
                    <span class='navbar-brand mb-0 h1 text-white p-2 fs-3'>SmartHome and Security</span>
                </div>
            </nav>
            <div class='d-flex justify-content-center shadow-lg m-3'>
                 <div class='w-100'>
                        <label class='p-3 fs-5 bg-primary bg-gradient rounded-top d-block text-white'>
                            Controls
                        </label>
                        
                    <div class='bd-example m-3'>
                        <label class='fs-3 p-2'>GPIO</label>
                        <br>
                        <div class="card card-body">
                            <div class='d-flex flex-column'>
                                <div class='row align-item-start p-2'>
                                    <div class='col'><h4 class='fw-bold'>D5<span id="D5" class="badge rounded-pill bg-dark">OFF</span></h4></div>
                                    <div class='col'><button class='btn btn-success btn-lg' onclick="send(1,5)">ON</button></div>
                                    <div class='col'><button class='btn btn-danger btn-lg' onclick="send(0,5)">OFF</button></div>
                                </div>
                                <div class='row align-item-start p-2'>
                                    <div class='col'><h4 class='fw-bold'>D6<span id="D6" class="badge rounded-pill bg-dark">OFF</span></h4></div>
                                    <div class='col'><button class='btn btn-success btn-lg' onclick="send(1,6)">ON</button></div>
                                    <div class='col'><button class='btn btn-danger btn-lg' onclick="send(0,6)">OFF</button></div>
                                </div>
                                <div class='row align-item-start p-2'>
                                    <div class='col'><h4 class='fw-bold'>D7<span id="D7" class="badge rounded-pill bg-dark">OFF</span></h4></div>
                                    <div class='col'><button class='btn btn-success btn-lg' onclick="send(1,7)">ON</button></div>
                                    <div class='col'><button class='btn btn-danger btn-lg' onclick="send(0,7)">OFF</button></div>
                                </div>
                                <div class='row align-item-start p-2'>
                                    <div class='col'><h4 class='fw-bold'>D8<span id="D8" class="badge rounded-pill bg-dark">OFF</span></h4></div>
                                    <div class='col'><button class='btn btn-success btn-lg' onclick="send(1,8)">ON</button></div>
                                    <div class='col'><button class='btn btn-danger btn-lg' onclick="send(0,8)">OFF</button></div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class='d-flex justify-content-center shadow-lg m-3'>
                <div class='w-100'>
                    <label class='p-3 fs-5 bg-primary bg-gradient rounded-top d-block text-white'>
                        Security log
                    </label>
                    <div class='bd-example m-3'>
                        <label class='fs-3 p-2'>Fingerprint Sensor log</label>
                        <button id='clear' class='btn btn-danger' onclick='clearStorage()'>Delete all records</button>
                        <br>
                        <table class='table table-hover'>
                            <thead>
                                <tr>
                                  <th scope='col'>#</th>
                                  <th scope='col'>Date</th>
                                  <th scope='col'>Time</th>
                                  <th scope='col'>Status</th>
                                  <th scope='col'>#ID</th>
                                  <th scope='col'>Command</th>
                                </tr>
                              </thead>
                              <tbody id='sensorLogTable'>
                              </tbody>
                        </table>
                    </div>
                </div>
            </div>
            <div class="d-flex justify-content-center shadow-lg m-3">
                <div class="w-100">
                    <label class='p-3 fs-5 bg-primary bg-gradient rounded-top d-block text-white'>
                        Schedule Task
                    </label>
                    <div class="bd-example m-3">
                        <label class='fs-3 p-2 d-block'>Schedule task</label>
                        <label class='fs-7 p-2 text-danger'>*Note: task can only be scheduled for current day</label>
                        <div class="d-flex flex-column mt-3">
                            <div class="card  card-body">
                                <form class="row g-3">
                                    <div class="col-md-6 mt-2">
                                        <label class="form-label fw-bold">NodeMcu Pin No.</label>
                                        <select class="form-select" id="inputGroupSelect01">
                                            <option selected>Choose....</option>
                                            <option value="D5">D5</option>
                                            <option value="D6">D6</option>
                                            <option value="D7">D7</option>
                                            <option value="D8">D8</option>
                                        </select>
                                    </div>
                                    <div class="col-md-6 mt-2">
                                        <label class="form-label fw-bold">Choose Pin State</label>
                                        <select name="" id="default_state" class="form-select">
                                            <option value="ON">OFF</option>
                                            <option value="OFF">ON</option>
                                        </select>
                                    </div>
                                    <div class="col-md-6 mt-3">
                                        <label class='form-label fw-bold'>Choose Time</label>
                                        <div class="card card-body">
                                            <div class="slidecontainer">
                                                <label>Choose Hour: <input type="range" class="form-range" id="hourRange" min="1" max="24"></label>
                                            </div>
                                            <div class="slidecontainer">
                                                <label for="">Choose Minute: <input type="range" class="form-range" id="minRange" min="0" max="59"></label>
                                            </div>
                                        </div>
                                    </div>
                                    <div class="col-md-6 mt-3">
                                        <label class='form-label fw-bold'>Selected Time</label>
                                        <div class="card card-body">
                                            <ul class="list-inline">
                                                <li class="list-inline-item">Time:</li>
                                                <li id='dispHour' class="list-inline-item fw-bold">0</li>
                                                <li class="list-inline-item">:</li>
                                                <li id='dispMin' class="list-inline-item fw-bold">0</li>
                                            </ul>
                                        </div>
                                    </div>
                                    <div class="col-12 mt-3">
                                        <button type="button" class="btn btn-primary" onclick="">Submit</button>
                                    </div>
                                </form>
                            </div>
                            <div class="card card-body mt-3">
                                <h4>Schedule Log</h4>
                                <div class="row">
                                    <table class="table">
                                        <thead>
                                          <tr>
                                            <th scope="col">#</th>
                                            <th scope="col">GPIO</th>
                                            <th scope="col">State</th>
                                            <th scope="col">Time</th>
                                            <th scope="col">Status</th>
                                          </tr>
                                        </thead>
                                        <tbody>
                                          <tr>
                                            <th scope="row">1</th>
                                            <td>G5</td>
                                            <td>OFF</td>
                                            <td>16:04</td>
                                            <td>done</td>
                                          </tr>
                                        </tbody>
                                      </table>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <script>
            let status1 = "null";
            let id = "NA";
            var hourSlider = document.getElementById('hourRange');
            var hourDisp = document.getElementById('dispHour');
            hourDisp.innerHTML = hourSlider.value;

            hourSlider.oninput = function() {
                hourDisp.innerHTML = this.value;
            };

            var minSlider = document.getElementById('minRange');
            var minDisp = document.getElementById('dispMin');
            minDisp.innerHTML = minSlider.value;

            minSlider.oninput = function() {
                minDisp.innerHTML = this.value;
            };
            function send(led_sts,led_pin) 
            {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    if (led_pin == 5) {
                        document.getElementById("D5").innerHTML = this.responseText;
                        console.log("btn1 status updated");
                    }
                    else if (led_pin == 6) {
                        document.getElementById("D6").innerHTML = this.responseText;
                        console.log("btn2 status updated");
                    }
                    else if (led_pin == 7) {
                        document.getElementById("D7").innerHTML = this.responseText;
                        console.log("btn3 status updated");
                    }
                    else if (led_pin == 8) {
                        document.getElementById("D8").innerHTML = this.responseText;
                        console.log("btn4 status updated");
                    }
                    else {
                        console.log("Error data not received for state");
                    }
                }
            };
            xhttp.open("GET", "led_set?state="+led_sts+"."+led_pin, true);
            console.log("Data sent");
            xhttp.send();
            }
            setInterval(function() 
            {
            getData();
            }, 1000);
            function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var temp = this.response;
                    if (temp != "nullNA") {
                        status1 = temp.substring(0,6);
                        id = temp.slice(6);
                        getAndUpdate();
                    }
                }
            };
            xhttp.open("GET", "sendData", true);
            xhttp.send();
            }
            update();
            function getAndUpdate() {
                let time = new Date();
                let hour = time.getHours();
                let min = time.getMinutes();
                let sec = time.getSeconds();
                let date = time.getDate();
                let month = (time.getMonth() + 1);
                let year = time.getFullYear();
                am_pm = "AM";
                if (hour > 12) {
                    hour -= 12;
                    am_pm = "PM";
                }
                if (hour == 0) {
                    hr = 12;
                    am_pm = "AM";
                }
                hour = hour < 10 ? "0" + hour : hour;
                min = min < 10 ? "0" + min : min;
                sec = sec < 10 ? "0" + sec : sec;
                let currentTime = hour + ":" + min + ":" + sec + am_pm;
                let currentDate = date + "/" + month + "/" + year;

                if (localStorage.getItem('itemJson') == null) {
                    itemJsonArray = [];
                    itemJsonArray.push([currentDate, currentTime, status1, id]);
                    localStorage.setItem('itemJson', JSON.stringify(itemJsonArray));
                }
                else {
                    itemJsonArrayStr = localStorage.getItem('itemsJson');
                    itemJsonArray = JSON.parse(itemJsonArrayStr);
                    itemJsonArray.push([currentDate, currentTime, status1, id]);
                    localStorage.setItem('itemsJson', JSON.stringify(itemJsonArray));
                }
                update();
            }
            function update() {
                if (localStorage.getItem('itemsJson') == null) {
                    itemJsonArray = [];
                    localStorage.setItem('itemsJson', JSON.stringify(itemJsonArray));
                }
                else {
                    itemJsonArrayStr = localStorage.getItem('itemsJson');
                    itemJsonArray = JSON.parse(itemJsonArrayStr);
                }
                let tableBody = document.getElementById("sensorLogTable");
                let str = "";
                itemJsonArray.forEach((element, index) => {
                    str += `
                        <tr>
                        <th scope="row">${index + 1}</th>
                        <td>${element[0]}</td>
                        <td>${element[1]}</td>
                        <td>${element[2]}</td>
                        <td>${element[3]}</td>
                        <td><button class='btn btn-sm btn-danger' onclick='deleted(${index})'>Delete</button></td> 
                        </tr>`;
                });
                tableBody.innerHTML = str;
            }
            function deleted(itemIndex) {
                console.log("Delete", itemIndex);
                itemJsonArrayStr = localStorage.getItem('itemsJson');
                itemJsonArray = JSON.parse(itemJsonArrayStr);
                itemJsonArray.splice(itemIndex, 1);
                localStorage.setItem('itemsJson', JSON.stringify(itemJsonArray));
                update();
            }
            function clearStorage() {
                if (confirm("Do you areally want to clear?")) {
                    console.log('Clearing the storage');
                    localStorage.clear();
                    update();
                }
            }
        </script>
    </body>
</html>

)====="; 