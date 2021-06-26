#include "Server.h"

inline Server::Server(){}
inline Server::Server(const char* ip,const int& port):Ip(ip),Port(port){}
inline Server::~Server(){}

inline void Server::Listen(){
    //绑定socket
    struct sockaddr_in server_address;
    bzero(&server_address , sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET,this->Ip,&server_address.sin_addr);
    server_address.sin_port = htons(this->Port);

    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    assert(listenfd >= 0 );

    int ret = bind(listenfd,(struct sockaddr*)&server_address,sizeof(server_address));
    assert( ret != -1 );
    // listen
    ret = listen(listenfd,5);
    assert( ret != -1 );

    this -> setPoll(listenfd);

    //getclient and dohandler
    
    this -> getClient(listenfd);

}

inline void Server::setPoll(const int& fd){
    //initial
    for(std::size_t i = 1; i <= USER_LIMIT; ++i){
        this->fds[i].fd = -1;
        this->fds[i].events = 0;
    }
    fds[0].fd = fd;
    fds[0].events = POLLIN | POLLERR ;
    fds[0].revents = 0;
}

inline void Server::getClient(const int& fd){
    std::size_t user_counter = 0;
    while(1){
        int ret = poll( fds , user_counter+1 , -1 );
        if( ret < 0 ){
            printf("poll failure");
            break;
        }
        for(std::size_t i = 0; i < user_counter + 1;++i){
            if(( this->fds[i].fd == fd) && (fds[i].revents & POLLIN )){
                struct sockaddr_in client_address;
                socklen_t client_addrlen = sizeof(client_address);
                int connfd = accept( fd , (struct sockaddr*)&client_address,&client_addrlen);
                if( connfd < 0 ){
                    printf("errno is: %d \n",errno);
                    continue;
                }
                //overload
                if( user_counter >= USER_LIMIT ){
                    const char* info = "to many users!\n";
                    printf(" --- %s --- ", info );
                    send( connfd , info , strlen( info ), 0 );  // to client
                    close(connfd);
                    continue;
                }
                ++user_counter;
                users[connfd].address = client_address;
                this->setnonblocking(connfd);
                this->fds[user_counter].fd = connfd;
                this->fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR ;
                this->fds[user_counter].revents = 0;
                printf("comes a new user,now have %d users\n",user_counter);
            }
            else if( this->fds[i].revents & POLLERR ){
                this->doErr(i);
                continue;
            }
            else if( this->fds[i].revents & POLLRDHUP ){
                this->doRhup(i,user_counter);
            }
            else if( this->fds[i].revents & POLLIN ){
                
            }
        }
    }
}

inline const int& setnonblocking(const int& fd){
    int old_option = fcntl( fd , F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd , F_SETFL , new_option);
    return old_option;
}

inline void Server::doErr(const int& who){
    printf("get an error from %d \n",this->fds[who].fd);
    char errors[ 100 ];
    memset(errors , '\0' , 100 );
    socklen_t length = sizeof( errors );
    if(getsockopt(this->fds[who].fd,SOL_SOCKET,SO_ERROR,&errors,&length) < 0 ){
        printf("get socket option failed\n");
    }
}

inline void Server::doRhup(std::size_t& i,std::size_t& user_counter){
    this->users[this->fds[i].fd] = this->users[this->fds[user_counter].fd];
    close( this->fds[i].fd );
    this->fds[i] = this->fds[user_counter];
    --i;
    --user_counter;
    printf("a client left\n");
}