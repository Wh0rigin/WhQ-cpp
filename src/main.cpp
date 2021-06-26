#include "Server.cpp"



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