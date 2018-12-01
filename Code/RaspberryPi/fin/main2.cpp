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

using namespace std;

int main(int argc, char** argv){
	cout << endl;
	
	DataBase sql("PATH", "USER", "PASSWD","DB");

	sql.addUser("Willem", "Welkom123");
	sql.queryUser();

	sql.closeConnection();
	
	cout << endl;
	return 0;
}

