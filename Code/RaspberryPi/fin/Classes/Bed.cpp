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
      int check = device.sendRead(i->first)
      if(check != IO[i]){
<<<<<<< HEAD
        IO[i->first] = check;
=======
<<<<<<< HEAD
        IO[i->first] = check;
=======
>>>>>>> 736ebd4ef5f2767909c5c6e986829139228c989f
>>>>>>> 8f40e73975de47db25cdb8147593672472aa4d5a
        returnmap[i->first] = check;
      }
    }
      return returnmap;
}
