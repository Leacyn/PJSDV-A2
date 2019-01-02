/*-----------------------------------
  Schemerlamp class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef SCHEMERLAMP_H
#define SCHEMERLAMP_H

#include "Device.h"
#include <map>
#include "../TCP.h"

class Schemerlamp : public Device {
public:
  Schemerlamp(char * );
  std::map check();
private:
  TCP Device;
  extend std::map<int key, int prevVal> IO;
};

#endif
