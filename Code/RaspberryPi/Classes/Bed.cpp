/*-----------------------------------
  Bed class definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/

#include "Bed.h"


Bed::Bed(int ID_Switch, int ID_Led,int ID_drukSensor):bedSwitch(ID_Switch), bedLED(ID_Led), DrukSensor(ID_drukSensor){


}


Bed::~Bed(){


}
