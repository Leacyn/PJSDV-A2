/*-----------------------------------
  Domotica includes
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

// #ifndef DOMOTICA_H
// #define DOMOTICA_H

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

/*Define SQL login data*/
#define DBPATH "tcp://127.0.0.1:3306"
#define USER "editor"
#define PASSWD "100%Domotics"
#define DB "domotics"

#define OFF 0
#define ON 1

// class Domotica{
// protected:
  std::map<int, Device*> deviceIDs;         /*id, device*/
  std::map<std::string, Device*> devices;   /*name, device*/
  std::map<std::string, int> allChanges;    /*subType, value*/

  int loop();
  int setup();

  /*start setup and loop
1. The main program starts with the setup
2. Loop runs continiously
Both defined in Domotica.cpp
  */
  int main(int argc, char** argv){if(setup())return loop();else return 0;}

  /*Initialise class - set up connection to database*/
  DataBase sqlDB(DBPATH, USER, PASSWD, DB);

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
//};

// #endif
