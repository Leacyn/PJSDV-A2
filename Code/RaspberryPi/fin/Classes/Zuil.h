/*-----------------------------------
  Zuil class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef ZUIL_H
#define ZUIL_H

#include "Device.h"
#include <map>
#include "../TPC.h"

class Zuil: public Device{
public:
  std::map check();
};

#endif
