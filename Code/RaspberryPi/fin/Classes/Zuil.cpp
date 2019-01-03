/*-----------------------------------
  Zuil class Definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Zuil.h"

Zuil::Zuil(char *ipaddress): Device(ipaddress){
  IO = std::map<int key, int prevVal>{{8, 0}, {9, 0}, {10, 0}};

};

Zuil::~Zuil(){

}


std::map Zuil::check(){
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

void Zuil::changeValue(int id, int val){
  Client.sendWrite(id,val);
  IO[id] = val;

}
