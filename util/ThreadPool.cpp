#include "ThreadPool.h"

struct Task
{
    void (*function) (void* arg);
    void* arg;
};


inline ThreadPool::ThreadPool():minNum(0),maxNum(0),queueSize(0){}  //default
inline ThreadPool::ThreadPool(const int& min , const int& max , const int& queueSize):minNum(min),maxNum(max),queueSize(queueSize){
    this->workerIDs = (pthread_t*)std::malloc(sizeof(pthread_t) * maxNum);
    if( this-> workerIDs == NULL ){
        printf("malloc workerIDs fail...\n");
    }
}
inline ThreadPool::~ThreadPool(){
    std::free(this->workerIDs);
}