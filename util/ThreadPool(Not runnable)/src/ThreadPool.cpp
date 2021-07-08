#include "ThreadPool.h"
#include <queue>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void* doManager(void* arg);
void* doWorker(void* arg);

struct Task
{
    void (*function) (void* arg);
    void* arg;
};


void* doWorker(void* arg){
    ThreadPool* pool = (ThreadPool*)arg;

    while(1){
        pthread_mutex_lock(&pool->mutexPool);
        while(pool->queueSize == 0 && !pool->shutdown){
            // 阻塞线程
            pthread_cond_wait(&pool->isEmpty,&pool->mutexPool);

            //判断是否销毁线程
            if(pool->exitNum > 0 ){
                --pool->exitNum;
                if(pool->liveNum > pool->minNum){
                    --pool->liveNum;
                    pthread_mutex_unlock(&pool->mutexPool);
                    pool->threadExit();
                }
            }
        }

        if( pool -> shutdown ){
            pthread_mutex_unlock(&pool->mutexPool);
            pool->threadExit();
        }

        Task task;
        task.function = pool->taskQueue.front()->function;
        task.arg =  pool->taskQueue.front()->arg;
        free(pool->taskQueue.front());
        pool->taskQueue.pop();
       --pool->queueSize;

        pthread_cond_signal(&pool->isFull);

        pthread_mutex_unlock(&pool->mutexPool);

        printf("thread %ld start working...\n",pthread_self());
        pthread_mutex_lock(&pool->mutexBusy);
        ++pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        
        (*task.function)(task.arg);
        std::free(task.arg);
        task.arg = NULL;

        pthread_mutex_lock(&pool->mutexBusy);
        --pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);
        printf("thread %ld end working...\n",pthread_self());
    }

    return NULL;
}

void* doManager(void* arg){
    ThreadPool* pool = (ThreadPool*)arg;
    while(!pool->shutdown){


        sleep(3);

        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveNum;
        pthread_mutex_unlock(&pool->mutexPool);

        pthread_mutex_lock(&pool->mutexBusy);
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexBusy);

        if(queueSize > liveNum && liveNum < pool->maxNum){
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for(int i = 0; i < pool->maxNum && counter < NUMBER && pool->liveNum < pool->maxNum;++i){
                if( pool -> workerIDs[i] == 0 ){
                    pthread_create(&pool->workerIDs[i],NULL,doWorker,pool);
                    ++counter;
                    
                    ++pool -> liveNum;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }

        if(busyNum *2 < liveNum  && liveNum > pool->minNum){
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);

            for(int i = 0;i < NUMBER;++i){
                pthread_cond_signal(&pool->isEmpty);
            }
        }
    }
    return NULL;
}



inline ThreadPool::ThreadPool():minNum(0),maxNum(0),queueSize(0),busyNum(0){  //default

}
inline ThreadPool::ThreadPool(const int& min , const int& max , const int& queueSize,const int& queueCapacity):minNum(min),maxNum(max),queueSize(queueSize),queueCapacity(),busyNum(0),liveNum(min),exitNum(0){
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
        pthread_create(&this->managerID,NULL,doManager,this);
        //创建工作者线程
        for(int i = 0; i < this->minNum; ++i){
            pthread_create(&this->workerIDs[i],NULL,doWorker,this);
        }
        return;
    }while(0);
    std::free(this->workerIDs);
    throw "initial error!";
}
inline ThreadPool::~ThreadPool(){
    this->threadPoolDestroy();
}



inline void ThreadPool::threadExit(){
    pthread_t tid = pthread_self();
    for(int i =0; i < this->maxNum;++i){
        if(this->workerIDs[i] == tid){
            this->workerIDs[i] = 0;
            printf("threadExit() called,%ld exiting...\n",tid);
            break;
        }
    }
    pthread_exit(NULL);
}


inline void ThreadPool::threadPoolAdd(void(*func)(void*),void* arg){
    pthread_mutex_lock(&this->mutexPool);
    while(!this->shutdown && this->queueSize == this->queueCapacity){
        pthread_cond_wait(&this->isFull,&this->mutexPool);
    }
    if(this->shutdown){
        pthread_mutex_unlock(&this->mutexPool);
        return;
    }
    //添加任务
    Task* task = new Task();
    task->function = func;
    task->arg = arg;
    this->taskQueue.push(task);

    ++this->queueSize;

    pthread_cond_signal(&this->isEmpty);

    pthread_mutex_unlock(&this->mutexPool);
}

inline const int ThreadPool::threadPoolBusyNum(){
    pthread_mutex_lock(&this->mutexBusy);
    int busy = this->busyNum;
    pthread_mutex_unlock(&this->mutexBusy);
    return busy;
}

inline const int ThreadPool::threadPoolLiveNum(){
    pthread_mutex_lock(&this->mutexPool);
    int live = this->liveNum;
    pthread_mutex_unlock(&this->mutexPool);
    return live;
}

inline const int ThreadPool::threadPoolDestroy(){
    //关闭线程池
    this->shutdown = true;

    pthread_join(this->managerID,NULL);

    for(int i = 0; i < this->liveNum;++i){
        pthread_cond_signal(&this->isEmpty);
    }

    if(this->workerIDs){
        free(this->workerIDs);
    }
    
    while(!taskQueue.empty()){
        free(taskQueue.front());
        taskQueue.pop();
    }

    pthread_mutex_destroy(&this->mutexPool);
    pthread_mutex_destroy(&this->mutexBusy);

    pthread_cond_destroy(&this->isEmpty);
    pthread_cond_destroy(&this->isFull);
    return 0;
}
