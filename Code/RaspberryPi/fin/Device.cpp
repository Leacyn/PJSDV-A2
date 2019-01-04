/*-----------------------------------
  Device class definition
  version: 0.4
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#include "Device.h"


Device::Device(char *wemosAddress, std::string Name, std::vector<int> ids): ServerAddress(wemosAddress), Client(wemosAddress,PORT), name(Name), sensorIDs(ids){
}

Device::~Device(){

}


void Device::changeValue(int id, int value){
  Client.sendWrite(id, value);
  IO[id] = value;
}

std::map<int,int> Device::check(){
  std::map<int id, int val> returnmap;
  for(std::map<int, int>::iterator i = IO.begin(); i!=IO.end(); ++i){
    int check = device.sendRead(i->first)
    if(check != IO[i]){
      IO[i->first] = check;
      returnmap[i->first] = check;
    }
  }
    return returnmap;
}
