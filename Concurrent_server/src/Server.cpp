#include "Server.hpp"
#include "ThreadPool.cpp"

inline explicit Server::Server():Ip("127.0.0.1"),Port(8080){}

inline explicit Server::Server(const char* ip,const int& port):Ip(ip),Port(port){}

inline Server::~Server(){
	printf("connect stop...\n");
}

inline void Server::Listen(){
	ThreadPool<int>* pool = new ThreadPool<int>(3,10);
	struct sockaddr_in server_address;
	bzero(&server_address , sizeof(server_address));
	server_address.sin_family = AF_INET;
	inet_pton(AF_INET,Ip,&server_address.sin_addr);
	server_address.sin_port = htons(Port);

	listenfd = socket(PF_INET,SOCK_STREAM,0);
	assert( listenfd >= 0 );

	int ret = bind(listenfd,(struct sockaddr*)&server_address,sizeof(server_address));
	assert( ret != -1 );

	ret = listen(listenfd,5);
	assert( ret != -1 );
	while(1){	
		int fd = this->accept();
		assert( fd != -1 );

				
	}	
}

inline const int Server::accept(){
	struct sockaddr_in  client_address;
	socklen_t client_addrlen  = sizeof(client_address);
	int connfd = accept( listenfd , (struct sockaddr*)&client_address,&client_addrlen);
	if(connfd < 0 ){
		printf("errno is %d \n",errno);
		return -1;
	}
	return connfd;
}

