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

class DataBase
{
	public:
		std::map<int, int> changes;/*id,val*/
		std::map<int, std::string> getTypes();
		std::map<int, std::string> getNames();
		DataBase(std::string path, std::string user, std::string password, std::string db);
		void closeConnection(void);
		int checkStateChange();
		void setStateValSensor(int id, int value);
		void setPrevValSensor(int id, int value);
		std::vector<struct deviceData> getDeviceData();
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
