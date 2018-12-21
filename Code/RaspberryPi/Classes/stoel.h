/*-----------------------------------
  stoel class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef STOEL_H
#define STOEL_H

#include "Device.h"

class Stoel: public Device{

public:
  Stoel(int ID_trilmotor, ID_drukSensor);

private:
  Actuator trilMotor;
  AnalogSensor drukSensor;

protected:

};


#endif
