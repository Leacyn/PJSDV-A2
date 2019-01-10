/*-----------------------------------
  Device Stoel
  version: 0.4
  contributors: 2
  Jordy van der Wijngaard 12073997
  Willem
----------------------------------*/

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

char* network = "Jordy en Manouk";
char* pass =  "gkTgbmvX3yfh";
String sending = "";
String returnval = "";

WiFiServer wifiServer(PORT);
StaticJsonBuffer<200> jsonBuffer;
IPAddress ip(192, 168, 178, 30);
IPAddress GW(192, 168, 178, 1);
IPAddress netmask(255, 255, 255, 0);

void reconnect();
void recieveObject(JsonObject&);
String SendJson();
void kiesSensor();
void leesDruksensor();
void leesSwitch();
void wijzigTril();
void wijzigLed();

struct Data {
  int id;
  String cmd;
  int state;
}; 

int currentState = 0;
int prevState = 0;

struct Data Ontvangst, drukSensor, Switch, Tril, Led;

void setup(void) {
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
  
  pinMode(D0, INPUT);

  Led.state = 0;
  Tril.state = 0;
  Ontvangst.state = 0;

  Switch.id = 3;
  drukSensor.id = 4;
}

void loop(void) {
  Wire.begin();
  jsonBuffer.clear();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected trying to reconnect:");
    reconnect();
  }

  WiFiClient pi = wifiServer.available();
  
  if (pi) {
    Serial.println("client connected");
    
    while (pi.connected()) {
      if (pi.available()) {
        
        Serial.println("receiving:");
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

void wijzigTril()
{
  Tril.state = Ontvangst.state;
  
  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet leds op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte((Tril.state + Led.state) << 4));
  Wire.endTransmission();
}

void wijzigLed()
{
  Led.state = Ontvangst.state;
  
  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet leds op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte((Led.state + Tril.state) << 4));
  Wire.endTransmission();
}

void leesSwitch()
{
    // Begin transmissie met switch
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x00));
    Wire.endTransmission();

    // Lees switch uit
    Wire.requestFrom(0x38, 4);
    unsigned int answer = Wire.read(); // uitgelezen waarde

    delay(50);

    currentState = answer % 2;

    if(currentState != prevState)
    {
      if(currentState)
      {
        Switch.state = !Switch.state;
      }
    }

    prevState = currentState;
    
  }


void leesDruksensor()
{
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));
  Wire.write(byte(0x03));
  Wire.endTransmission();
  
  //Read analog 10bit inputs 0&1
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();
  drukSensor.state = (anin0/100);
  Serial.print("analog in 0: ");
  Serial.println(anin0);
}

void kiesSensor()
{
  // Controleer of de ontvangen data read of write is
  if (Ontvangst.cmd == "r") {
    // Spreek de juiste functie aan op basis van het id dat ontvangen is
    switch (Ontvangst.id) {
      case 3:
        leesSwitch();
        Serial.print("sending state:");
        sending = SendJson(Switch);
        Serial.print(sending);
        break;
      case 4:
        leesDruksensor();
        Serial.print("sending state:");
        sending = SendJson(drukSensor);
        Serial.print(sending);
        break;
      case 5:
        Serial.print("sending state:");
        sending = SendJson(Ontvangst);
        Serial.print(sending);
        break;
      case 6:
        Serial.print("sending state:");
        sending = SendJson(Ontvangst);
        Serial.print(sending);
        break;
    }
  }
  else if (Ontvangst.cmd == "w") {
    // Spreek de juiste functie aan op basis van het id dat ontvangen is
    switch (Ontvangst.id) {
      case 5:
        wijzigTril(); //Geef 2
        break;
      case 6:
        wijzigLed();  //Geef 1
        break;
      default: break;
    }
  }
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
