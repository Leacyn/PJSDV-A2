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

/*set up connection to database*/
DataBase sqlDB(PATH, USER, PASSWD, DB);

int main(int argc, char** argv){
	/*SETUP*/
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

	/*LOOP*/
	while(1){
    if(sqlDB.checkStateChange()){/*Returns true when changes have been made on website*/
      for(map<int,int>::iterator it = sqlDB.changes.begin(); it != sqlDB.changes.end(); ++it){/*all changes are set to the sql.changes map with id, value*/
				if(sqlDB.getTypes()[it->first]=="actuator"){
					deviceIDs[it->first]->changeValue(it->first,it->second);	/*For every change in database, change value of device*/
				}
				clog << "value changed ID:'" << it->first << "' Value:'" << it->second << "'" << endl;
      }
    }
    for(map<string, Device*>::iterator it = devices.begin(); it!=devices.end(); ++it){/*for each device*/
			saveChanges((it->second)->check());
		}
		execute(logic(allChanges));
		allChanges.clear();
  }
  sqlDB.closeConnection();
	return 0;
}

void saveChanges(map<int, int> changes){
	map<int, string> names = sqlDB.getNames();
  for(map<int, int>::iterator i = changes.begin(); i!=changes.end(); ++i){
		if(sqlDB.getTypes()[i->first]=="sensor")
    	allChanges[names[i->first]]=changes[i->first];
  }
}

void execute(map<string, int> IO){
	map<int,string> names = sqlDB.getNames();
	for(map<int, string>::iterator i = names.begin(); i!=names.end(); ++i){
		if (IO.count(i->second)>0){
			if (sqlDB.getTypes()[i->first]=="actuator"){
				deviceIDs[i->first]->changeValue(i->first, IO[i->second]);
			}
			sqlDB.setSensorValue(i->first, IO[i->second]);
		}
	}
}

int toggle(string name){
	map<int,string> names = sqlDB.getNames();
	for(map<int, string>::iterator i = names.begin(); i!=names.end(); ++i){
		if(i->second == name){
			return !(deviceIDs[i->first]->getValue(i->first));
			// if (deviceIDs[i->first]->getValue(i->first)){
			// 	return 0;
			// }else{
			// 	return 1;
			// }
		}
	}
}

void logSleep(int val){

}
