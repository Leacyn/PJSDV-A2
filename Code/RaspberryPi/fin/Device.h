/*-----------------------------------
  Device class decleration
  version: 0.4
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef DEVICE_H
#define DEVICE_H

#define PORT 54000

#include "TCP.h"

class Device{

public:
  Device(char *wemosAddress, int startID, int sensorAmount);
  void changeValue(int id, int value);
  std::map<int,int> check();

private:
  std::map<int, int> IO;
  char* ServerAddress;
  TCP Client;

protected:

};

#endif
