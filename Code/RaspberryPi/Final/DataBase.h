/*-----------------------------------
  DataBase class decleration
  version: 1.0
  contributors:
  Stijn van Es 17018498
----------------------------------*/

#ifndef DATABASE_H
#define DATABASE_H

#include "mysql_connection.h"
#include "deviceStruct.h"
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

/*
This class sets up a connection to the database. It also runs queries and updates the tables of this database.
*/
class DataBase
{
	public:
		std::map<int, int> changes;							/*map (id, val) of changes in database made by website*/

		DataBase(std::string path, std::string user, std::string password, std::string db); /*constructor*/

		std::map<int, std::string> getTypes();
		std::map<int, std::string> getNames();
		int getVal(std::string name);
		std::vector<struct deviceData> getDeviceData();

		void closeConnection(void);
		int checkStateChange();

		void setStateValSensor(int id, int value);
		void setPrevValSensor(int id, int value);
		void setSensorValue(int id, int value);

		void insertIntoSleep(int value);
		void insertIntoLog(std::string dev, std::string state);
	protected:
		std::map<int, std::string> types;
		std::map<int, std::string> names;
		sql::Driver *driver;
  	sql::Connection *con;
  	sql::Statement *stmt;
  	sql::ResultSet *res;
  	sql::PreparedStatement *pstmt;
		void reset();
  	void sqlError(sql::SQLException e);
};

#endif
