/*-----------------------------------
  Deur class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef DEUR_H
#define DEUR_H

#include "Device.h"


class Deur : public Device{
public:
  Deur(int ID_switch, int ID_servo);

private:
  Swtich doorSwitch;
  Actuator doorServo;
protected:
};

#endif
