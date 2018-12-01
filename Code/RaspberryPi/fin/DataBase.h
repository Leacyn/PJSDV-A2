#ifndef DATABASE_H
#define DATABASE_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DataBase
{
	public:
		DataBase(std::string path, std::string user, std::string password, std::string db);
		int queryValue(std::string value, std::string table, int id);
		void updateValue(std::string table, std::string valueName, int value, int id);
		void closeConnection(void);
		
		void addUser(std::string username, std::string password);
		void queryUser(void);
	protected:
		sql::Driver *driver;
  		sql::Connection *con;
  		sql::Statement *stmt;
  		sql::ResultSet *res;
  		sql::PreparedStatement *pstmt;
  		void sqlError(sql::SQLException e);
};

#endif


