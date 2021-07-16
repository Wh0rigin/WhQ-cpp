#ifndef __SERVER__
#define __SERVER__

#include "ThreadPool.hpp"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

const int BUFFER_SIZE = 1024;

class Server{
public:
	explicit Server();
	~Server();
	explicit Server(const char* ip,const int& port);
public:
	void Listen();
private:
	const int fdaccept();
	static void doHandler(void* arg);
private:
	const char* Ip;
	int Port ;
	int listenfd;
};



#endif
