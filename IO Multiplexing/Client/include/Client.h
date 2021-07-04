#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>

const std::size_t BUFFER_SIZE = 64; 

class Client{
public:
    inline explicit Client();
    inline explicit Client(const char* ip,const int& port);
    inline ~Client();
    inline void Connect();
private:
    inline void setPoll(const int& fd);
    inline void doHandler(const int& fd);
private:
    const char* Ip;
    int Port;
    pollfd fds[2];
};

#endif