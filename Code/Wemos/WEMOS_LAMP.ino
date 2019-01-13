/*-----------------------------------
  Device Lamp
  version: 0.4
  contributors: 2
  Jordy van der Wijngaard 12073997
  Willem van der Gaag 13009672
----------------------------------*/

#include <FastLED.h>

#define LED_PIN     D5
#define NUM_LEDS    1

#include <Wire.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 54000
#define I2C_SDL    D1
#define I2C_SDA    D2

/*defining WPA login data for WiFi connection.*/
char* network = "MichielDeRouter";
char* pass =  "100%Domotica";

String sending = "";
String returnval = "";
WiFiServer wifiServer(PORT);
StaticJsonBuffer<200> jsonBuffer;

/*defining static ip information.*/
IPAddress ip(10, 5, 5, 103);
IPAddress GW(10, 5, 5, 1);
IPAddress netmask(255, 255, 255, 0);

void reconnect();
void recieveObject(JsonObject&);
String SendJson();
void kiesSensor();

struct Data {
  int id;
  String cmd;
  int state;
};

CRGB leds[NUM_LEDS];

struct Data Ontvangst, bewegingsSensor;

void leesBeweging();
void wijzigLed();
void initLed();


void setup() {
  Wire.begin();
  Serial.begin(9600);
  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  WiFi.begin(network, pass);
  WiFi.config(ip, GW, netmask, GW);
  Serial.println("connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n---------------------------------------------");
  Serial.print("Connected to wifi. Ip address: ");
  Serial.println(WiFi.localIP());

  wifiServer.begin();

  initSensoradres();
  initLED();
  bewegingsSensor.state = 0;
}

void loop() {
  jsonBuffer.clear();
  //leesBeweging();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected trying to reconnect:");
    reconnect();
  }

  WiFiClient pi = wifiServer.available();

  if (pi) {
    Serial.println(bewegingsSensor.state);
    Serial.println("client connected");
    while (pi.connected()) {
      if (pi.available()) {
        Serial.println("recieving:");
        JsonObject& temp = jsonBuffer.parseObject(pi);
        if (!temp.success())Serial.println("error parsing");
        pi.flush();
        temp.printTo(returnval);

        temp.printTo(Serial);
        recieveObject(temp);
        kiesSensor(); // bepaal waar de data naartoe moet
      }

      if(returnval.length() > 5){
      pi.print(returnval);
      }

      returnval = "";

      if (sending.length() > 5) {
          pi.print(sending);
          sending = "";
        }
      jsonBuffer.clear();
    }
    Serial.println("client disconnected");
  }
}

void initLED()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(D5, OUTPUT);
}

void kiesSensor()
{
  /*
      Hier kijken we naar de aard van het bericht. Op basis van het bericht word besloten waar de informatie naartoe gestuurd moet worden.
  */

  // Controleer of de ontvangen data read of write is
  if (Ontvangst.cmd == "r") {
    // Spreek de juiste functie aan op basis van het id dat ontvangen is
    switch (Ontvangst.id) {
      case 6:
        Serial.print("sending state:");
        sending = SendJson(Ontvangst);
        Serial.print(sending);
        break;
      case 7:
        leesBeweging();
        Serial.print("sending state:");
        sending = SendJson(bewegingsSensor);
        Serial.print(sending);
        break;
      default: break;
    }
  }
  else if (Ontvangst.cmd == "w") {
    // Spreek de juiste functie aan op basis van het id dat ontvangen is
    switch (Ontvangst.id) {
      case 6:
        wijzigLed();
        break;
      default: break;
    }
  }
}

void leesBeweging()
{
  //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  unsigned int inputs = Wire.read();
  Serial.print("Digital in: ");
  Serial.println(inputs & 0x0F);

  bewegingsSensor.state = inputs % 2;
}

void wijzigLed()
{
  if (Ontvangst.state) {            // lamp aan als er beweging is
    leds[0] = CRGB::Gray;
    FastLED.show();
  }
  else{
    leds[0] = CRGB::Black;
    FastLED.show();         // lamp uit als er geen beweging is
  }
}

void initSensoradres()
{
  // Zet ID's
  bewegingsSensor.id = 7;
}

String SendJson(struct Data temp) {
  String returnVal;
  jsonBuffer.clear();
  JsonObject& msg = jsonBuffer.createObject();
  msg["id"].set(temp.id);// + 1);
  msg["command"].set(temp.cmd);
  msg["value"].set(temp.state);// + 1500);
  msg.printTo(Serial);
  msg.printTo(returnVal);
  return returnVal;
}
void recieveObject(JsonObject& item) {
  Ontvangst.id = item["id"].as<int>();
  Ontvangst.cmd = item["command"].as<String>();
  Ontvangst.state = item["value"].as<int>();
}

void reconnect() {
  WiFi.begin(network, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("reconnecting");

  }
  Serial.println("reconnected");
}
