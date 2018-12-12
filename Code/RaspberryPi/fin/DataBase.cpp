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

void DataBase::setStateValSensor(int id, int value){
        try {
                pstmt = con->prepareStatement("UPDATE Sensor SET stateVal = ? WHERE id = ?");
                pstmt->setInt(1, value);
                pstmt->setInt(2, id);
                pstmt->executeUpdate();
                delete pstmt;
        } catch (sql::SQLException &e) {
                sqlError(e);
        }
}


void DataBase::setPrevValSensor(int id, int value){
	try {
		pstmt = con->prepareStatement("UPDATE Sensor SET prevVal = ? WHERE id = ?");
		pstmt->setInt(1, value);
		pstmt->setInt(2, id);
    		pstmt->executeUpdate();
  		delete pstmt;
  	} catch (sql::SQLException &e) {
  		sqlError(e);
	}
}

int DataBase::sensorNewState(int id){
	int result;
	try{
		/* Select Value from tabel where id is id */
  		pstmt = con->prepareStatement("SELECT prevVal, stateVal FROM Sensor WHERE id = ?");
		pstmt->setInt(1, id);
  		res = pstmt->executeQuery();
		while (res->next()){
  			result = res->getInt("stateVal");
			if (result == res->getInt("prevVal")){
				result = 0;
			}
		}
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


