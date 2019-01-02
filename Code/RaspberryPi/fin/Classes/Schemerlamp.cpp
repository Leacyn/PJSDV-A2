/*-----------------------------------
  Schemerlamp class Definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Schemerlamp.h"


Schemerlamp::schemerlamp(char *): beweginssensor(ID_Sensor), led(ID_led){
  IO = std::map<int key, std::string, int prevVal>{{6, "Actuator", 0}, {7, "Sensor", 0}};


}
Schemerlamp::~Schemerlamp(){


}
