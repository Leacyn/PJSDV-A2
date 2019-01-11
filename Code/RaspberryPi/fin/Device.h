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
/*
Device is a class which specifies the device and its IO. Through this class, a connection is set up with each wemos
*/
class Device{
public:
  Device(const char *wemosAddress,std::string Name, std::vector<int> ids);
  void changeValue(int id, int value);
  int getValue(int id);
  std::map<int,int> check();
private:
  std::map<int, int> IO;
  std::vector<int> sensorIDs;
  const char* ServerAddress;
  TCP Client;
  std::string name;
};

#endif
