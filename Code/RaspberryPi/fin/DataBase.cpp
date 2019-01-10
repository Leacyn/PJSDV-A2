/*-----------------------------------
  DataBase class Definition
  version: 1.0
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
		return;
	}
	clog << "Database connected" << endl;
}

vector<struct deviceData> DataBase::getDeviceData(){
	vector<struct deviceData> v;
	try{
		/*query all sensor and device data*/
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT Sensor.id AS sensor_id, Sensor.type AS type, CONCAT(Devices.name,\"_\",Sensor.sub_type) AS name, Devices.name AS device, Devices.ipAddress AS ip FROM Sensor INNER JOIN Devices ON Sensor.device = Devices.name ORDER BY name ASC");

		string prevDev = "";
		string IP;
		vector<int> IDs;


		while(res->next()){/*for every entry in the Sensor table*/
			string currDev = res->getString("device").c_str();
			if (prevDev == "" || prevDev!=currDev){
				if (prevDev != ""){
					struct deviceData data;/*create a DataStruct and put it inn vector v*/
					data.name = prevDev;
					data.ipAddress = IP;
					data.IDs = IDs;
					v.push_back(data);
					IDs.clear();
				}
				IP = res->getString("ip").c_str();
			}
			names[res->getInt("sensor_id")]=res->getString("name").c_str();
			types[res->getInt("sensor_id")]=res->getString("type").c_str();
			IDs.push_back(res->getInt("sensor_id")); /*get every id per entry in sensor*/
			prevDev = currDev;
		}
		struct deviceData finalData;
		finalData.name = prevDev;
		finalData.ipAddress = IP;
		finalData.IDs = IDs;
		v.push_back(finalData);/*put last entry in vector*/
		delete res;
  	delete stmt;
  }catch(sql::SQLException &e){
		sqlError(e);
	}
	return v;
}



void DataBase::setStateValSensor(int id, int value){
	try {
		/*edit value where id*/
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
		/*set all previous values in database to current state*/
		stmt = con->createStatement();
		stmt->executeUpdate("UPDATE Sensor SET prevVal = stateVal");
		delete stmt;
	} catch (sql::SQLException &e) {
		sqlError(e);
	}
}

void DataBase::insertIntoSleep(int value){
	try{
		/*insert new log entry into Sleep*/
		pstmt = con->prepareStatement("insert into Sleep (value) VALUES (?)");
		pstmt->setInt(1, value);
		pstmt->execute();
		delete pstmt;
	} catch (sql::SQLException &e) {
  	//sqlError(e);
	}
}

void DataBase::insertIntoLog(string dev, string state){
	try{
		/*insert new log entry*/
		pstmt = con->prepareStatement("insert into Log (device, state) VALUES (?, ?)");
		pstmt->setString(1, dev);
		pstmt->setString(2, state);
		pstmt->execute();
		delete pstmt;
	} catch (sql::SQLException &e) {
		//sqlError(e);
	}
}

void DataBase::setSensorValue(int id, int value){
	try {
		/*edit current state value and previous state value where id*/
		pstmt = con->prepareStatement("UPDATE Sensor SET stateVal = ?, prevVal = ? WHERE id = ?");
		pstmt->setInt(1, value);
		pstmt->setInt(2, value);
		pstmt->setInt(3, id);
    pstmt->executeUpdate();
  	delete pstmt;
  } catch (sql::SQLException &e) {
  	sqlError(e);
	}
}

void DataBase::setPrevValSensor(int id, int value){
	try {
		/*edit previous state value where id*/
		pstmt = con->prepareStatement("UPDATE Sensor SET prevVal = ? WHERE id = ?");
		pstmt->setInt(1, value);
		pstmt->setInt(2, id);
    pstmt->executeUpdate();
  	delete pstmt;
  } catch (sql::SQLException &e) {
  	sqlError(e);
	}
}

int DataBase::getVal(string name){
	/*get current sensor value where <device name>_<subtype>*/
	int result;
	try {
		pstmt = con->prepareStatement("select stateVal from Sensor where CONCAT(device,\"_\",sub_type) = ?");
		pstmt->setString(1, name);
		res = pstmt->executeQuery();
		while (res->next()){
			//changes.insert(pair<int, int>(res->getInt("id"),res->getInt("stateVal")));
			result = res->getInt("stateVal");
		}
		delete pstmt;
	} catch (sql::SQLException &e) {
		sqlError(e);
	}
	return result;
}

int DataBase::checkStateChange(){
	changes.clear();/*remove old changes*/
	try{
		/*get value where current value differs from previous value*/
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT id, stateVal FROM Sensor WHERE stateVal != prevVal");
		while (res->next()){
			changes.insert(pair<int, int>(res->getInt("id"),res->getInt("stateVal")));/*insert id, current value into changes map*/
		}
		delete res;
  	delete stmt;
  } catch (sql::SQLException &e){
		sqlError(e);
	}
	reset();/*set previous value to current value*/
	if(changes.empty()){
		return 0;/*if no changes occured return 0 else return 1*/
	}else{
		return 1;
	}
}

void DataBase::sqlError(sql::SQLException e){/*output if errors occur*/
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

std::map<int, string> DataBase::getNames(){
	return names;
}

std::map<int, string> DataBase::getTypes(){
	return types;
}
