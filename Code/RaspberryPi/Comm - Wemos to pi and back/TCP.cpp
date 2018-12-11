#include "TCP.h"
#include <iostream>

using namespace std;

//message 

struct TCPmessage{
   			int ID;
   			char command;
   			int value;
   		};

TCP::TCP(char  *address, int portNumber){
	port = portNumber;
	serverAddress = address;
	
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        cerr << endl << "Socket creation error" << endl; 
 //       throw runtime_error("failed to connect");
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr)<=0){ 
        cerr << endl << "Invalid address / Address not supported" << endl; 
 //       throw runtime_error("failed to connect");
    } 
    //connect
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        cerr << endl << "Connection Failed" << endl; 
 //       throw runtime_error("failed to connect");
    } 
}

void TCP::sendMsg(char *msg){
	char *message = msg;
	send(sock , message , strlen(message) , 0 ); 
    std::cout << "Message sent \n"; 
}


void TCP::sendMsg(int id, char *cmd, int Value){
	string smsg= encode(id,cmd,Value);
	cout << smsg;
	char *message = new char[smsg.length()+1];
	strcpy(message, smsg.c_str());
	send(sock , message , strlen(message)+1 , 0 ); 
    std::cout << "Message sent \n";
    free(message); 

}

std::string TCP::receive(void){
	valread = recv( sock , buffer,sizeof(buffer),0);
//	JsonObject& message = jBuffer.parseObject(valread);
//	if(!message.success())cout<< "parserfail";
//	int id, value;
//	char * command;
//	id = message["id"].as<int>();
//	value = message["value"].as<int>();
//	strcpy(command, message["command"].as<char*>());
//	std::cout << id <<"|" << command << "|" << value;
	std::cout << "Message received";
	close(sock); 
	return buffer;
}

std::string TCP::recieveJson(void){
	
	int recieved = recv(sock, buffer,sizeof(buffer) + 1, 0);
	cout << (string)buffer <<"    |     " << recieved << endl;
	JsonObject& message = jBuffer.parseObject((string)buffer);
	
	if(!message.success()) cout << "parserfail";
	else {message.printTo(cout);}
	cout << message.get<signed int>("id") << "|" << message.get<char *>("command") << "|" << message.get<signed int>("value") << "\n\r ";

	return buffer;
}


string TCP::encode(int id, char *command, int value){
	string buffer;
	JsonObject& message = jBuffer.createObject();
	message["id"] = id;
	message["command"] = (char *)command;
	message["value"] = value;

	message.printTo(buffer);
	jBuffer.clear();

	return buffer;
}
/*
void TCP::decode(TCPmessage message ,char *Data){
	int *i = (int *)Data;
	message.ID = *i; 		i++;
	char *q = (char*)i;
	message.command = *q;	q++;
	i = (int *)q;
	message.value = *i; 	i++;

}
*/



