#include <ESP8266WiFi.h>
#include <Wire.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define PORT 54000

char* network = "MichielDeRouter"/*"Leacyn"*/;
char* pass = "100%Domotica";
int written = 0;
WiFiServer wifiServer(PORT);

void reconnect();
unsigned int ReadAnalog();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  Serial.println("setting up");

  WiFi.begin(network,pass);
  Serial.println("connecting");

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("---------------------------------------------");
  Serial.print("Connected to wifi. Ip address: ");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Disconnected trying to reconnect:");
    reconnect();
  }
  
  WiFiClient pi = wifiServer.available();
  
   
  if(pi){
    Serial.println("client connected");
    while (pi.connected()){
      while(pi.available()>0){  
        char s[1280] = {pi.read()};
        Serial.write(s);

        pi.print("Hello from Server");
//        int i = 0;
//        while( i<1280){
//         pi.write(s[i]);
//         i++; 
//        }
//        //pi.write(s);

      }
       
    }
//    Serial.println(written);
    pi.stop();
    Serial.println("client disconnected");
  }
}


void reconnect(){
  WiFi.begin(network, pass);
    while(WiFi.status() != WL_CONNECTED){
       delay(1000);
       Serial.println("reconnecting");
       
    }
    Serial.println("reconnected");  
}

unsigned int ReadAnalog(){
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));  
  Wire.endTransmission(); 
  
  unsigned int value = 0;
  Wire.requestFrom(0x36,4);   
  value = Wire.read()&0x03;  
  value = value<<8;
  value = value|Wire.read();  
  Serial.print("analog in 0: ");
  Serial.println(value);  

  return value;
}
