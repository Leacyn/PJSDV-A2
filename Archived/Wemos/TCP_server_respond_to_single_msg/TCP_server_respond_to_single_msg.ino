#include <ESP8266WiFi.h>
#include <Wire.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 54000

char* network = /*"MichielDeRouter"*/"Leacyn";
char* pass =  "100%Domotica";
int written = 0;
WiFiServer wifiServer(PORT);
struct tcpData {
  int id;
  char command;
  int value;
} tcpData;
struct tcpData item;

void reconnect();
unsigned int ReadAnalog();
void serialiser();
int deserialise(struct tcpData*, char []);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("setting up");
//
//  WiFi.mode(WIFI_STA);
  WiFi.softAPdisconnect(true);
  WiFi.disconnect(true);
  WiFi.begin(network, pass);
  Serial.println("connecting");

  while (WiFi.status() != WL_CONNECTED)
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
  char *c;
  struct tcpData *msg;
  msg = &item;
  //  msg->id = 0;
  //  msg->command = '0';
  //  msg->value = 0;

  // put your main code here, to run repeatedly:

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Disconnected trying to reconnect:");
    reconnect();
  }

  WiFiClient pi = wifiServer.available();

 
  int i = 0;
  if (pi) {
    Serial.println("client connected");
    while (pi.connected()) {
      while (pi.available() > 0) {
       char s[64] = {pi.read()};
       if(i==1) c = s;
      i++;
      Serial.println(s);
      }
      //        char s[1024] ={pi.read()};
      //        c = s;
      //        Serial.println(*c);
      //
     
       //       deserialise(msg, c);
      //
              Serial.println(msg->id);
              Serial.println(msg->command);
              Serial.println(msg->value);
      //         for(int i=0;i<sizeof(struct tcpData);i++){
      //          Serial.print((char)*(msg+i),HEX);
      //        }
      
      pi.print("Hello from server \n");
      //        int i = 0;
      //        while( i<1280){
      //         pi.write(s[i]);
      //         i++;
      //        }
      //        //pi.write(s);
      //      }
    }
    pi.stop();
    Serial.println("client disconnected");
  }
  //    Serial.println(written);

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
  Serial.print("analog in 0: ");
  Serial.println(value);

  return value;
}

int deserialise(struct tcpData* msg, char Data[] ) {
  int *i = (int *)Data;
  Serial.println(*i + "Data:" + *Data );
  msg->id = *i; i++;
  Serial.println(*i);
  msg->value = *i;i++;
  Serial.println(*i);
  char *q = (char*)i;
  msg->command = *q;
  Serial.println(*i);

  return 0;
}
