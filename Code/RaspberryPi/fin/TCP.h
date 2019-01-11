/*-----------------------------------
  TCP class decleration
  version: 1.0
  contributors:
  Vincent Geers 13009672
----------------------------------*/
#ifndef TCP_H
#define TCP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include "ArduinoJson-v5.13.4.h"

/*Struct to define message object*/
struct TCPmessage{
  signed int ID;
  std::string command;
  signed int value;
};

/*Class to manage TCP connection to endpoint. Also send/ receive data from and to endpoint*/
class TCP {

	public:
  /*Public functions send/ receive and constructor*/
  	void sendWrite(int id, int val);
		int sendRead(int id);
		TCP(const char *address, int portNumber);
  protected:
  /*Attributes*/
    StaticJsonBuffer<200> jBuffer;
		const char *serverAddress;
		char *buffer;//[256];
		int port;
		int sock;
		int valread;
		struct sockaddr_in address;
    struct sockaddr_in serv_addr;
		TCPmessage msg;
  /*Private functions*/
    std::string receiveJson(void);
		std::string encode(int id, std::string cmd, int value);
		void sendMsg(int id, std::string cmd, int Value);
};

#endif
