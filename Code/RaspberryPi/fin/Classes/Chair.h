/*-----------------------------------
  stoel class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef CHAIR_H
#define CHAIR_H

#include "Device.h"
#include <map>
#include "../TCP.h"

class Chair: public Device{

public:
  std::map check();


};


#endif
