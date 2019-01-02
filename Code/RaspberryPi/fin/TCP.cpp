/*-----------------------------------
  Zuil class Definition
  version: 0.1
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#include "TCP.h"
#include <iostream>

using namespace std;

//message


TCP::TCP(char  *address, int portNumber){
	port = portNumber;
	serverAddress = address;

    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        	cerr << endl << "CRIT, Socket creation error" << endl;
    	}
    	memset(&serv_addr, '0', sizeof(serv_addr));

    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(port);

    	/* Convert IPv4 and IPv6 addresses from text to binary form */
    	if(inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr)<=0){
    	    	cerr << endl << "CRIT, Invalid address / Address not supported" << endl;
   	}
	/*connect*/
    	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        	cerr << endl << "CRIT, Connection Failed" << endl;
    	}
}

void TCP::sendMsg(int id, std::string cmd, int Value){
	jBuffer.clear();
	string smsg= encode(id,cmd,Value);
	//cout << "LOG, " << smsg;
	char *message = new char[smsg.length()];
	strcpy(message, smsg.c_str());
	send(sock , message , strlen(message) , 0 );
	cout << "Message sent";
	receiveJson();
	cout << endl << "(" << id << " " << msg.ID << ")" << "(" << cmd << " " <<  msg.command << ")" << "(" << Value << " " << msg.value << ")" << endl;
	if(id == msg.ID && !(cmd.compare(msg.command)) && Value == msg.value){
		cout << " Message varified" << endl;
	}

	free(message);
}

std::string TCP::receiveJson(void){

	int recieved = recv(sock, buffer,sizeof(buffer) + 1, 0);
	//cout << (string)buffer <<"    |     " << recieved;
	JsonObject& message = jBuffer.parseObject((string)buffer);

	if(!message.success()) cout << "parserfail";
	//else {message.printTo(cout);}
	msg.ID = message.get<signed int>("id");
	msg.command =  message.get<std::string>("command");
	//strcpy(msg.command,message.get<std::string>("command").c_str());
	//msg.command = message.get<std::string>("command").c_str();
	msg.value = message.get<signed int>("value");

	return buffer;
}


string TCP::encode(int id, std::string command, int value){
	string buffer;
	JsonObject& message = jBuffer.createObject();
	message["id"] = id;
	message["command"] = command;
	message["value"] = value;

	message.printTo(buffer);
	jBuffer.clear();

	return buffer;
}

TCP::sendWrite(int id, int val){
	sendMsg(id,"w", val);
}


int TCP::sendRead(int id, int val){
	sendMsg(id, "r", val);
	receiveJson();
	return msg.value;
}
