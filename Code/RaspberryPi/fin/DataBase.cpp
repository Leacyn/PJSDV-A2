/*-----------------------------------
  DataBase class Definition
  version: 0.1
  contributors:
  Stijn van Es 17018498
----------------------------------*/
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

vector<struct deviceData> DataBase::getDeviceData(){
	vector<struct deviceData> v;
	try{
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM Device");
		while (res->next()){
			struct deviceData data;
			data.ipAddress = res->getString("ipAddress").c_str();
			data.startId = res->getInt("startId");
			data.idAmount = res->getInt("idAmount");
			data.name = res->getString("name");
			v.push_back(data);
		}
	}
	delete res;
  delete stmt;
  } catch (sql::SQLException &e){
		sqlError(e);
	}
	return v;
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

void DataBase::reset(){
	try {
		stmt = con->createStatement();
		stmt->executeUpdate("UPDATE Sensor SET prevVal = stateVal");
		delete stmt;
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

int DataBase::checkStateChange(){
	changes.clear();
	try{
		/* Select Value + id from tabel where value changed */
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT id, stateVal FROM Sensor WHERE stateVal != prevVal");
		while (res->next()){
			changes.insert(pair<int, int>(res->getInt("id"),res->getInt("stateVal")));
		}
	}
	delete res;
  delete stmt;
  } catch (sql::SQLException &e){
		sqlError(e);
	}
	reset();
	if(changes.empty()){
		return 0;/*if no changes return 0*/
	}else{
		return 1;
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
  	cerr << "CRIT, SQLException in " << __FILE__;
  	cerr << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
  	cerr << "CRIT, " << e.what();
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
    		clog << "LOG, " << res->getString("username") << "\t" << res->getString("password") << endl;

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
