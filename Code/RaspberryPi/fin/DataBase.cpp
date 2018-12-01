#include "DataBase.h"

using namespace std;

DataBase::DataBase(string path, string user, string password, string db){
	try {
		/* Create a connection */
  		driver = get_driver_instance();
  		con = driver->connect(path, user, password);
  		/* Connect to the MySQL domotics database */
  		con->setSchema(db);
	} catch (sql::SQLException &e) {
  		sqlError(e);
	}
}

void DataBase::updateValue(string table, string valueName, int value, int id){
	try {
		pstmt = con->prepareStatement("UPDATE ? SET ? = ? WHERE id = ?");
		pstmt->setString(1, table);
		pstmt->setString(2, valueName);
		pstmt->setInt(3, value);
		pstmt->setInt(4, id);
    	pstmt->executeUpdate();
  		delete pstmt;
  	} catch (sql::SQLException &e) {
  		sqlError(e);
	}
}

int DataBase::queryValue(string value, string table, int id){
	int result;	
	try{
		/* Select Value from tabel where id is id */
  		pstmt = con->prepareStatement("SELECT ? FROM ? WHERE id = ?");
  		pstmt->setString(1, value);
		pstmt->setString(2, table);
		pstmt->setInt(3, id);
  		res = pstmt->executeQuery();

  		/* Fetch in reverse = descending order! */
  		res->afterLast();
  		while (res->previous())
    			result = res->getInt(value);

		delete res;
  		delete pstmt;
  	} catch (sql::SQLException &e){
		sqlError(e);
	}
	return result;
}

void DataBase::sqlError(sql::SQLException e){
  	cerr << "# ERR: SQLException in " << __FILE__;
  	cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
  	cerr << "# ERR: " << e.what();
  	cerr << " (MySQL error code: " << e.getErrorCode();
  	cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
}

void DataBase::closeConnection(void){
	delete con;
	delete stmt;
	delete res;
	delete pstmt;
}

void DataBase::queryUser(void){
	try{
		/* Select in ascending order */
  		pstmt = con->prepareStatement("SELECT username, password FROM User ORDER BY username ASC");
  		res = pstmt->executeQuery();

  		/* Fetch in reverse = descending order! */
  		res->afterLast();
  		while (res->previous())
    		clog << res->getString("username") << "\t" << res->getString("password") << endl;

		delete res;
  		delete pstmt;
  	} catch (sql::SQLException &e){
		sqlError(e);
	}
}

void DataBase::addUser(string username, string password){
	try {
		pstmt = con->prepareStatement("INSERT INTO User(username, password) VALUES (?, ?)");
		pstmt->setString(1, username);
		pstmt->setString(2, password);
    	pstmt->executeUpdate();
  		delete pstmt;
  	} catch (sql::SQLException &e) {
  		sqlError(e);
	}
}


