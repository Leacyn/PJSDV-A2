/*-----------------------------------
  Muur class definitions
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Muur.h"


Muur::Muur(char *ipaddress): Device(ipaddress){
  IO = std::map<int key, int prevVal>{{11, 0}, {12,0}, {13,0}, {14, 0}};

}

Muur::~Muur(){

}

std::map Muur::check(){
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

void Muur::changeValue(int id, int val){
  Client.sendWrite(id,val);
  IO[id] = val;

}
