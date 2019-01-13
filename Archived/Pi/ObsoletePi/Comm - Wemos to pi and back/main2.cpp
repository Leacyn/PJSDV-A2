/* C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include "TCP.cpp"
//#include "DataBase.cpp"

/*Define SQL login data*/
#define PATH "tcp://127.0.0.1:3306"
#define USER "monitor"
#define PASSWD "100%Domotica"
#define DB "domotics"

/*Define WEMOS connection data*/
#define WEMOS_PORT 54000

char *wemosAddress = (char *)"192.168.1.120" /*"192.168.2.1" "192.168.43.52"*/;
int const maxSensor = 3;

using namespace std;

int main(int argc, char** argv){
	/*SETUP*/
	cout << endl;

	/*set up connection to database*/
//	DataBase sql(PATH, USER, PASSWD, DB);
	/*set up connection to WEMOS*/
	TCP wemos(wemosAddress, WEMOS_PORT);

	/*LOOP*/
//	while(1){
//	for(int i = 1; i <= maxSensor; i++){
//		if (int val = sql.queryValue("stateVal", "Sensor", i) != sql.queryValue("prevVal", "Sensor", i)){
//			sql.updateValue("Sensor", "prevVal", val, i);
//			//wemos.sendMsg("toggle");
//		}
//	}
//	}

	//sql.addUser("Willem", "Welkom123");
	//sql.queryUser();

//	sql.closeConnection();
	wemos.sendMsg(72,(char *)"w",250000);
	cout << wemos.recieveJson();
//	cout << wemos.receive() << endl;
	
	return 0;
}

