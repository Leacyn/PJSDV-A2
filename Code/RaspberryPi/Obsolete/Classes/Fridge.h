/*-----------------------------------
  Fridge class decleration
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef FRIDGE_H
#define FRIDGE_H


#include <map>


class Fridge : public Device{
public:
  std::map check(std::map<int, int> IO);
};


#endif
