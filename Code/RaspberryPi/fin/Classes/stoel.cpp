/*-----------------------------------
  Stoel class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "stoel.h"


Stoel::Stoel(char *ipaddress): Device(ipaddress){
  IO = std::map<int key, int prevVal>{{4,0},{5,0}};

}



Stoel::~Stoel(){




}


std::map Stoel::check(){
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

void Stoel::changeValue(int id, int val){
  Client.sendWrite(id,val);
  IO[id] = val;

}
