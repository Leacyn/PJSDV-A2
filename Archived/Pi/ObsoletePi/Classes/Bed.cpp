/*-----------------------------------
  Bed class definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

#include "Bed.h"


std::map Bed::check(std::map<int, int> IO){
  if (IO["switch"]){
    IO["led"]=1;
  }else{
    IO["led"]=0;
  }
  return IO;
}
