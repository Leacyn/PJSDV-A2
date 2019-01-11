/*-----------------------------------
  TCP class Definition
  version: 1.0
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#include "TCP.h"
#include <iostream>

using namespace std;

TCP::TCP(const char  *address, int portNumber){
	/*allocate memory for the recieving data buffer*/
	buffer = (char*)malloc(512);
	/*assign given values to private members*/
	port = portNumber;
	serverAddress = address;

	clog << endl << "connecting to " << serverAddress << ", " << port << endl;
	/*create the socket for the connection to the devices */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
  	cerr << endl << "CRIT, Socket creation error" << endl;
  }
	/*set memory to the values*/
  memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  /* Convert IPv4 addresses from text to binary form */
  if(inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr)<=0){
  	cerr << endl << "CRIT, Invalid address / Address not supported" << endl;
  }
	/*connect*/
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
  	cerr << endl << "CRIT, Connection Failed" << endl;
  }
	clog << " connected" << endl;
}



void TCP::sendMsg(int id, std::string cmd, int Value){
	jBuffer.clear(); // clear json buffer for more stable conversion
	string smsg= encode(id,cmd,Value); // encode parameters to a json string
	char *message = new char[smsg.length()];
	strcpy(message, smsg.c_str()); // copy the encoded string to message
	send(sock , message , strlen(message) , 0 ); //send message to device
	receiveJson();
	// check if message arrived correctly
	//cout << endl << "(" << id << " " << msg.ID << ")" << "(" << cmd << " " <<  msg.command << ")" << "(" << Value << " " << msg.value << ")" << endl;
	// if(id == msg.ID && !(cmd.compare(msg.command)) && Value == msg.value){
	// 	//cout << " Message varified" << endl;
	// }
	delete message; // clean up memory
}

std::string TCP::receiveJson(void){
	/*recieve tcp data, parce it through the json buffer and put the data in the msg struct for later use*/
	jBuffer.clear();
	recv(sock, buffer,128, 0);//recieve data from tcp the socket and push to buffer
	JsonObject& message = jBuffer.parseObject((string)buffer);// parsing json object
	if(!message.success()) cerr << "parserfail\n";
	msg.ID = message.get<signed int>("id");
	msg.command =  message.get<std::string>("command");
	msg.value = message.get<signed int>("value");

	return buffer;
}


string TCP::encode(int id, std::string command, int value){
	// take the parameters, make a json object out of it, and return it via a std::string.
	string buffer;
	JsonObject& message = jBuffer.createObject();
	message["id"] = id;
	message["command"] = command;
	message["value"] = value;

	message.printTo(buffer);
	jBuffer.clear();

	return buffer;
}

void TCP::sendWrite(int id, int val){
	//interface function to more easily determine read/write messages
	sendMsg(id,"w", val);
	clog << "send {w, "  << id << ", " << val << "}" << endl;
}


int TCP::sendRead(int id){
	//interface function to more easily determine read/write messages
	sendMsg(id, "r", 0);
	receiveJson();
	//clog << msg.value<<", "<<id << endl;
	return msg.value;
}
