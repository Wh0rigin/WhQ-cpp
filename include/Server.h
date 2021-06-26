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
#include <errno.h>

class Server;

const std::size_t BUFFER_SIZE = 64;  //缓存区最大限制
const std::size_t USER_LIMIT =  5;    //最大用户限制
const std::size_t FD_LIMIT = 65535;  //文件描述符数量限制

struct client_data{
    sockaddr_in address;
    char* write_buf;
    char buf[ BUFFER_SIZE ];
};

class Server{
public:
    inline explicit Server();
    inline ~Server();
    inline explicit Server(const char* ip,const int& port);
    inline void Listen();
private:
    inline void setPoll(const int& fd);
    inline void getClient(const int& fd);
    inline const int setnonblocking(const int& fd);
private:
    inline void doErr(const std::size_t& who);
    inline void doRhup(std::size_t& i);
    inline void doIn(std::size_t& i);
    inline void doOut(const std::size_t& i);
private:
    const char* Ip;
    int Port;
    client_data users[ FD_LIMIT ];
    pollfd fds[ USER_LIMIT + 1 ];
    std::size_t user_counter = 0;
};

#endif