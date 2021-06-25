#ifndef __SERVER_H__
#define __SERVER_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

class Server;

class Server{
public:
    inline Server();
    inline ~Server();
    inline Server(const char* ip,const int& port);
    inline void Listen();
private:
    const char* Ip;
    int Port;
    int Sock_fd;
};

#endif