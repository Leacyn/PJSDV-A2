/*-----------------------------------
  Device Deur
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
#include <Servo.h>

#define PORT 54000
#define I2C_SDL    D1
#define I2C_SDA    D2

char* network = "MichielDeRouter";
char* pass =  "100%Domotica";
String sending = "";
String returnval = "";

WiFiServer wifiServer(PORT);
StaticJsonBuffer<200> jsonBuffer;
IPAddress ip(10, 5, 5, 107);
IPAddress GW(10, 5, 5, 1);
IPAddress netmask(255, 255, 255, 0);

void reconnect();
void recieveObject(JsonObject&);
String SendJson(struct Data temp);
void kiesSensor();
void leesSwitchbuit();

int currentState = 0;
int prevState = 0;

struct Data {
  int id;
  String cmd;
  int state;
};

Servo myservo;  // create servo object to control a servo
struct Data Ontvangst, switchBuiten, switchBinnen;

void wijzigServo();
void wijzigLed();
//void leesSwitchbin();
//void leesSwitchbuit();
void initSensoradres();


int pos = 0;    // variable to store the servo position

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

  myservo.attach(D5);  // attaches the servo on pin 9 to the servo object
}

void loop() {

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
        
        Serial.println("recieving: ");
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

void initSensoradres()
{
  // Zet ID's
  switchBinnen.id = 19;
  switchBuiten.id = 20;
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
      case 17:
        sending = SendJson(Ontvangst);
        Serial.print(sending);
      break;
      case 18:
        sending = SendJson(Ontvangst);
        Serial.print(sending);
      break;
      case 19:
        //leesSwitchbin();
        sending = SendJson(switchBinnen);
        Serial.print(sending);
        Serial.print("\n");
      break;
      case 20:
        leesSwitchbuit();
        sending = SendJson(switchBuiten);
        Serial.print(sending);
        Serial.print("\n");
      break;
      default: break;
    }
  }
  else if(Ontvangst.cmd == "w") {
    // Spreek de juiste functie aan op basis van het id dat ontvangen is
    switch (Ontvangst.id) {
      case 17:
        wijzigLed();
      break;
      case 18:
        wijzigServo();
      break;
      default: break;
    }
  }
}

void wijzigServo()
{
  if (Ontvangst.state == 1) {                    
    for (pos = 82; pos >= -30; pos -= 1) {        // deur openen als knop aan de buitenkant wordt ingedrukt
      // in steps of 1 degree
      myservo.write(pos);                        
      delay(10);
    }
  }
  
   if(Ontvangst.state == 0)
   {
      for (pos = -30; pos <= 82; pos += 1) {        // deur sluiten na 5s
      //Switch.state = 0;
      leesSwitchbuit();
      myservo.write(pos);
      }  
   }
}
// Nog doen!!
void wijzigLed()
{
  // to be continued
}

void leesSwitchbuit(){
  //Read PCA9554 outputs (IO40-IO3)
  Wire.beginTransmission(0x38);                   // kijken of knop wordt ingedrukt
  Wire.write(byte(0x00));
  Wire.endTransmission();
  
  Wire.requestFrom(0x38, 4);
  unsigned int answer = Wire.read();

  delay(20);

  currentState = answer % 2;

    if(currentState != prevState)
    {
      if(currentState)
      {
        switchBuiten.state = !switchBuiten.state;
      }
    }

    prevState = currentState;  
}

//void leesSwitchbin()
//{
//  //Read PCA9554 outputs (IO40-IO3)
//  Wire.beginTransmission(0x38);                   // kijken of knop wordt ingedrukt
//  Wire.write(byte(0x00));
//  Wire.endTransmission();
//  
//  Wire.requestFrom(0x38, 4);
//  unsigned int answer = Wire.read();
//
//  delay(20);
//
//  Switch.state = answer % 2; // convert uitgelezen waarde naar boolean //return deze naar PI  
//}

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
