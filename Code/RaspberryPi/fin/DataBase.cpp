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
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT Sensor.id AS sensor_id, Sensor.type AS type, CONCAT(Devices.name,\"_\",Sensor.sub_type) AS name, Devices.name AS device, Devices.ipAddress AS ip FROM Sensor INNER JOIN Devices ON Sensor.device = Devices.name ORDER BY name ASC");

		string prevDev = "";
		string IP;
		vector<int> IDs;


		while(res->next()){
			string currDev = res->getString("device").c_str();
			if (prevDev == "" || prevDev!=currDev){
				if (prevDev != ""){
					struct deviceData data;
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
			IDs.push_back(res->getInt("sensor_id"));
			prevDev = currDev;
		}
		struct deviceData finalData;
		finalData.name = prevDev;
		finalData.ipAddress = IP;
		finalData.IDs = IDs;
		v.push_back(finalData);
		delete res;
  	delete stmt;
  }catch(sql::SQLException &e){
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

std::map<int, string> DataBase::getNames(){
	return names;
}

std::map<int, string> DataBase::getTypes(){
	return types;
}
