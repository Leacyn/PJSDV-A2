/*-----------------------------------
  Bed class definition
  version: 0.3
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

#include "Bed.h"


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
