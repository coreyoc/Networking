#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "FileManager.cpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
const int bufferSize = 1024;

int main()
{
    

    FileManager file("/Users/coreyoconnor/NetworkCPP/Dog.jpg");
    FileManager rcvFile("/Users/coreyoconnor/NetworkCPP/Recieved.jpg");
    int chunkCount = 0;
    if(file.readFile())
    {
        cout << "file is open " << endl;
    };
    char *chunk = new char[bufferSize];
    while(file.fileState)
    {

        int chunkSize = file.getChunk(chunk);
        chunkCount++;
        cout << "Read chunk # " << chunkCount << " with size " << chunkSize << endl;
        rcvFile.putChunk(chunk, chunkSize);
    };
    rcvFile.writeFile();

    return 0;
}