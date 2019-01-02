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
		void sendWrite(int id, int val);
		int sendRead(int id);
		TCP(char *address, int portNumber);
		std::string receiveJson(void);
	protected:
		StaticJsonBuffer<200> jBuffer;
		char *serverAddress;
		char buffer[256];
		int port;
		int sock;
		int valread;
		struct sockaddr_in address;
    		struct sockaddr_in serv_addr;
		TCPmessage msg;

		std::string encode(int id, std::string cmd, int value);
		void sendMsg(int id, std::string cmd, int Value);

};

#endif
