#include "Server.h"

inline Server::Server(){}
inline Server::Server(const char* ip,const int& port):Ip(ip),Port(port),Sock_fd(0){}
inline Server::~Server(){}

inline void Server::Listen(){
    //绑定socket
    struct sockaddr_in server_address;
    bzero(&server_address , sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET,this->Ip,&server_address.sin_addr);
    server_address.sin_port = htons(this->Port);

    this->Sock_fd = socket(PF_INET,SOCK_STREAM,0);
    assert(this->Sock_fd >= 0 );

    int ret = bind(this->Sock_fd,(struct sockaddr*)&server_address,sizeof(server_address));
    assert( ret != -1 );
    // listen
    ret = listen(this->Sock_fd,5);
    assert( ret != -1 );

    //handler
    while(1){
        sleep(1);
    }
    close(this->Sock_fd);
}