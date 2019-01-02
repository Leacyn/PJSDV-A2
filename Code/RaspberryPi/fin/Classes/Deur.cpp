/*-----------------------------------
  Deur class definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Deur.h"



Deur::Deur(char *ipaddress): Device(ipaddress){
 IO = std::map<int key, int lastVal> {{17,0},{18,0},{19,0}};


}


Deur::~Deur(){


}




std::map Deur::check(){
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
