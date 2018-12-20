/*-----------------------------------
  Zuil class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef ZUIL_H
#define ZUIL_H

#include "Device.h"
#include "Switch.h"
#inlcude "Actuator.h"
#include "AnalogSensor.h"

class Zuil: public Device{
public:
  Zuil(int ID_Beeper, int ID_rookmelder, int ID_Switch);
private:
  AnalogSensor Rookmelder;
  Switch zuilSwitch;
  Actuator Beeper;
protected:
};

#endif
