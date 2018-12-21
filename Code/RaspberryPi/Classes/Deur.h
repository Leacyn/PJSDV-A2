/*-----------------------------------
  Deur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef DEUR_H
#define DEUR_H

#include "Device.h"
#include <map>

class Deur : public Device{
public:
  Deur(int ID_switch, int ID_servo);
  int[2] check();
private:
  std::map<int key, std::string type> IO;
};

#endif
