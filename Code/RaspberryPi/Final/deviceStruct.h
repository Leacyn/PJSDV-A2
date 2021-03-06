/*-----------------------------------
  DeviceData struct definition
  version: 1.0
  contributors:
  Stijn van Es 17018498
  ----------------------------------*/
#ifndef DEVICEDATA_H
#define DEVICEDATA_H

#include <string>
#include <vector>

/*struct with data for a device*/
struct deviceData{
  std::string name;
  std::vector<int> IDs;
  std::string ipAddress;
};

#endif
