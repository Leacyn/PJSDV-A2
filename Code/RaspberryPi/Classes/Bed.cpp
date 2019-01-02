/*-----------------------------------
  Bed class definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

#include "Bed.h"


Bed::Bed(char *ipaddress):Device(ipaddress){
  IO = std::map<int, std::string,int> {{1,"Sensor",0},{2,"Actuator",0},{3,"Sensor",0}};
}


Bed::~Bed(){


}
