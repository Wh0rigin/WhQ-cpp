#include "Server.cpp"

#define USER_LIMIT 5    //最大用户限制
#define BUFFER_SIZE 64  //缓存区最大限制
#define FD_LIMIT 65535  //文件描述符数量限制

Server* server;  //前置声明

int main(int argc ,char* argv[]){
    if(argc <= 2){
        printf("usage: %s ip_address port_number\n",basename(argv[0]));
        return 1;
    }
    const char* ip = argv[1];
    const int port = atoi( argv[2] );

    server = new Server(ip,port);

    server->Listen();
    
}