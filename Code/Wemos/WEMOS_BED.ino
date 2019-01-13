/*-----------------------------------
  Device Bed
  version: 0.4
  contributors: 2
  Jordy van der Wijngaard 12073997
  Vincent Geers 13009672
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
#define I2C_SDL  D1
#define I2C_SDA  D2

/*defining WPA login data for WiFi connection.*/
char* network = "MichielDeRouter";
char* pass =  "100%Domotica";

String sending = "";
String returnval = "";
WiFiServer wifiServer(PORT);
StaticJsonBuffer<200> jsonBuffer;

/*defining static ip information.*/
IPAddress ip(10, 5, 5, 101);
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

struct Data Ontvangst, drukSensor, Switch;
void initDruksensor();
void initSensoradres();
void leesSwitch();
void leesDruksensor();
void wijzigLed();

int currentState = 0;
int prevState = 0;

void setup(void)
{
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

  initDruksensor();
  initSensoradres();
}

void loop(void)
{
  Wire.begin();
  jsonBuffer.clear();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected trying to reconnect:");
    reconnect();
  }

  WiFiClient pi = wifiServer.available();

  leesSwitch();

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

void initDruksensor()
{
  pinMode(D0, INPUT);
  Ontvangst.state = 0;
  drukSensor.state = 0;
  Switch.state = 0;
}

void initSensoradres()
{
  // Zet ID's
  Switch.id = 2;
  drukSensor.id = 3;
}

void leesSwitch()
{
  /*
    Het idee hier is: Het uitlezen van de switch waaraan de led verbonden zit (Switch.state).

    De state van de switch wordt uitgelezen (Switch.state) en terug gestuurd naar de PI.
    Vervolgens moet de PI kijken of de vorige state anders is dan de huidige state. (Wel ervoor zorgen dat prevState == huidigeState na elke iteratie, want de led gaat alleen aan bij een hoge state)
    Op het moment dat datgene waar is dan geeft de PI de state van de led mee in een pakket aan de WEMOS.
    Deze status komt te staan in Ontvangst.state.

  */
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

void wijzigLed()
{
  /*
     Het idee hier is: het ontvangen van een state (Ontvangst.state) van de PI voor de led.

     Bovenstaande kan alleen gebeuren als er een state change is geweest op de switch (Switch.state).
     Deze state change verwerkt de PI en die bepaald daaruit wat er moet gebeuren. Dus die stuurt dan een
     pakket met de state die de led moet krijgen. In dit programma wordt deze state toegekend aan Ontvangst.state.

  */

  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet leds op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte((Ontvangst.state) << 4)); // zet led op basis van ontvangen state // dit is de ontvangen data in de 2de iteratie
  Wire.endTransmission();
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
      case 1:
        sending = SendJson(Ontvangst);
        Serial.print(sending);
        break;
      case 2:
        Serial.print("sending state:");
        leesSwitch();
        Switch.cmd = "r";
        sending = SendJson(Switch);
        Serial.print(sending);
        break;
      case 3:
        Serial.print("sending state:");
        leesDruksensor();
        drukSensor.cmd = "r";
        sending = SendJson(drukSensor);
        Serial.print(sending);
        break;
      default: break;
    }
  }
  else if (Ontvangst.cmd == "w") {
    // Spreek de juiste functie aan op basis van het id dat ontvangen is
    switch (Ontvangst.id) {
      case 1:
        Serial.print(Ontvangst.state);
        wijzigLed();
        break;
      default: break;
    }
  }
}

String SendJson(struct Data temp) {
  String returnVal;
  jsonBuffer.clear();
  JsonObject& msg = jsonBuffer.createObject();
  msg["id"].set(temp.id);
  msg["command"].set(temp.cmd);
  msg["value"].set(temp.state);
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
