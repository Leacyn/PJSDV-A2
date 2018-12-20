/*-----------------------------------
  TrendSensor class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef TRENDSENSOR_H
#define TRENDSENSOR_H

#include "AnalogSensor.h"

class TrendSensor: public AnalogSensor{
public:
  int logState(int id);

};
