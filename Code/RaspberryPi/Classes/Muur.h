/*-----------------------------------
  Muur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef MUUR_H
#define MUUR_H

#include "Device.h"


class Muur : public Device{
public:
  Muur(int ID_Venster, int ID_LDR);
  int[2] check();
private:
  std::map<int key, std::string type> IO;
};

#endif
