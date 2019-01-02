/*-----------------------------------
  Stoel class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "stoel.h"


Stoel::Stoel(char *ipaddress): Device(ipaddress){
  IO = std::map<int key, std::string type, int prevVal>{{4,"Sensor",0},{5, "Actuator",0}};

}



Stoel::~Stoel(){




}
