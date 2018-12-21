/*-----------------------------------
  Schemerlamp class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef SCHEMERLAMP_H
#define SCHEMERLAMP_H

#include "Device.h"

class Schemerlamp : public Device {
public:
  Schemerlamp(int ID_led, int ID_Sensor);
  int[2] check();
private:
  std::map<int key, std::string type> IO;
};

#endif
