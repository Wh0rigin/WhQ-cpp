#include "Client.hpp"

inline Client::Client(){}
inline Client::Client(const char* ip,const int& port):Ip(ip),Port(port){}
inline Client::~Client(){
    printf("connect stop...");
}

inline void Client::Connect(){
    struct sockaddr_in dir_sockaddress;
    bzero( &dir_sockaddress , sizeof( dir_sockaddress ) );
    dir_sockaddress.sin_family = AF_INET;
    inet_pton( AF_INET , this->Ip , &dir_sockaddress.sin_addr );
    dir_sockaddress.sin_port = htons( this->Port );

    int sockfd = socket( PF_INET , SOCK_STREAM , 0 );
    assert( sockfd >= 0 );

    if( connect( sockfd , (struct sockaddr*)&dir_sockaddress , sizeof( dir_sockaddress )) < 0 ){
        printf("connection failed\n");
        close(sockfd);
        return;
    }


    this->setPoll(sockfd);

    this->doHandler(sockfd);

    close(sockfd);

}

inline void Client::setPoll(const int& fd){
    // 0 标准输入
    this->fds[0].fd = 0;
    this->fds[0].events = POLLIN;
    this->fds[0].revents = 0;
    this->fds[1].fd = fd;
    this->fds[1].events = POLLIN | POLLRDHUP;
    this->fds[1].revents = 0;
}

inline void Client::doHandler(const int& fd){
    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    int ret = pipe( pipefd );
    assert( ret != -1 );
    
    while(1){
        ret = poll( this->fds , 2 , -1);
        if( ret < 0 ){
            printf("poll failure\n");
            break;
        }

        if(this->fds[1].revents & POLLRDHUP ){
            printf("server close the connection\n");
            break;
        }
        else if(this->fds[1].revents & POLLIN ){
            memset( read_buf , '\0' , BUFFER_SIZE);
            recv( this->fds[1].fd , read_buf , BUFFER_SIZE - 1 , 0 );
            printf("%s\n",read_buf);
        }
        else if(this->fds[0].revents & POLLIN ){
            ret = splice( 0 , NULL , pipefd[1] , NULL , 32768 , SPLICE_F_MORE | SPLICE_F_MOVE );
            ret = splice( pipefd[0] , NULL , fd , NULL , 32768 , SPLICE_F_MORE | SPLICE_F_MOVE );
        }
    }
}