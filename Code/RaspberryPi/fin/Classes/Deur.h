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
#include "../fin/TCP.h"

class Deur : public Device{
public:
  Deur(char *ipaddress);
  int[2] check();
private:
  TCP device;
  extern std::map<int key, std::string type, int prevVal> IO;
};

#endif
