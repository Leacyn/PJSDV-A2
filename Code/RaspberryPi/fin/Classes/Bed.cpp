/*-----------------------------------
  Bed class definition
  version: 0.3
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

#include "Bed.h"


Bed::Bed(char *ipaddress):Device(ipaddress){
  IO = std::map<int id, int prevVal> {{1,0},{2,0},{3,0}};
}


Bed::~Bed(){


}

std::map Bed::check(){
    std::map<int id, int val> returnmap;
    for(std::map<int, int>::iterator i = IO.begin(); i!=IO.end(); ++i){
      int check = Client.sendRead(i->first)
      if(check != IO[i]){
        IO[i->first] = check;
        returnmap[i->first] = check;
      }
    }
      return returnmap;
}


void Bed::changeValue(int id, int val){
  Client.sendWrite(id,val);
  IO[id] = val;

}
