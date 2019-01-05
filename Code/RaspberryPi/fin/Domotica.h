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
#include "deviceStruct.h"
//#include "Device.h"
#include "DataBase.h"

/*Define SQL login data*/
#define PATH "tcp://127.0.0.1:3306"
#define USER "monitor"
#define PASSWD "100%Domotica"
#define DB "domotics"

std::map<int id, Device dev> deviceIDs;
std::map<string name, Device dev> devices;
std::map<int id, int val> changes;
