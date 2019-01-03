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

  /*set up connection to database*/
	DataBase sql(PATH, USER, PASSWD, DB);

  vector<struct deviceData> data = sql.getDeviceData();
  int deviceAmount = 0;
  for(struct deviceData i : data){/*create device for each device in the database*/
    deviceAmount ++;
    Device dev(i.ipAddress,i.startId,i.idAmount);
    vector<int> ids = dev.getIDs();
    for (int id : ids){
      deviceIDs.insert(pair<int, Device>(id,dev));
    }
    devices.insert(pair<string, Device>(i.name,dev));
  }

	/*LOOP*/
	while(1){
    if(sql.checkStateChange()){
      for(map<int,int>::iterator it = sql.changes.begin(); it != sql.changes.end(); ++it){
        devices[it->first].changeValue(it->first,it->second);
        //clog << "value changed ID:'" << i << "' Value:'" << val << "'" << endl;
      }
    }


    for(map<int, Device>::iterator it = deviceIDs.begin(); it!=deviceIDs.end(); ++it){/*for each device*/
      changes = it->second.check();
      for(map<int,int>::iterator i = changes.begin(); i!=changes.end(); ++i){/*for each sensor/ actuator*/
        sql.setPrevValSensor(i->first, i->second);
        sql.setStateValSensor(i->first, i->second);
      }
    }


  }
  sql.closeConnection();
	return 0;
}
