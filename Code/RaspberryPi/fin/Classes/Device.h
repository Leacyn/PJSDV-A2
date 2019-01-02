/*-----------------------------------
  Device class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef DEVICE_H
#define DEVICE_H

#define PORT 54000

#include "TCP.h"

class Device{

public:
  Device(std::string wemosAddress);
  changeValue(int id, int value);

private:

  std::string ServerAddress;
  TCP Client(ServerAddress, PORT);

protected:

};

#endif
