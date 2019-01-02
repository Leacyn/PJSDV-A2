/*-----------------------------------
  Domotica main definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
  ----------------------------------*/

#include "Domotica.h"

//int const totalSensors = 19;
int const totaldevices = 7;

using namespace std;

int main(int argc, char** argv){
	/*SETUP*/
	cout << endl;
  deviceID = map<int, Device> {
    {1,bed},{2,bed},{3,bed},
    {4,chair},{5,chair},
    {6,lamp},{7,lamp},
    {8,column},{9,column},{10,column},
    {11,wall},{12,wall},{13,wall},{14,wall},
    {15,fridge},{16,fridge},
    {17,door},{18,door},{19,door}
  };
  int id = 0;
  /*set up connection to database*/
	DataBase sql(PATH, USER, PASSWD, DB);


	/*LOOP*/
	while(1){
    Device dev = door;
    for(std::map::iterator it = deviceID.begin(); it!=deviceID.end(); ++it){/*for each device ID*/

      if (int val = sql.queryValue("stateVal", "Sensor", it->first) != sql.queryValue("prevVal", "Sensor", it->first)){
        sql.updateValue("Sensor", "prevVal", val, it->first);
        devicesID[it->first].changeValue(it->first,val);
		  }
      if (it->second != dev){
        changes = it->second.check();
        for(std::map::iterator i = changes.begin(); i!=changes.end(); ++i){/*for each value change*/
          sql.updateValue("Sensor", "prevVal", i->second, i->first);
          sql.updateValue("Sensor", "stateVal", i->second, i->first);
        }
      }
    dev = it->second;
    }


	}

	sql.closeConnection();
	return 0;
}
