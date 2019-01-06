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
    Device *dev = new Device (d.ipAddress.c_str(), d.name,d.IDs);
    for (int id : d.IDs){
      deviceIDs.insert(pair<int, Device*>(id, dev));
    }
    devices.insert(pair<string, Device*>(d.name, dev));
	}
	clog << endl << "devices have been initialised" << endl << endl;

	/*LOOP*/
	while(1){
    if(sql.checkStateChange()){/*Returns true when changes have been made on website*/
      for(map<int,int>::iterator it = sql.changes.begin(); it != sql.changes.end(); ++it){/*all changes are set to the sql.changes map with id, value*/
				deviceIDs[it->first]->changeValue(it->first,it->second);	/*For every change in database, change value of device*/
        clog << "value changed ID:'" << it->first << "' Value:'" << it->second << "'" << endl;
      }
    }


    for(map<string, Device*>::iterator it = devices.begin(); it!=devices.end(); ++it){/*for each device*/
			saveChanges((it->second)->check());
			//changes = (it->second)->check();
			//changes = checkLogic(sql.getTypes(),changes);
  		// for(map<int,int>::iterator i = changes.begin(); i!=changes.end(); ++i){/*for each sensor/ actuator*/
    	// 	sql.setPrevValSensor(i->first, i->second);
    	// 	sql.setStateValSensor(i->first, i->second);
      // }
    }

		execute(logic(allChanges));
		allChanges.clear();
  }
  sql.closeConnection();
	return 0;
}

saveChanges(map<int, int> changes){
	map<int, string> names = sql.getNames();
  for(map<int, int>::iterator i = changes.begin(); i!=changes.end(); ++i){
    allChanges[names[i->first]]=changes[i->first];
  }
}

execute(map<string, int> IO){
	for(map<int, string>::iterator i = sql.getNames().begin(); i!=sql.getNames().end(); ++i){
		if (IO.count(i->second)>0){
			if (sql.getTypes()[i->first]=="actuator"){
				deviceIDs[i->first]->changeValue(i->first, IO[i->second]);
			}
			sql.setPrevValSensor(i->first, IO[i->second);
			sql.setStateValSensor(i->first, IO[i->second);
		}
	}
}

int toggle(string name){
	for(map<int, string>::iterator i = sql.getNames().begin(); i!=sql.getNames().end(); ++i){
		if(i->second == name){
			if (deviceIDs[i->first]->getValue(i->first)){
				return 0;
			}else{
				return 1;
			}
		}
	}
}
