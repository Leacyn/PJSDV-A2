/*-----------------------------------
  Koelkast class Definiiton
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Koelkast.h"




Koelkast::Koelkast(char *ipaddress):Device(ipaddress) {
  IO = std::map<int key, std::string type , int prevVal>{{15, "Sensor", 0},{16, "Actuator",0}};

}


Koelkast::~Koelkast(){


}
