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
#include "../fin/TCP.h"

class Stoel: public Device{

public:
  Stoel(char *ipaddress);
  int[2] check();
private:
  TCP Device;
  std::map<int key, std::string type, int prevVal> IO;

};


#endif
