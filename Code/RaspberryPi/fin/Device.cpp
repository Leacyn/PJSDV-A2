/*-----------------------------------
  Device class definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

#include "Device.h"


Device::Device(const char *wemosAddress, std::string Name, std::vector<int> ids): ServerAddress(wemosAddress), Client(wemosAddress,PORT), sensorIDs(ids), name(Name){
  // switch(name){
  //   case "bed": Bed dev;
  //     break;
  //   case "chair": Chair dev;
  //     break;
  //   case "door": Door dev;
  //     break;
  //   case "lamp": Lamp dev;
  //     break;
  //   case "fridge": Fride dev;
  //     break;
  //   case "wall": Wall dev;
  //     break;
  //   case "column": Column dev;
  //     break;
  //   default: Default dev;
  //     cerr << "WARNING: No Logic Class Found For Type: " << name << ". ::Using Default::" << endl;
  //     break;
  // }
  std::map<int,int> tempmap;
  for(int i:sensorIDs){
    tempmap[i] = 0;
  }
  IO = tempmap;
  std::clog << name << " connected" << endl;
}



void Device::changeValue(int id, int value){
  Client.sendWrite(id, value);
  IO[id] = value;
}

std::map<int,int> Device::check(){
  std::map<int, int> returnmap;
  for(std::map<int, int>::iterator i = IO.begin(); i!=IO.end(); ++i){
    int check = Client.sendRead(i->first);
    if(check != IO[i->first]){
      IO[i->first] = check;
      returnmap[i->first] = check;
    }
  }
  //IO = dev.check(IO);
  return returnmap;
}
