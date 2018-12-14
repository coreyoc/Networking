#include "RDT.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

Packet::Packet()
{
    *data = 0;
};
Packet::Packet(char* inData, short size)
{   
    dataSize = size;
    checksum = 0;
    memcpy(&data[0], inData, size);
};
char* Packet::getData(void)
{
    return data;
};
short Packet::getDataSize(void)
{
    return dataSize;
};
rdtSender::rdtSender(int outPort)
{
    port = outPort;
    struct sockaddr_in address; 
 
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};  

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
//        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
//        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
//        return -1; 
    } 
};
int rdtSender::rdtSend(char *data, short size)
{
    Packet newPacket(data,size);
    if(send(sock , &newPacket , sizeof(newPacket) , 0) == -1)
    {
        printf("\n Error on send\n");
        return 1;
    }
        printf("\n Sent Chunk\n");
    return 0;
};
rdtReciever::rdtReciever(int(*callback)(char*,int),int port)
{
    deliver = callback;
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( port ); 

       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

};
int rdtReciever::rdtRecieve(void)
{

     while(1)
    {
        valread = recv( new_socket , sbuffer, Packet::PACKET_SIZE,0);
        if(valread <= 0)
        {
            cout << "Recv has returned " << valread << endl;
            cout << "Breaking loop.." << endl;
            break;
        }
        if(strcmp(sbuffer,"start") == 0)
        {
            cout << "START" << endl;
            continue;
        }
        cout << "Packet recieved" << endl;
        Packet *newPacket;
        newPacket = (Packet*)sbuffer;
        char *data = newPacket->getData();
        int dataSize = newPacket->getDataSize();
        deliver(data,dataSize);
        memset(sbuffer, 0, sizeof sbuffer);
    }
  
    close(new_socket); 
    return 0;
};