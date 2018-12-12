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

class TCP {
	

	public:
		TCP(char *address, int portNumber);
		void sendMsg(char * msg);
		void sendMsg(int id, char *cmd, int Value);
		std::string receive(void);
		std::string recieveJson(void);
	protected:
		StaticJsonBuffer<200> jBuffer;
		int port;
		char *serverAddress;
		struct sockaddr_in address; 
    	int sock;
		int valread; 
    	struct sockaddr_in serv_addr; 
    	char msg[256];
   		char buffer[256]; 
		std::string encode(int id, char *cmd, int value);
		//void decode(TCPmessage message ,char *Data);
};

#endif
