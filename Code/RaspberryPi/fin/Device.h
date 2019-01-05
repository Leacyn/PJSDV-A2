/*-----------------------------------
  Device class decleration
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef DEVICE_H
#define DEVICE_H

#define PORT 54000

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "TCP.h"
#include "Classes/Default"

#include "Classes/Bed.h"
#include "Classes/Chair.h"
#include "Classes/Column.h"
#include "Classes/Door.h"
#include "Classes/Lamp.h"
#include "Classes/Fridge.h"
#include "Classes/Wall.h"


class Device{

public:
  Device(const char *wemosAddress,std::string Name, std::vector<int> ids);
  void changeValue(int id, int value);
  std::map<int,int> check();

private:
  std::map<int, int> IO;
  std::vector<int> sensorIDs;
  const char* ServerAddress;
  TCP Client;
  std::string name;
};

#endif
