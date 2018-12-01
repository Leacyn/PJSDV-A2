#include "TCP.h"

using namespace std;

TCP::TCP(char address, int portNumber){
	port = portNumber;
	*serverAddress = address;
	
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        cerr << endl << "Socket creation error" << endl; 
        throw runtime_error("failed to connect");
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr)<=0){ 
        cerr << endl << "Invalid address / Address not supported" << endl; 
        throw runtime_error("failed to connect");
    } 
    //connect
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        cerr << endl << "Connection Failed" << endl; 
        throw runtime_error("failed to connect");
    } 
}

TCP::send(string message){
	msg = message;
	send(sock , msg , strlen(msg) , 0 ); 
    clog << "Message sent" << endl; 
}

TCP::receive(void){
	valread = recv( sock , buffer,sizeof(buffer),0); 
	clog << "Message received" << endl;
	return buffer; 
}
