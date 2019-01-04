/*-----------------------------------
  Koelkast class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef REFRIDGERATOR_H
#define REFRIDGERATOR_H

#include "Device.h"
#include "../TCP.h"
#include <map>


class refridgerator : public Device{
  std::map check();
};


#endif
