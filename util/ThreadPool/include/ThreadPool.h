#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <queue>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//任务队列
struct Task;

const int NUMBER = 2;

class ThreadPool{
public:
    inline explicit ThreadPool();
    inline ~ThreadPool();
    inline explicit ThreadPool(const int& min , const int& max , const int& queueSize,const int& queueCapacity);
    inline void threadExit();
    inline void threadPoolAdd(void(*func)(void*),void* arg);
    inline const int threadPoolBusyNum();
    inline const int threadPoolLiveNum();
    inline const int threadPoolDestroy();
public:
    pthread_mutex_t mutexPool;  //线程池锁
    pthread_mutex_t mutexBusy;  //busyNum单独锁

    pthread_cond_t isFull;      //任务队列是否满了
    pthread_cond_t isEmpty;     //任务队列是否为空



    std::queue<Task*> taskQueue;

    int busyNum;    //工作中线程
    
    int liveNum;    //存活线程
    int queueSize;
    bool shutdown;      //是否销毁线程池

    int minNum;     //最小线程数
    int maxNum;     //最大线程数

    int exitNum;    //需要杀死的线程数
    pthread_t *workerIDs;       //工作者线程
private:


    pthread_t managerID;        //管理者线程
    int queueCapacity;

};

void* doWorker(void* arg);
void* doManager(void* arg);

#endif