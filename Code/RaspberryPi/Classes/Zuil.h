/*-----------------------------------
  Zuil class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef ZUIL_H
#define ZUIL_H

#include "Device.h"
#include <map>
#include "../fin/TPC.h"

class Zuil: public Device{
public:
  Zuil(char *ipaddress);
  int[2] check();
private:
  TCP Device;
  std::map<int key, std::string type> IO;

};

#endif
