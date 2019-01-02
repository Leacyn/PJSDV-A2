/*-----------------------------------
  Muur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef MUUR_H
#define MUUR_H

#include "Device.h"
#include <map>
#include "../fin/TCP.h"


class Muur : public Device{
public:
  Muur(char *ipaddress);
  int[2] check();
private:
  TCP Device;
  extend std::map<int key, std::string type, int prevVal> IO;
};

#endif
