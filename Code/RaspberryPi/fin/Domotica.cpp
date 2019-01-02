/*-----------------------------------
  Domotica main definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
  ----------------------------------*/

#include "Domotica.h"

int const maxSensor = 3;

using namespace std;

int main(int argc, char** argv){
	/*SETUP*/
	cout << endl;

	/*set up connection to database*/
  devices = map<int, Device> {
    {1,bed},{2,bed},{3,bed},
    {4,chair},{5,chair},
    {6,lamp},{7,lamp},
    {8,column},{9,column},{10,column},
    {11,wall},{12,wall},{13,wall},{14,wall},
    {15,fridge},{16,fridge},
    {17,door},{18,door},{19,door}
  }
	DataBase sql(PATH, USER, PASSWD, DB);


	/*LOOP*/
	while(1){
    for(int i = 1; i <= maxSensor; i++){
	       if (int val = sql.queryValue("stateVal", "Sensor", i) != sql.queryValue("prevVal", "Sensor", i)){
			       sql.updateValue("Sensor", "prevVal", val, i);
		     }
	  }
	}

	sql.closeConnection();
	return 0;
}
