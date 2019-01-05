/*-----------------------------------
  Domotica main definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
  ----------------------------------*/

#include "Domotica.h"

using namespace std;

int main(int argc, char** argv){
	/*SETUP*/
	cout << endl;

  /*set up connection to database*/
	DataBase sql(PATH, USER, PASSWD, DB);

  vector<struct deviceData> data = sql.getDeviceData();
  int deviceAmount = 0;
  for (struct deviceData d : data){
    deviceAmount++;
    Device *dev = new Device (d.ipAddress.c_str(), d.name,d.IDs, d.idType);
    for (int id : d.IDs){
      deviceIDs.insert(pair<int, Device*>(id, dev));
    }
    devices.insert(pair<string, Device*>(d.name, dev));
	}
	clog << endl << "devices have been initialised" << endl << endl;

	/*LOOP*/
	while(1){
    if(sql.checkStateChange()){/*Returns true when changes have been made from website*/
      for(map<int,int>::iterator it = sql.changes.begin(); it != sql.changes.end(); ++it){/*all changes are set to the sql.changes map with id, value*/
				deviceIDs[it->first]->changeValue(it->first,it->second);	/*For every change in database, change value of device*/
        clog << "value changed ID:'" << it->first << "' Value:'" << it->second << "'" << endl;
      }
    }


    for(map<string, Device*>::iterator it = devices.begin(); it!=devices.end(); ++it){/*for each device*/
      changes = (it->second)->check();

  		for(map<int,int>::iterator i = changes.begin(); i!=changes.end(); ++i){/*for each sensor/ actuator*/
    		sql.setPrevValSensor(i->first, i->second);
    		sql.setStateValSensor(i->first, i->second);
      }
    }
  }
  sql.closeConnection();
	return 0;
}
