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
