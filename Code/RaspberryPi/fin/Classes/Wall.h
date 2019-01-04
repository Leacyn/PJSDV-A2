/*-----------------------------------
  Muur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef WALL_H
#define WALL_H

#include "Device.h"
#include <map>
#include "../TCP.h"


class Wall : public Device{
public:
  std::map check(std::map<int, int> IO);

};

#endif
