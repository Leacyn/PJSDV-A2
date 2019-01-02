/*-----------------------------------
  Schemerlamp class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef SCHEMERLAMP_H
#define SCHEMERLAMP_H

#include "Device.h"
#include <map>
#include "../fin/TCP.h"

class Schemerlamp : public Device {
public:
  Schemerlamp(char * );
  int[2] check();
private:
  TCP Device;
  extend std::map<int key, std::string type, int prevVal> IO;
};

#endif
