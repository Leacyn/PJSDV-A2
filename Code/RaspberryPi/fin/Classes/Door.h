/*-----------------------------------
  Deur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef DOOR_H
#define DOOR_H

#include "Device.h"
#include <map>
#include "../TCP.h"

class DOOr : public Device{
public:
  std::map check();
};

#endif
