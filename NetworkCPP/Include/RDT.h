class Packet
{    public:
        static const int PACKET_SIZE = 1024;
        static const int DATA_BUFFER_SIZE = PACKET_SIZE - (2* sizeof(short));
        Packet();
        Packet(char *inData, short size);
        char *getData(void);
        short getDataSize(void);

    private:
        short dataSize;
        short checksum;
        char data[DATA_BUFFER_SIZE];
};

class rdtSender
{
    private:
        int port;
        int sock, valread;
    public:
        rdtSender(int port);
        int rdtSend(char *data, short size);

};

class rdtReciever
{
    private:
        int (*deliver)(char*,int);
        char sbuffer[1024];
        int server_fd, new_socket, valread;
    public:
        rdtReciever(int(*callback)(char*,int),int port);
        int rdtRecieve(void);
};