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
private:
  Actuator Venster;
  AnalogSensor LDR;

protected:


};

#endif
