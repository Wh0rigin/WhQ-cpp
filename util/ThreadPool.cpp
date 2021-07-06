#include "ThreadPool.h"

struct Task
{
    void (*function) (void* arg);
    void* arg;
};


inline ThreadPool::ThreadPool():minNum(0),maxNum(0),queueSize(0),busyNum(0){  //default

}
inline ThreadPool::ThreadPool(const int& min , const int& max , const int& queueSize):minNum(min),maxNum(max),queueSize(queueSize),busyNum(0),liveNum(min),exitNum(0){
    do{
        this->workerIDs = (pthread_t*)std::malloc(sizeof(pthread_t) * maxNum);
        if( this-> workerIDs == NULL ){
            printf("malloc workerIDs fail...\n");
            break;
        }
        memset(this->workerIDs,0,sizeof(pthread_t) * this->maxNum );
        if( pthread_mutex_init(&this->mutexPool,NULL) != 0 || pthread_mutex_init(&this->mutexBusy,NULL) != 0 || pthread_cond_init(&this->isEmpty,NULL) != 0 || pthread_cond_init(&this->isFull,NULL) != 0 )
        {
            printf("mutex or cond create init fail...\n");
            break;
        }
        

        this -> shutdown = false;

        //创建管理者线程
        pthread_create(&this->managerID,NULL,doManager,NULL);
        //创建工作者线程
        for(int i = 0; i < this->minNum; ++i){
            pthread_create(&this->workerIDs[i],NULL,doWorker,NULL);
        }
        return;
    }while(0);
    std::free(this->workerIDs);
    throw "initial error!";
}
inline ThreadPool::~ThreadPool(){
    std::free(this->workerIDs);
}

void* doWorker(void* arg){
    ThreadPool* pool = (ThreadPool*)arg;

    while(1){
        pthread_mutex_lock(&pool->mutexPool);
        while(pool->queueSize == 0 && !pool->shutdown){
            // 阻塞线程
            pthread_cond_wait(&pool->isEmpty,&pool->mutexPool);
        }

        if( pool -> shutdown ){
            pthread_mutex_unlock(&pool->mutexPool);
            pthread_exit(NULL);
        }

        Task task;
        task.function = pool->taskQueue.front()->function;
        task.arg =  pool->taskQueue.front()->arg;
        pool->taskQueue.pop();

        pthread_mutex_unlock(&pool->mutexPool);

        printf("thread %ld start working...\n");
        pthread_mutex_lock(&pool->mutexBusy);
        ++pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        
        (*task.function)(task.arg);
        std::free(task.arg);
        task.arg = NULL;

        pthread_mutex_lock(&pool->mutexBusy);
        --pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);
        printf("thread %ld end working...\n");
    }

    return NULL;
}

void* doManager(void* arg){
    return NULL;
}