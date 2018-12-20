/*-----------------------------------
  Bed class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef BED_H
#define BED_H

#include "Device.h"
#include "Switch.h"
#include "Actuator.h"
#include "AnalogSensor.h"
#include "TrendSensor.h"

class BED : class Device{
public:
  BED(int ID_Switch, int ID_Led, int ID_drukSensor);

private:
  Switch bedSwitch;
  Actuator bedLED;
  TrendSensor DrukSensor;

};


#endif
