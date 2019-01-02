/*-----------------------------------
  Koelkast class decleration
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/
#ifndef KOELKAST_H
#define KOELKAST_H

#include "Device.h"
#include "../TCP.h"
#include <map>


class Koelkast : public Device{
public:
  Koelkast(int id_deur, int id_koeling);
  setTemp(int temprature);
  getTemp();
  std::map check();

private:
  TCP Device;
  extend std::map<int id, int prevVal> IO;




};


#endif
