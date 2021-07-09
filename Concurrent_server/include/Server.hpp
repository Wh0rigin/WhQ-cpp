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

class Server{
public:
	explicit Server();
	~Server();
	explicit Server(const char* ip,const int& port);
public:
	void Listen();
private:
	const int accept();  	
private:
	const char* Ip;
	int port ;
	int listenfd;
};

#endif
