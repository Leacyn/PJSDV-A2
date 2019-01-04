/*-----------------------------------
  Bed class decleration
  version: 0.3
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef BED_H
#define BED_H

#include "Device.h"
#include "../TCP.h"
#include <map>

class Bed : class Device{
public:
  std::map check(std::map<int, int> IO);
}
