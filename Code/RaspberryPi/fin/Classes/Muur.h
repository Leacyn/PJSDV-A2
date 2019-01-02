/*-----------------------------------
  Muur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef MUUR_H
#define MUUR_H

#include "Device.h"
#include <map>
#include "../TCP.h"


class Muur : public Device{
public:
  Muur(char *ipaddress);
  std::map check();
private:
  TCP Device;
  extend std::map<int key, int prevVal> IO;
};

#endif
