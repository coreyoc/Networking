//File manager
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
using namespace std;

FileManager::FileManager(char* file,int chunkSize) : fn(file)
{
    bufferSize = chunkSize;
    fileState = 0;
 };
int FileManager::readFile(void)
{
 
    fileStream.open(fn, ios::in | ios::binary);
    if (fileStream.is_open())
    {
        fileState = 1;
        return 1;
    }
    return 0;
};
int FileManager::getChunk(char *chunk)
{
    fileStream.read(chunk,bufferSize);
    cout << "Chunk read" << endl;
    if(fileStream.eof())
    {
        fileState = 0;
    }
    return fileStream.gcount();
};
void FileManager::putChunk(char *chunk,int size)
{
    if(!outputFile.is_open())
    {
        cout << "Opening output file" << endl;
        outputFile.open(fn, ios::out | ios::binary);
        //todo: check if file opened
    }
    outputFile.write(chunk,size);
    cout << "Chunk written of size " << size << endl;
    
};
void FileManager::writeFile(void)
{
    outputFile.close();
    cout << "Output file closed" << endl;
};








