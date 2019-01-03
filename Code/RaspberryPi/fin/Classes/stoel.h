/*-----------------------------------
  stoel class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef STOEL_H
#define STOEL_H

#include "Device.h"
#include <map>
#include "../TCP.h"

class Stoel: public Device{

public:
  Stoel(char *ipaddress);
  std::map check();
  void changeValue(int id, int val);
private:
  std::map<int key, int prevVal> IO;

};


#endif
