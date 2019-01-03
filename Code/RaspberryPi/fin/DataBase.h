/*-----------------------------------
  Zuil class decleration
  version: 0.1
  contributors:
  Stijn van Es 17018498
----------------------------------*/

#ifndef DATABASE_H
#define DATABASE_H

#include "mysql_connection.h"
#include <map>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DataBase
{
	public:
		DataBase(std::string path, std::string user, std::string password, std::string db);
		void closeConnection(void);
		int checkStateChange();
		void setStateValSensor(int id, int value);
		void setPrevValSensor(int id, int value);
		int sensorNewState(int id);

		void addUser(std::string username, std::string password);
		void queryUser(void);
	protected:
		std::map<int id, int val> changes;
		sql::Driver *driver;
  	sql::Connection *con;
  	sql::Statement *stmt;
  	sql::ResultSet *res;
  	sql::PreparedStatement *pstmt;
  	void sqlError(sql::SQLException e);
};

#endif
