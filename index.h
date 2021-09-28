const char WebPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/bootstrap.min.css">
    <script src="/bootstrap.min.js"></script>
    <title>SmartHome and Security</title>
    <style>.btn-lg:hover{font-size: 1.35rem;}.btn-md:hover{font-size: 1.1rem;}</style>
</head>
<body>
    <div class="w-100">
        <nav class="navbar navbar-light bg-primary">
            <span class="navbar-brand text-white fs-4 p-1 px-3">SmartHome and Security</span>
        </nav>
        <div class="d-flex justify-content-center m-3 shadow-lg">
            <div class="w-100">
                <label class="bg-primary fs-5 text-white p-3 d-block rounded-top bg-gradient">Controls</label>
                <div class="bd-example">
                    <div class="card card-body m-3">
                        <div class="d-flex flex-column p-2">
                            <div class="row align-item-center p-2">
                                <div class="col"><h4 id="h5" class="fw-bold">D5</h4><span id="D5" class="badge rounded-pill bg-dark">OFF</span></div>
                                <div class="col"><button class="btn btn-success btn-lg" onclick="send(1,0)">ON</button></div>
                                <div class="col"><button class="btn btn-danger btn-lg" onclick="send(0,0)">OFF</button></div>
                            </div>
                            <br>
                            <div class="row p-2">
                                <div class="col"><h4 id="h6" class="fw-bold">D6</h4><span id="D6" class="badge rounded-pill bg-dark">OFF</span></div>
                                <div class="col"><button class="btn btn-success btn-lg" onclick="send(1,1)">ON</button></div>
                                <div class="col"><button class="btn btn-danger btn-lg" onclick="send(0,1)">OFF</button></div>
                            </div>
                            <br>
                            <div class="row p-2">
                                <div class="col"><h4 id="h7" class="fw-bold">D7</h4><span id="D7" class="badge rounded-pill bg-dark">OFF</span></div>
                                <div class="col"><button class="btn btn-success btn-lg" onclick="send(1,2)">ON</button></div>
                                <div class="col"><button class="btn btn-danger btn-lg" onclick="send(0,2)">OFF</button></div>
                            </div>
                            <br>
                            <div class="row p-2">
                                <div class="col"><h4 id="h8" class="fw-bold">D8</h4><span id="D8" class="badge rounded-pill bg-dark">OFF</span></div>
                                <div class="col"><button class="btn btn-success btn-lg" onclick="send(1,3)">ON</button></div>
                                <div class="col"><button class="btn btn-danger btn-lg" onclick="send(0,3)">OFF</button></div>
                            </div>
                            <br>
                            <div class="p-2">
                                <button class="btn btn-primary btn-md p-2" data-bs-toggle="collapse" data-bs-target="#content">Edit Appliance Name</button>
                                <div class="collapse mt-2" id="content">
                                    <div class="card card-body">
                                        <div class="input-group mb-3">
                                            <span class="input-group-text">Pin D5</span>
                                            <input type="text" class="form-control" placeholder="Appliance Name" id="app1">
                                        </div>
                                        <div class="input-group mb-3">
                                            <span class="input-group-text">Pin D6</span>
                                            <input type="text" class="form-control" placeholder="Appliance Name" id="app2">
                                        </div>
                                        <div class="input-group mb-3">
                                            <span class="input-group-text">Pin D7</span>
                                            <input type="text" class="form-control" placeholder="Appliance Name" id="app3">
                                        </div>
                                        <div class="input-group mb-3">
                                            <span class="input-group-text">Pin D8</span>
                                            <input type="text" class="form-control" placeholder="Appliance Name" id="app4">
                                        </div>
                                        <div class="col-auto">
                                            <button class="btn btn-primary btn-md" onclick="changeName()">Save</button>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="d-flex justify-content-center m-3 shadow-lg">
            <div class="w-100">
                <label class="bg-primary fs-5 text-white p-3 d-block rounded-top bg-gradient">Security</label>
                <div class="m-3">
                    <label class="fs-3 p-2">Sensor Data Log</label>
                    <table class="table table-hover">
                        <thead>
                            <tr>
                                <th scope="col">#</th>
                                <th scope="col">Date</th>
                                <th scope="col">Time</th>
                                <th scope="col">Status</th>
                                <th scope="col">#ID</th>
                                <th scope="col">Command</th>
                            </tr>
                        </thead>
                        <tbody id="sensorLog">
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
        <div class="d-flex justify-content-center shadow-lg m-3">
            <div class="w-100">
                <label class="bg-primary fs-5 text-white p-3 d-block rounded-top bg-gradient">Task Scheduler</label>
                <div class="bd-example m-3">
                    <label class="fs-3 p-2 d-block">Schedule Task</label>
                    <label class="fs-7 p-2 text-danger fw-bold">*Note:Only four tasks can be scheduled in a day</label>
                    <div class="d-flex flex-column mt-3">
                        <div class="card  card-body">
                            <form class="row g-3">
                                <div class="col-md-6 mt-2">
                                    <label class="form-label fw-bold">Choose Appliance</label>
                                    <select class="form-select" id="pinSelectChoice">
                                        <option value=0 id="c1">D5</option>
                                        <option value=1 id="c2">D6</option>
                                        <option value=2 id="c3">D7</option>
                                        <option value=3 id="c4">D8</option>
                                    </select>
                                </div>
                                <div class="col-md-6 mt-2">
                                    <label class="form-label fw-bold">Choose State</label>
                                    <select name="" id="modeSelectChoice" class="form-select">
                                        <option value=0>OFF</option>
                                        <option value=1>ON</option>
                                    </select>
                                </div>
                                <div class="col-md-6 mt-3">
                                    <label class='form-label fw-bold'>Choose Time</label>
                                    <div class="card card-body">
                                        <div class="slidecontainer">
                                            <label>Choose Hour: <input type="range" class="form-range" id="hourRange" min="0" max="23"></label>
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
                                    <button type="button" class="btn btn-md btn-primary" onclick="sendScheduleData()">Submit</button>
                                </div>
                                <div class="d-flex align-items-center" id="msg-loading">
                                </div>
                            </form>
                        </div>
                        <div class="card card-body mt-3">
                            <label class='fs-4 p-2'>Task Scheduled</label>
                            <br>
                            <table class="table table-hover">
                                <thead>
                                    <tr>
                                    <th scope="col">#</th>
                                    <th scope="col">Appliance</th>
                                    <th scope="col">State</th>
                                    <th scope="col">Time</th>
                                    <th scope="col">Command</th>
                                    </tr>
                                </thead>
                                <tbody id="scheduleTable"></tbody>
                            </table>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <script>
        let currentTime;
        let currentDate;
        let id;
        let status;
        let hour;
        let minute;
        let pin;
        let mode;

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

        initialize();
        displaySensorLog();
        updateScheduleLogTable();

        function getTime() {
            var time = new Date();
            hour = time.getHours();
            minute = time.getMinutes();
            var sec = time.getSeconds();
            var date = time.getDate();
            var month = time.getMonth() + 1;
            var year = time.getFullYear();
            var am_pm = "AM";
            if (hour > 12) {
                hour -= 12;
                am_pm = "PM";
            }
            if (hour == 0) {
                hr = 12;
                am_pm = "AM";
            }
            hour = hour < 10 ? "0" + hour:hour;
            minute = minute < 10 ? "0" + minute:minute;
            currentDate = date + "/" + month + "/" + year;
            currentTime = hour + ":" + minute + ":" + sec + am_pm;
        }
        function initialize() {
            if (localStorage.getItem('appName') == null) {
                var JsonStr = ["D5","D6","D7","D8"];
                localStorage.setItem('appName',JSON.stringify(JsonStr));
            }
            else {
                var JsonStr = localStorage.getItem('appName');
                var nameArray = JSON.parse(JsonStr);
                document.getElementById("h5").innerHTML = nameArray[0];
                document.getElementById("h6").innerHTML = nameArray[1];
                document.getElementById("h7").innerHTML = nameArray[2];
                document.getElementById("h8").innerHTML = nameArray[3];
                document.getElementById("c1").innerHTML = nameArray[0];
                document.getElementById("c2").innerHTML = nameArray[1];
                document.getElementById("c3").innerHTML = nameArray[2];
                document.getElementById("c4").innerHTML = nameArray[3];
            }
            nameUpdate();
        }
        function changeName() {
            var app1 = document.getElementById("app1").value;
            var app2 = document.getElementById("app2").value;
            var app3 = document.getElementById("app3").value;
            var app4 = document.getElementById("app4").value;
            if (app1=="" || app2=="" || app3=="" || app4=="") {
                console.log("Check Input");
            }
            else {
                var jsonStr = [app1,app2,app3,app4];
                localStorage.setItem('appName',JSON.stringify(jsonStr));
            }
            nameUpdate();
        }
        function nameUpdate() {
            var str = localStorage.getItem('appName');
            var strArray = JSON.parse(str);
            document.getElementById("h5").innerHTML = strArray[0];
            document.getElementById("h6").innerHTML = strArray[1];
            document.getElementById("h7").innerHTML = strArray[2];
            document.getElementById("h8").innerHTML = strArray[3];
            document.getElementById("c1").innerHTML = strArray[0];
            document.getElementById("c2").innerHTML = strArray[1];
            document.getElementById("c3").innerHTML = strArray[2];
            document.getElementById("c4").innerHTML = strArray[3];
        }
        function tableUpdate() {
            getTime();
            if (localStorage.getItem('sensorItem') == null) {
                itemJsonArray = [];
                itemJsonArray.push([currentDate,currentTime,status,id]);
                localStorage.setItem('sensorItem',JSON.stringify(itemJsonArray));
            }
            else {
                itemJsonArrayStr = localStorage.getItem('sensorItem');
                itemJsonArray = JSON.parse(itemJsonArrayStr);
                itemJsonArray.push([currentDate,currentTime,status,id]);
                localStorage.setItem('sensorItem', JSON.stringify(itemJsonArray));
            }
            displaySensorLog();
        }
        function displaySensorLog() {
            if (localStorage.getItem('sensorItem') == null) {
                itemJsonArray = [];
                localStorage.setItem('sensorItem',JSON.stringify(itemJsonArray));
            }
            else {
                itemJsonArrayStr = localStorage.getItem('sensorItem');
                itemJsonArray = JSON.parse(itemJsonArrayStr);
            }
            let tablebody = document.getElementById("sensorLog");
            let string = "";
            itemJsonArray.forEach((element, index) => {
                string += `
                <tr>
                    <th scope="row">${index + 1}</th>
                    <td>${element[0]}</td>
                    <td>${element[1]}</td>
                    <td>${element[2]}</td>
                    <td>${element[3]}</td>
                    <td><button class="btn btn-danger" onclick="deleteSensorLog(${index})">Delete</button></td>
                </tr>`;
            });
            tablebody.innerHTML = string;
        }
        function deleteSensorLog(logIndex) {
            itemJsonArrayStr = localStorage.getItem('sensorItem');
            itemJsonArray = JSON.parse(itemJsonArrayStr);
            itemJsonArray.splice(logIndex, 1);
            localStorage.setItem('sensorItem',JSON.stringify(itemJsonArray));
            displaySensorLog();
        }
        function submit() {
            var tm = document.getElementById('hourRange').value + ":" + document.getElementById('minRange').value;
            var temp = localStorage.getItem('appName');
            var temp1 = JSON.parse(temp);
            var mdTemp = mode == 1 ? "ON" : "OFF";
            if (localStorage.getItem('scheduleLog') == null) {
                jsonArray = [];
                jsonArray.push([temp1[pin],mdTemp,tm]);
                localStorage.setItem('scheduleLog',JSON.stringify(jsonArray));
            }
            else {
                jsonStr = localStorage.getItem('scheduleLog');
                jsonArray = JSON.parse(jsonStr);
                jsonArray.push([temp1[pin],mdTemp,tm]);
                localStorage.setItem('scheduleLog',JSON.stringify(jsonArray));
            }
            updateScheduleLogTable();
        }
        function updateScheduleLogTable() {
            if (localStorage.getItem('scheduleLog') == null) {
                itemJsonArray1 = [];
                localStorage.setItem('scheduleLog', JSON.stringify(itemJsonArray1));
            }
            else {
                itemJsonArrayStr1 = localStorage.getItem('scheduleLog');
                itemJsonArray1 = JSON.parse(itemJsonArrayStr1);
            }
            let tableBody1 = document.getElementById("scheduleTable");
            let str1 = "";
            itemJsonArray1.forEach((element, index) => {
                str1 += `
                    <tr>
                    <th scope="row">${index + 1}</th>
                    <td>${element[0]}</td>
                    <td>${element[1]}</td>
                    <td>${element[2]}</td>
                    <td><button class='btn btn-danger' onclick='selectedDelete(${index})'>Delete</button></td> 
                    </tr>`;
            });
            tableBody1.innerHTML = str1;
        }
        function selectedDelete(index) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var x = this.response;
                    if (x == "SDS") {
                        itemJsonArrayStr1 = localStorage.getItem('scheduleLog');
                        itemJsonArray1 = JSON.parse(itemJsonArrayStr1);
                        itemJsonArray1.splice(index, 1);
                        localStorage.setItem('scheduleLog', JSON.stringify(itemJsonArray1));
                        updateScheduleLogTable();
                        document.getElementById("msg-loading").innerHTML = "<label class='text-success'>Successfully deleted task</label>";
                    }
                }
            };
            xhttp.open("GET","sds?index="+index);
            xhttp.send();
        }
        function send(ledState,ledPin) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    if (ledPin == 0) {
                        document.getElementById("D5").innerHTML = this.response;
                    }
                    else if (ledPin == 1) {
                        document.getElementById("D6").innerHTML = this.response;
                    }
                    else if (ledPin == 2) {
                        document.getElementById("D7").innerHTML = this.response;
                    }
                    else {
                        document.getElementById("D8").innerHTML = this.response;
                    }
                }
            };
            xhttp.open("GET","led_control?ledData="+ledState+"."+ledPin,true);
            xhttp.send();
        }
        function sendScheduleData() {
            var count = (JSON.parse(localStorage.getItem('scheduleLog'))).length;
            if (count < 4) {
                document.getElementById("msg-loading").innerHTML = "<label class='text-danger'>Adding to database Wait...<div class='spinner-border text-danger spinner-border-sm'></div></label>";
                pin = document.getElementById("pinSelectChoice").value;
                mode = document.getElementById("modeSelectChoice").value;
                hr = document.getElementById('hourRange').value;
                hr = hr<10?"0"+hr:hr;
                mn = document.getElementById('minRange').value;
                mn = mn<10?"0"+mn:mn;
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    if (this.response == "OK") {
                          document.getElementById("msg-loading").innerHTML = "<label class='text-success'>Successfully scheduled task</label>";
                          submit();
                    }
                    else {
                      console.log(this.response);
                      document.getElementById("msg-loading").innerHTML = "<label class='text-danger'>Error occured while scheduling.TRY AGAIN</label>";
                    }
                }
            };
            xhttp.open("GET", "schData?data="+pin+mode+hr+mn, true);
            xhttp.send();
            }
            else {
                document.getElementById("msg-loading").innerHTML = "<label class='text-danger'>Task limit has reached.Try deleting redentent tasks</label>";
            }
        }
        setInterval(function() {
            recData();
            disStatePill();
        },1000);
        function recData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    if (this.response != -1) {
                        if (this.response == -2) {
                            id = "NA";
                            status = "failed"
                            tableUpdate();
                        }
                        else {
                            id = this.response;
                            status = "Pass";
                            tableUpdate();
                        }
                    }
                }
            };
            xhttp.open("GET", "recData", true);
            xhttp.send();
        }
        function disStatePill() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var temp = this.response;
                    var temp1 = temp.charAt(0);
                    var temp2 = temp.substring(1);
                    if (temp1 == "0") {
                        document.getElementById("D5").innerHTML = temp2;
                    }
                    else if (temp1 == "1") {
                        document.getElementById("D6").innerHTML = temp2;
                    }
                    else if (temp2 == "2") {
                        document.getElementById("D7").innerHTML = temp2;
                    }
                    else {
                        document.getElementById("D8").innerHTML = temp2;
                    }
                }
            };
            xhttp.open("GET", "disPill",true);
            xhttp.send();
        }
    </script>
</body>
</html>
)=====";