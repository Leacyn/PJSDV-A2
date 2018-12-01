#ifndef TCP_H
#define TCP_H

#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

class TCP {
	public:
		TCP(char *address, int portNumber);
		void sendMsg(std::string message);
		std::string receive(void); 
	protected:
		int port;
		char *serverAddress;
		struct sockaddr_in address; 
    	int sock = 0;
		int valread = 0; 
    	struct sockaddr_in serv_addr; 
    	char msg[1024];
   		char buffer[1024] = {0}; 
};

#endif
