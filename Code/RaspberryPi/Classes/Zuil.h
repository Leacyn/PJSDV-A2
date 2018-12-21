/*-----------------------------------
  Zuil class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef ZUIL_H
#define ZUIL_H

#include "Device.h"
#include <map>

class Zuil: public Device{
public:
  Zuil(int ID_Beeper, int ID_rookmelder, int ID_Switch);
  int[2] check();
private:
  std::map<int key, std::string type> IO;

};

#endif
