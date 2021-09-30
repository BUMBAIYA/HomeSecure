#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_Fingerprint.h>
#include <FS.h>
#include "index.h"

const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

const unsigned long eventInterval2 = 30000;
unsigned long previousTime2 = 0;

const long utcOffSetInSeconds = 19802;

const char* ssid = "Chauhan";
const char* password = "9619886170";
const uint8_t gpio[4] = {D5,D6,D7,D8};
const char* host = "www.google.com";
char buff[24];
String data[4];
int pos;
int id;
String state = "OFF";
String dataCheck = "OK";
int pin;

ESP8266WebServer server(80);
SoftwareSerial mySerial(D1,D2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org",utcOffSetInSeconds);

void setup() {
  WiFiClient client;
  Serial.begin(115200);
  for(int x=0;x<4;x++) {
    pinMode(gpio[x], OUTPUT);
  }

  finger.begin(57600);

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  Serial.println("Connected to selected wifi");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  server.on("/", sendWebPage);
  server.on("/bootstrap.min.css", bootstrap);
  server.on("bootstrap.min.css", bootstrap);
  server.on("/bootstrap.min.js", jsbootstrap);
  server.on("bootstrap.min.js", jsbootstrap);
  server.on("/led_control", ledControl);
  server.on("/recData", sendSensorData);
  server.on("/schData", saveData);
  server.on("/sds", selectedDelete);
  server.on("/disPill", pillState);
  server.begin();
  SPIFFS.begin();
  timeClient.begin();
  if (client.connect(host,80)) {
    Serial.println("Starting Time calibration.");
    timeClient.update();
    int x = timeClient.getMinutes();
    int y=x;
    while (x == y) {
      timeClient.update();
      y = timeClient.getMinutes();
      delay(1000);
      Serial.print(".");
    }
    Serial.println("Clock calibrated Successfully");
  }
  else {
    Serial.println("ESP8266 is offline cannot calibrate clock");
  }
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= eventInterval) {
    id = getID();
    previousTime = currentTime;
  }
  unsigned long currentTime2 = millis();
  if (currentTime2 - previousTime2 >= eventInterval2) {
    checkScheduleRun();
    previousTime2 = currentTime2;
  }
  server.handleClient();
}

void sendWebPage() {
  String c = WebPage;
  server.send(200, "text/html", c);
}

void bootstrap() {
  File file = SPIFFS.open("/bootstrap.min.css.gz", "r");
  size_t sent = server.streamFile(file, "text/css");
}

void jsbootstrap() {
  File file = SPIFFS.open("/bootstrap.min.js.gz", "r");
  size_t sent = server.streamFile(file, "application/javascript");
}

void ledControl() {
  String s = server.arg("ledData");
  float randomFloat = s.toFloat();
  int led_state = randomFloat;
  int led_pin = ((randomFloat*10) - (led_state*10));
  if (led_state == 1) {
    digitalWrite(gpio[led_pin],HIGH);
    pin = led_pin;
    state = "ON";
    server.send(200, "text/plain","ON");
  }
  else {
    digitalWrite(gpio[led_pin],LOW);
    pin = led_pin;
    state = "OFF";
    server.send(200, "text/plain","OFF");
  }
}

void sendSensorData() {
  server.send(200, "text/plain", String(id));
}

int getID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -2;
  return finger.fingerID;
}

void saveData() {
  dataCheck = "OK";
  String data = server.arg("data");
  Serial.println(data);
  File file = SPIFFS.open("/scheduleLog.txt", "a+");
  file.print(data);
  file.close();
  Serial.println("Data written in the file");
  readStoreData();
}

void readStoreData() {
  File file = SPIFFS.open("/scheduleLog.txt", "r");
  Serial.print("FILE CONTENT: ");
  while (file.available()) {
    char c = file.read();
    buff[pos] = c;
    pos++;
  }
  Serial.println(buff);
  String c = String(buff);
  Serial.println("Reading file is done.");
  pos = 0;
  for (int a=0;a<4;a++) {
    int i = (a * 6);
    int y = ((a+1) * 6);
    String t = c.substring(i,y);
    data[a] = t;
    Serial.println(data[a]);
  }
  for (int x=0;x<4;x++) {
    if (data[x].length() < 6 && data[x].length() > 0){
      dataCheck = "ER";
    }
  }
  server.send(200, "text/plain", dataCheck);
}

void selectedDelete() {
  String ind = server.arg("index");
  int index = ind.toInt();
  data[index] = "";
  memset(buff,0,sizeof buff);
  SPIFFS.remove("/scheduleLog.txt");
  File file = SPIFFS.open("/scheduleLog.txt", "a+");
  for(int x=0;x<4;x++) {
    if (data[x].length() >5) {
      Serial.println(data[x]);
      file.print(data[x]);
    }
  }
  file.close();
  Serial.println("After selected delete");
  server.send(200, "text/plain", "SDS");
  readStoreData();
}

void checkScheduleRun() {
  timeClient.update();
  String hr = String(timeClient.getHours());
  hr = hr.length() == 1 ? "0" + hr : hr;
  String mn = String(timeClient.getMinutes());
  mn = mn.length() == 1 ? "0" + mn : mn;
  String tm = String(hr + ":" + mn);
  for (int x=0;x<4;x++) {
    if (data[x].length() == 6) {
      String h = data[x].substring(2,4);
      String m = data[x].substring(4,6);
      String p = data[x].substring(0,1);
      String mde = data[x].substring(1,2);
      int md = mde.toInt();
      int pn = p.toInt();
      if (tm == h + ":" + m) {
        if (md == 1) {
          digitalWrite(gpio[pn],HIGH);
          state = "ON";
          pin = pn;
        }
        else {
          digitalWrite(gpio[pn], LOW);
          state = "OFF";
          pin = pn;
        }
      }
    }
  }
}

void pillState() {
  String s = String(pin) + state;
  server.send(200, "text/plain", s);
}