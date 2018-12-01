/* C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
#include "TCP.cpp"
#include "DataBase.cpp"

/*Define SQL login data*/
#define PATH "tcp://127.0.0.1:3306"
#define USER "monitor"
#define PASSWD "100%Domotica"
#define DB "domotics"

/*Define WEMOS connection data*/
#define WEMOS_PORT 54000

char const *wemosAddress = "192.168.2.1";


using namespace std;

int main(int argc, char** argv){
	/*SETUP*/
	cout << endl;
	
	/*set up connection to database*/
	DataBase sql(PATH, USER, PASSWD, DB);
	/*set up connection to WEMOS*/
	//TCP wemos(wemosAddress, WEMOS_PORT);
	
	/*LOOP*/
	while(1){
		for(int id = 1, id =< MAX_SENSOR, id++){
			if (int val = sql.queryValue("stateVal", "Sensor", id) != sql.queryValue("prevVal", "Sensor", id)){
				sql.updateValue("Sensor", "prevVal", val, id);
				//wemos.sendMsg("toggle");
			}
		}
	}
	
	//sql.addUser("Willem", "Welkom123");
	//sql.queryUser();

	sql.closeConnection();
	
	cout << endl;
	return 0;
}

