/*-----------------------------------
  Domotica includes
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
----------------------------------*/

/* C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include "DataBase.cpp"
#include "Classes/Bed.h"
#include "Classes/Deur.h"
#include "Classes/Koelkast.h"
#include "Classes/Muur.h"
#include "Classes/Schemerlamp.h"
#include "Classes/Stoel.h"
#include "Classes/zuil.h"

/*Define SQL login data*/
#define PATH "tcp://127.0.0.1:3306"
#define USER "monitor"
#define PASSWD "100%Domotica"
#define DB "domotics"

Koelkast fridge("10.5.5.101");
Bed bed("10.5.5.102");
Deur door("10.5.5.103");
Muur wall("10.5.5.104");
Schemerlamp lamp("10.5.5.105");
Stoel chair("10.5.5.106");
zuil column("10.5.5.107");
