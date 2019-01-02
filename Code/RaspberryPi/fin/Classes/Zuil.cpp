/*-----------------------------------
  Zuil class Definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#include "Zuil.h"

Zuil::Zuil(char *ipaddress): Device(ipaddress){
  IO = std::map<int key, str::string type, int prevVal>{{8, "Sensor", 0}, {9, "Actuator", 0}, {10, "Sensor", 0}};

};

Zuil::~Zuil(){

}
