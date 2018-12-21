/*-----------------------------------
  Bed class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef BED_H
#define BED_H

#include "Device.h"
#include <map>

class BED : class Device{
public:
  BED(int ID_Switch, int ID_Led, int ID_drukSensor);
  int[2] check();
private:
  std::map<int key, std::string type> IO;


#endif
