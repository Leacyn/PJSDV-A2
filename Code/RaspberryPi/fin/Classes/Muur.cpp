/*-----------------------------------
  Muur class definitions
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#include "Muur.h"


Muur::Muur(char *ipaddress): Device(ipaddress){
  IO = std::map<int key, std::string, int prevVal>{{11, "Sensor", 0}, {12,"Sensor",0}, {13,"Actuator",0}, {14, "Actuator", 0}};
  
}

Muur::~Muur(){

}
