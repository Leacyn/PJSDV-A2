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



std::map Koelkast::check(){
  std::map<int id, int val> returnmap;
  for(std::map<int, int>::iterator i = IO.begin(); i!=IO.end(); ++i){
    int check = device.sendRead(i->first)
    if(check != IO[i]){
      IO[i->first] = check;
      returnmap[i->first] = check;
    }
  }
    return returnmap;  
}
