// Client side C/C++ program to demonstrate Socket programming 
#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <netdb.h>
#include <netinet/in.h> 
#include <string.h>
#include <string> 
#include <arpa/inet.h>

#define PORT 54000 
char const *ServerAddress = "192.168.2.1";

using namespace std;
   
int main(int argc, char const *argv[]) 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread = 0; 
    struct sockaddr_in serv_addr; 
    char hello[1024] = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        std::cout << "\n Socket creation error \n"; 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ServerAddress, &serv_addr.sin_addr)<=0)  
    { 
        std::cout << "\nInvalid address/ Address not supported \n"; 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        std::cout <<"\nConnection Failed \n"; 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    std::cout << "Hello message sent\n"; 
    valread = recv( sock , buffer,sizeof(buffer),0); 
    std::cout << buffer , "/r/n"; 
    return 0; 
}