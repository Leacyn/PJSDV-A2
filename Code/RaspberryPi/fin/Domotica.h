/*-----------------------------------
  Domotica includes
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

#ifndef DOMOTICA_H
#define DOMOTICA_H

/* C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <time.h>
#include "deviceStruct.h"
#include "Device.h"
#include "DataBase.h"


#define OFF 0
#define ON 1

class Domotica{
public:
  Domotica(std::string path, std::string user, std::string pass, std::string db);
  int loop();
  int setup();
protected:
  std::map<int, Device*> deviceIDs;         /*id, device*/
  std::map<std::string, Device*> devices;   /*name, device*/
  std::map<std::string, int> allChanges;    /*subType, value*/

  DataBase sqlDB;

  int getCurrentTime();
  void logSwitch(std::string dev, std::string state);
  void logSleep(int val);
  void saveChanges(std::map<int, int> changes);
  void execute(std::map<std::string, int> IO);
  int toggle(std::string name);
  std::map<std::string, int> logic(std::map<std::string, int> IO);

  /*logic variables*/
  int startedSitting=0;
  int sitting = 0;
  int fridgeOpen = 0;
  int fridgeOpeningTime =0;
  int tooLong = 0;
  int timeOn = 0;
  int flagLDRled = 0;
  int flagLDRwindow = 0;
};

#endif
