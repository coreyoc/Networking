#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "FileManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "RDT.h"
#define PORT 8080
using namespace std;

FileManager rcvFile("/Users/coreyoconnor/NetworkCPP/ServerFolder/Recieved.jpg");
int deliverData(char* data,int dataSize)
{
    rcvFile.putChunk(data,dataSize);
    return 0;
};
int main(int argc, char const *argv[]) 
{
    rdtReciever rdt(deliverData,PORT);
    rdt.rdtRecieve();
    rcvFile.writeFile(); 
    return 0;
}