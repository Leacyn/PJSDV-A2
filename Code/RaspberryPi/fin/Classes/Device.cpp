/*-----------------------------------
  Device class definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Device.h"


Device::Device(char *wemosAddress, std::map<int,int> IOlist): ServerAddress(wemosAddress), Client(Server Address,PORT),IO(IOlist),{

}

Device::~Device(){

}


void Device::changeValue(int id, int value){
  Client.sendWrite(id, value);
}
