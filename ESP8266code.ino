#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <Adafruit_Fingerprint.h>
#include "index.h"

const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

const char* ssid = "Chauhan";
const char* password = "9619886170";
const uint8_t GPIOPIN[4] = {D5,D6,D7,D8};
String data;
String id = "NA";
String fingerStatus = "null";
ESP8266WebServer server(80);
SoftwareSerial mySerial(D1,D2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); 

void handleRoot() 
{
 String s = webpage;
 server.send(200, "text/html", s);
}

void led_control() 
{
  String state = "OFF";
  String act_state = server.arg("state");
  float led_float = act_state.toFloat();
  if (led_float != 0) {
    int pinState = led_float;
    int btnNumber = ((led_float*10) - (pinState*10));
    Serial.println(pinState);
    Serial.println(btnNumber);
    if (pinState == 1) {
      if (btnNumber == 5) {
        digitalWrite(D5,HIGH);
        Serial.println("led5 ON");
      }
      else if (btnNumber == 6) {
        digitalWrite(D6,HIGH);
        Serial.println("led6 ON");
      }
      else if (btnNumber == 7) {
        digitalWrite(D7,HIGH);
        Serial.println("led7 ON");
      }
      else if (btnNumber == 8) {
        digitalWrite(D8,HIGH);
        Serial.println("led8 ON");
      }
      else {
        Serial.println("Error at active pin but no btn number");
      }
      state="ON";
      server.send(200, "text/plain",state);
      return;
     }
     else if (pinState == 0) {
          if (btnNumber == 5) {
            digitalWrite(D5,LOW);
            Serial.println("led5 OFF");
          }
          else if (btnNumber == 6) {
            digitalWrite(D6,LOW);
            Serial.println("led6 OFF");
          }
          else if (btnNumber == 7) {
            digitalWrite(D7,LOW);
            Serial.println("led7 OFF");
          }
          else if (btnNumber == 8) {
            digitalWrite(D8,LOW);
            Serial.println("led8 OFF");
          }
          else {
            Serial.println("Error at active pin but no btn number");
          }
          state="OFF";
          server.send(200, "text/plain",state);
          return;
      }
      else {
        Serial.println("Error is PinState in not defined");
        return;
      }
  }
  else {
    Serial.println("Error converting string to float");
    return;
  }
}

void setup(void)
{
  for(int x=0;x<4;x++) { 
    pinMode(GPIOPIN[x],OUTPUT);
  }
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting...");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found");
  }
  else {
    Serial.println("Did not find fingerprint sensor");
  }
  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
 
  server.on("/", handleRoot);
  server.on("/bootstrap.min.css", bootstrap);
  server.on("bootstrap.min.css", bootstrap);
  server.on("/bootstrap.min.js", bootstrapmin);
  server.on("bootstrap.min.js", bootstrapmin);
  server.on("/led_set", led_control);
  server.on("/sendData", sendSensorData);
  server.begin();
  SPIFFS.begin();
}

void loop(void)
{
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= eventInterval) {
    getFingerprintID();
    previousTime = currentTime;
  }
  server.handleClient();
}

void bootstrap() {
  File file = SPIFFS.open("/bootstrap.min.css.gz", "r");
  size_t sent = server.streamFile(file, "text/css");
}

void bootstrapmin() {
  File file = SPIFFS.open("/bootstrap.min.js.gz", "r");
  size_t sent = server.streamFile(file, "application/javascript");
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      fingerStatus = "null";
      id = "NA";
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    // here the data edit code will be injected for esp8266 WebServer
    Serial.println("Fingerprint did not matched");
    fingerStatus = "Failed";
    id = "NA";
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  // here the entry log code will be injected for the esp8266 WebServer
  Serial.println("Fingerprint matched Successfully");
  int x = finger.fingerID;
  id = String(x);
  fingerStatus = "Passed";
  return finger.fingerID;
}

void sendSensorData() {
  data = fingerStatus + id;
  server.send(200, "text/plain",data);
}
