/*-----------------------------------
  Device class definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

#include "Device.h"

/*Constructor, initialize attributes*/
Device::Device(const char *wemosAddress, std::string Name, std::vector<int> ids): ServerAddress(wemosAddress), Client(wemosAddress,PORT), name(Name), sensorIDs(ids){
  std::map<int,int> tempmap;
  for(int i:sensorIDs){ /*set value is 0 for every id belonging to this device*/
    tempmap[i] = 0;
  }
  IO = tempmap;
  std::cout << name << " initialised" << std::endl;
}


/*send value to actuator*/
void Device::changeValue(int id, int value){
  Client.sendWrite(id, value);
  IO[id] = value;/*update value table*/
}

/*check value of every sensor of current device*/
std::map<int,int> Device::check(){
  std::map<int, int> returnmap;
  for(std::map<int, int>::iterator i = IO.begin(); i!=IO.end(); ++i){/*for every id of current device*/
    int check = Client.sendRead(i->first);/*send read request*/
    if(check != IO[i->first]){
      IO[i->first] = check;/*update value table for every change*/
      std::clog << "received change: " << IO[i->first] << std::endl;
      returnmap[i->first] = check;
    }
  }
  return returnmap;/*return map (id, val) with changes only*/
}

int Device::getValue(int id){
  return IO[id];
}
