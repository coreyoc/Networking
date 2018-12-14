#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
class FileManager
{
    private:
        char* fn;
        int bufferSize;
        std::ifstream fileStream;
        std::ofstream outputFile;
        
    public:
        FileManager(char* file,int chunkSize);
        int readFile(void);
        int fileState;
        int getChunk(char *chunk);
        void putChunk(char *chunk,int size);
        void writeFile(void);
};