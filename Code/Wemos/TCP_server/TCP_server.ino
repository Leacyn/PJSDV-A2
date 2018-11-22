#include <ESP8266WiFi.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define PORT 54000

char* network = "Leacyn";
char* pass = "100%Domotica";
WiFiServer wifiServer(PORT);

void reconnect();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
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
    while (pi.connected()){
      while(pi.available()>0){
        char c = pi.read();
        Serial.write(c);
        //int temp = pi.write(c);
      }
      
    }

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


