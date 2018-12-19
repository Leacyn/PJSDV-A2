#ifndef TRENDSENSOR_H
#define TRENDSENSOR_H

#include "AnalogSensor.h"

class TrendSensor: public AnalogSensor{
public:
  int logState(int id);

};
