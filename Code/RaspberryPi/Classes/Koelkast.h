/*-----------------------------------
  Koelkast class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef KOELKAST_H
#define KOELKAST_H

#include "Device.h"
#include "Koelelement.h"
#include "Switch.h"


class Koelkast : public Device{
public:
Koelkast(int id_deur, int id_koeling);
setTemp(int temprature);
getTemp();
getDoor();

private:
Koelelement koeling;
Switch deursensor;

protected:


};


#endif
