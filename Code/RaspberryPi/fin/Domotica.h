/*-----------------------------------
  Domotica includes
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

/* C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include "deviceStruct.h"
#include "Device.h"
#include "DataBase.h"

/*Define SQL login data*/
#define PATH "tcp://127.0.0.1:3306"
#define USER "editor"
#define PASSWD "100%Domotics"
#define DB "domotics"

//DataBase sqlDB;
std::map<int, Device*> deviceIDs;    /*id, device*/
std::map<std::string, Device*> devices;   /*name, device*/
std::map<std::string, int> allChanges;         /*subType, value*/

void saveChanges(std::map<int, int> changes);
void execute(std::map<std::string, int> IO);
int toggle(std::string name);
std::map<std::string, int> logic(std::map<std::string, int> IO);

//#include "Logic.h"
