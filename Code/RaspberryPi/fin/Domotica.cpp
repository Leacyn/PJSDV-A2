/*-----------------------------------
  Domotica main definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
  ----------------------------------*/

#include "Domotica.h"

using namespace std;

int main(int argc, char** argv){
	/*SETUP*/
	cout << endl;
  devices = map<int, Device> {
    {1,bed},{2,bed},{3,bed},
    {4,chair},{5,chair},
    {6,lamp},{7,lamp},
    {8,column},{9,column},{10,column},
    {11,wall},{12,wall},{13,wall},{14,wall},
    {15,fridge},{16,fridge},
    {17,door},{18,door},{19,door}
  };
  /*set up connection to database*/
	DataBase sql(PATH, USER, PASSWD, DB);
  Device dev = door;

	/*LOOP*/
	while(1){
    if(sql.checkStateChange()){
      for(map<int,int>::iterator it = sql.changes.begin(); it != sql.changes.end(); ++it){
        devices[it->first].changeValue(it->first,it->second);
        //clog << "value changed ID:'" << i << "' Value:'" << val << "'" << endl;
      }
    }
    for(map<int, Device>::iterator it = devices.begin(); it!=devices.end(); ++it){/*for each device*/
      if (it->second != dev){
        changes = it->second.check();
        for(map<int,int>::iterator i = changes.begin(); i!=changes.end(); ++i){/*for each sensor/ actuator*/
          sql.setPrevValSensor(i->first, i->second);
          sql.setStateValSensor(i->first, i->second);
        }
      }
      dev = it->second;
    }
	}
	sql.closeConnection();
	return 0;
}
