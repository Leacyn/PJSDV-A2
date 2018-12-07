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

class TCP {
	

	public:
		TCP(char *address, int portNumber);
		void sendMsg(char* msg);
		std::string receive(void); 
	protected:
		int port;
		char *serverAddress;
		struct sockaddr_in address; 
    	int sock = 0;
		int valread = 0; 
    	struct sockaddr_in serv_addr; 
    	char msg[256];
   		char buffer[265]; 
   		struct TCPmessage{
   			uint16_t ID;
   			char command;
   			char data[128];
   		};
		void serialize_data();
		void deserialize_data();
};

#endif
