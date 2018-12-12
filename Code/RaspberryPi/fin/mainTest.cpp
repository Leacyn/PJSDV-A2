/* C++ includes */
#include <stdlib.h>
#include <iostream>
#include <string>
//#include "TCP.cpp"
#include "DataBase.cpp"

/*Define SQL login data*/
#define PATH "tcp://127.0.0.1:3306"
#define USER "editor"
#define PASSWD "100%Domotics"
#define DB "domotics"

/*Define WEMOS connection data*/
#define WEMOS_PORT 54000

char const *wemosAddress = "192.168.2.1";
int const maxSensor = 3;

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
		for(int i = 1; i <= maxSensor; i++){
			if (int val = sql.sensorNewState(i)){
				sql.setPrevValSensor(i, val);
				clog << "value changed ID:'" << i << "' Value:'" << val << "'" << endl;
				//wemos.sendMsg("toggle");
			}else{
			//cout << "value did not change" << endl;
			}

		}
	}

	//sql.addUser("Willem", "Welkom123");
	//sql.queryUser();

	sql.closeConnection();

	cout << endl;
	return 0;
}

