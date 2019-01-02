/*-----------------------------------
  Bed class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef BED_H
#define BED_H

#include "Device.h"
#include "../fin/TCP.h"
#include <map>

class Bed : class Device{
public:
  Bed(char *ipaddress);
  int[2] check();
private:
  TCP device;
  extern std::map<int key, std::string type, int lastVal> IO;


#endif
