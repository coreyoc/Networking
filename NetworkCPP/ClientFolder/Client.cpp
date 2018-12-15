// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include "FileManager.h"
#include <unistd.h>
#include "RDT.h"
#define PORT 8080 
using namespace std;

int main(int argc, char const *argv[]) 
{ 
	// Helper for relaible transport 
    rdtSender rdt(PORT);
	// Helper for file IO
    FileManager file("/Users/coreyoconnor/NetworkCPP/ClientFolder/Dog.jpg",Packet::DATA_BUFFER_SIZE);

	if(file.readFile())
    {
        cout << "file is open " << endl;
    };
    
	char *chunk = new char[Packet::DATA_BUFFER_SIZE];
    while(file.fileState)
    {

        int chunkSize = file.getChunk(chunk);
        cout << "got Chunk of size " << chunkSize << endl;
        if(rdt.rdtSend(chunk,chunkSize))
        {
            break;
        };

    }; 
    
	cout << "Client Progem END" << endl;
    return 0; 
}