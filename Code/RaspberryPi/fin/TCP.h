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

struct TCPmessage{
        signed int ID;
        std::string command;
        signed int value;
};


class TCP {
	

	public:
		TCP(char *address, int portNumber);
		void sendMsg(int id, std::string cmd, int Value);
		std::string receiveJson(void);
	protected:
		StaticJsonBuffer<200> jBuffer;
		int port;
		char *serverAddress;
		struct sockaddr_in address; 
    		int sock;
		int valread; 
    		struct sockaddr_in serv_addr; 
   		char buffer[256]; 
		std::string encode(int id, std::string cmd, int value);
		TCPmessage msg;
};

#endif
