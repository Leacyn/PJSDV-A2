/*-----------------------------------
  Schemerlamp class Definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Schemerlamp.h"


Schemerlamp::schemerlamp(char *ipaddress):Device(ipaddress){
  IO = std::map<int key, int prevVal>{{6, 0}, {7, 0}};


}
Schemerlamp::~Schemerlamp(){


}

std::map Schemerlamp::check(){
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

void Schemerlamp::changeValue(int id, int val){
  Client.sendWrite(id,val);
  IO[id] = val;
    
}
