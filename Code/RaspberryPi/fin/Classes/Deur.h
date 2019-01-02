/*-----------------------------------
  Deur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef DEUR_H
#define DEUR_H

#include "Device.h"
#include <map>
#include "../TCP.h"

class Deur : public Device{
public:
  Deur(char *ipaddress);
  std::map check();
private:
  TCP device;
  extern std::map<int key, std::string type, int prevVal> IO;
};

#endif
