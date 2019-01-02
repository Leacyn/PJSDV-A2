/* C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include "TCP.cpp"
#include "DataBase.cpp"

/*Define SQL login data*/
#define PATH "tcp://127.0.0.1:3306"
#define USER "editor"
#define PASSWD "100%Domotics"
#define DB "domotics"

/*Define WEMOS connection data*/
#define WEMOS_PORT 54000

char *wemosAddress = (char *)"10.5.5.101" /*"10.5.5.101" "10.5.5.254"*/;
int const sensorAmount = 3;

using namespace std;

int main(int argc, char** argv){
	/*SETUP*/
	cout << endl;

	/*set up connection to database*/
	DataBase sql(PATH, USER, PASSWD, DB);
	clog << "LOG, Database connected" << endl;
	/*set up connection to WEMOS*/
	TCP wemos(wemosAddress, WEMOS_PORT);
	clog << "LOG, Wemos connected" << endl;

	/*LOOP*/
	while(1){
		for(int id = 1; id <= sensorAmount; id++){
			if (int val = sql.sensorNewState(id)){
				sql.setPrevValSensor(id, val);
				clog << "LOG, value changed ID:'" << id << "' Value:'" << val << "'" << endl;
				wemos.sendMsg(id,"w",val);
			}
		}
	}

	//sql.addUser("Willem", "Welkom123");
	//sql.queryUser();

	sql.closeConnection();
	clog << "CRIT, program stopped SQL connection closed" << endl;
//	wemos.sendMsg(72,(char *)"w",250000);
//	cout << wemos.recieveJson();
//	cout << wemos.receive() << endl;

	return 0;
}

