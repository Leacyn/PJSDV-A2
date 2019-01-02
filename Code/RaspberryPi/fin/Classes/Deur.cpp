/*-----------------------------------
  Deur class definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Deur.h"



Deur::Deur(char *ipaddress): Device(ipaddress){
 IO = std::map<int key,std::string type ,int lastVal> {{17,"Actuator",0},{18,"Actuator",0},{19,"Sensor",0}};


}


Deur::~Deur(){


}
