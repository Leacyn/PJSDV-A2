/*-----------------------------------
  Domotica main definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
  Stijn van Es 17018498
  ----------------------------------*/

#include "Domotica.h"
#include "Logic.cpp"

using namespace std;


int /*Domotica::*/setup(){
	cout << endl;

  vector<struct deviceData> data = sqlDB.getDeviceData();
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
	return 1;
}

int /*Domotica::*/loop(){
	while(1){
    if(sqlDB.checkStateChange()){/*Returns true when changes have been made on website*/
      for(map<int,int>::iterator it = sqlDB.changes.begin(); it != sqlDB.changes.end(); ++it){/*all changes are set to the sql.changes map with id, value*/
				if(sqlDB.getTypes()[it->first]=="actuator"){
					deviceIDs[it->first]->changeValue(it->first,it->second);	/*For every change in database, change value of device*/
				}
				clog << "value changed ID:'" << it->first << "' Value:'" << it->second << "'" << endl;
      }
    }
    for(map<string, Device*>::iterator it = devices.begin(); it!=devices.end(); ++it){/*check changesfor each device*/
			saveChanges((it->second)->check());/*Compile a map (alllChanges) with all changes from every device */
		}
		execute(logic(allChanges));/*execute all logic on the current changes and send changes to device*/
		allChanges.clear();
  }
  sqlDB.closeConnection();/*close sql connection if loop stops somehow*/
	return 0;
}

void /*Domotica::*/saveChanges(map<int, int> changes){
	map<int, string> names = sqlDB.getNames();
  for(map<int, int>::iterator i = changes.begin(); i!=changes.end(); ++i){
		if(sqlDB.getTypes()[i->first]=="sensor")
    	allChanges[names[i->first]]=changes[i->first];
  }
}

void /*Domotica::*/execute(map<string, int> IO){
	map<int,string> names = sqlDB.getNames();/*get map id, name */
	for(map<int, string>::iterator i = names.begin(); i!=names.end(); ++i){/*for each existing name in database*/
		if (IO.count(i->second)>0){/*if id corresponding to name occures in IO map*/
			if (sqlDB.getTypes()[i->first]=="actuator"){
				deviceIDs[i->first]->changeValue(i->first, IO[i->second]);/*send new value to device where id belongs to if id belongs to an actuator*/
			}
			sqlDB.setSensorValue(i->first, IO[i->second]);/*set new value to database*/
		}
	}
}

int /*Domotica::*/getCurrentTime(){
	int t = time(0);
	return (t%60)+(((t/60)%60)*60)+(((((t/60)/60)%24)+1)*60*60);/*return current time in seconds since 00:00*/
}

int /*Domotica::*/toggle(string name){
	int val = sqlDB.getVal(name);
	return !(val);/*return opposite of current state*/
}

void /*Domotica::*/logSleep(int val){
	sqlDB.insertIntoSleep(val);
}

void /*Domotica::*/logSwitch(string dev, string state){
	sqlDB.insertIntoLog(dev, state);
}
