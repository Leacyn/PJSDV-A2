#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 54000

char* network = "MichielDeRouter";
char* pass =  "100%Domotica";
int written = 0;

struct tcpData {
  int id;
  const char *command;
  int value;
} tcpData;
struct tcpData item;

WiFiServer wifiServer(PORT);
StaticJsonBuffer<200> jsonBuffer;
IPAddress ip(10, 5, 5, 101);
IPAddress GW(10, 5, 5, 1);
IPAddress netmask(255, 255, 255, 0);


void reconnect();
unsigned int ReadAnalog();
int PrintJson(JsonObject&);
String returnValue(WiFiClient);

void setup() {


  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("setting up");
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
}

void loop() {
  char *c;
  struct tcpData *msg;
  msg = &item;
  // put your main code here, to run repeatedly:

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected trying to reconnect:");
    reconnect();
  }

  WiFiClient pi = wifiServer.available();


 
  if (pi) {
    Serial.println("client connected");
    while (pi.connected()) {
      int i = 0;
      //pi.flush();
      while (pi.available() > 0 && i == 0) {
        i = 1;
        Serial.println("recieving:");
        JsonObject& temp = jsonBuffer.parseObject(pi);
        if (!temp.success())Serial.println("error parsing");
        Serial.println("translating");
        PrintJson(temp);

        pi.print(returnValue(pi));

        //  pi.print("Hello from server \n:");
      }
      jsonBuffer.clear();
    }
    Serial.println("client disconnected");
    //pi.stop();
  }
}

void reconnect() {
  WiFi.begin(network, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("reconnecting");

  }
  Serial.println("reconnected");
}

unsigned int ReadAnalog() {
  unsigned int value = 0;
  Wire.requestFrom(0x36, 2);
  value = Wire.read() & 0x03;
  value = value << 8;
  value = value | Wire.read();
  unsigned int temp  = Wire.read(); temp += Wire.read();
  Serial.print("analog in 0: ");
  Serial.println(value);

  return value;
}



int PrintJson(JsonObject& json) {
  Serial.print("this is the json message: ");
  json.printTo(Serial);
  item.id = json["id"].as<int>();
  item.command = json["command"].as<char *>();
  item.value = json["value"].as<int>();
  Serial.print("\nid: ");
  Serial.println(item.id);
  Serial.print("command: ");
  Serial.println(item.command);
  Serial.print("value: ");
  Serial.println(item.value);
  //return temp;
}

String returnValue(WiFiClient pi) {
  String returnVal;
  jsonBuffer.clear();
  JsonObject& msg = jsonBuffer.createObject();
  msg["id"].set(item.id);// + 1);
  msg["command"].set((String)item.command);
  msg["value"].set(item.value);// + 1500);
  msg.printTo(Serial);
  msg.printTo(returnVal);
  return returnVal;
}
