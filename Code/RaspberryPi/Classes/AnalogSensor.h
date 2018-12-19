#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

class AnalogSensor{
public:
  int getState(int id);
  AnalogSensor(int id);
private:
  int ID, State;
protected:

};
