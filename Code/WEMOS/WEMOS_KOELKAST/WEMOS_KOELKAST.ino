/*-----------------------------------
  Device Koelkast
  version: 0.4
  contributors: 2
  Jordy van der Wijngaard 12073997
  Willem van der Gaag 13009672
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

/*defining WPA login data for WiFi connection.*/
char* network = "MichielDeRouter"; // SSID
char* pass =  "100%Domotica";      // Wachtwoord

/* Starting setup variables for communication*/
String sending = "";
String returnval = "";


WiFiServer wifiServer(PORT);
StaticJsonBuffer<200> jsonBuffer;
IPAddress ip(10, 5, 5, 106);
IPAddress GW(10, 5, 5, 1);
IPAddress netmask(255, 255, 255, 0);

/*defining functions for communication and more*/
void reconnect();
void recieveObject(JsonObject&);
String SendJson();
void kiesSensor();
void initOutputs();
void leesTemp(); 
void wijzigVentilator(); 
void wijzigKoeling(); 
void leesSwitch(); 

/*data structure voor het opslaan van data van binnenkomende of uitgaande messages.*/
struct Data {
  int id;
  String cmd;
  int state;
}; 

struct Data Ontvangst, Switch, tempHeatsink, tempKoelkast;

void setup(void) 
{
  /*begin met het starten van de seriele verbinding, het starten van de wire library en het starten van de wifi verbinding*/
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

  pinMode(D0, INPUT);   // Ventilator
  pinMode(D5, OUTPUT);  // Koelelement

  Switch.id = 15;
  tempHeatsink.id = 36;
  tempKoelkast.id = 37;
}

void loop(void) 
{
  Wire.begin();
  jsonBuffer.clear();
  /* als de Wifi niet meer verbonden is, herstel de verbinding met de reconnect functie*/
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected trying to reconnect:");
    reconnect();
  }
  /*wijs alle binnenkomende verbindingen toe aan de variabele PI*/
  WiFiClient pi = wifiServer.available();

  /*als er een verbinding gemaakt is*/
  if (pi) {
    Serial.println("client connected");
    /*en de TCP verbinding is opgezet*/
    while (pi.connected()) {
     /*voor zolang er verbinding aanwezig is, lees data uit de TCP buffer en trek er data uit met de ArduinoJson library*/
      if (pi.available()) {

        Serial.println("receiving:");
        JsonObject& temp = jsonBuffer.parseObject(pi);//lees een Json string uit de TCP buffer 

        if (!temp.success())Serial.println("error parsing");

        pi.flush(); // flush the tcp connection to make sure that there is no rogue data
        temp.printTo(returnval);// print een jsonstring naar returnval voor verification

        temp.printTo(Serial);// print een jsonstring naar serial terminal voor feedback.
        recieveObject(temp);
        kiesSensor(); // bepaal waar de data naartoe moet
      }
    /* is er data klaar gezet om teruggestuurd te worden. stuur deze terug naar de Controller(PI)*/
      if (returnval.length() > 5) {
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

void leesTemp()
{ 
  /* Wordt niet gebruikt */
  
  // Begin transmissie met temperatuursensoren
  Wire.beginTransmission(0x36);             
  Wire.write(byte(0xA2));
  Wire.write(byte(0x03));
  Wire.endTransmission();
    
  // Lees temperatuur heatsink            
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;                    
  anin0 = anin0 | Wire.read();

  tempHeatsink.state = anin0;
  
  // Lees temperatuur koelkast
  unsigned int anin1 = Wire.read() & 0x03;    
  anin1 = anin1 << 8;                        
  anin1 = anin1 | Wire.read();

  tempKoelkast.state = anin1;
}

void wijzigVentilator()
{
  /* Wordt niet gebruikt */
  
  // Begin transmissie met ventilator
  Wire.beginTransmission(0x38);       
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();
  
  // Zet ventilator op HIGH
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(Ontvangst.state << 4));
  Wire.endTransmission();
}

void wijzigKoeling()
{ 
  digitalWrite(D5, Ontvangst.state);     // Zet koelelement state op basis van ontvangen data 
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

  delay(20);

  Switch.state = answer % 2; // convert uitgelezen waarde naar 0 of 1
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
      case 15:
        Serial.print("sending state: ");
        leesSwitch();
        sending = SendJson(Switch);         // Stuur data van Switch naar PI
        Serial.print(sending);
        break;
      case 16:
        Serial.print("sending state: ");
        sending = SendJson(Ontvangst);      // Bij eerst contact tussen de devices verwacht de PI van elk id een bericht terug
        Serial.print(sending);
        break;
      default: break;
    }
  }
  else if(Ontvangst.cmd == "w") {
    // Spreek de juiste functie aan op basis van het id dat ontvangen is
    switch (Ontvangst.id) {
      case 18:
        wijzigKoeling();
        break;
      case 19:
        wijzigVentilator(); // wordt niet gebruikt
        break;
      default: break;
    }
  }
}

String SendJson(struct Data temp) {
// lees de waarden uit de struct en stop deze in een json string die wordt teruggestuurd.
  String returnVal;// bufferstring
  jsonBuffer.clear();
  JsonObject& msg = jsonBuffer.createObject();
  // zet de waarden in het json object goed.
  msg["id"].set(temp.id);
  msg["command"].set(temp.cmd);
  msg["value"].set(temp.state);
  // print voor verificatie en monitoring
  msg.printTo(Serial);
  msg.printTo(returnVal);
  return returnVal;// stuur de string terug
}
void recieveObject(JsonObject& item) {
//parse de informatie uit de Json variabele en stop deze in de ontvangst struct.
  Ontvangst.id = item["id"].as<int>();
  Ontvangst.cmd = item["command"].as<String>();
  Ontvangst.state = item["value"].as<int>();
}

void reconnect() {
// herstart de wifimodule en watch tot hij verbonden is.
  WiFi.begin(network, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("reconnecting");

  }
  Serial.println("reconnected");
}
