#ifndef __THREADPOOL__
#define __THREADPOOL__

#include "TaskQueue.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>


class ThreadPool{
public:
    inline ThreadPool(const size_t& min,const size_t& max);
    inline ~ThreadPool();
    inline void addTask(callback func,void* arg);
    inline void addTask(const Task& t);
    inline const int getBusyNum();
    inline const int getAliveNum();
private:
    static void* doWorker(void* arg);
    static void* doManager(void* arg);

    inline void threadExit();

private:
    TaskQueue* taskQ;       //任务队列

    pthread_t managerID;    //管理者线程
    pthread_t* workerIDs;   //工作者线程

    size_t minNum;          //最小线程数
    size_t maxNum;          //最大线程数
    size_t busyNum;         //繁忙线程数
    size_t liveNum;         //存活线程数
    size_t exitNum;         //预销毁线程数

    pthread_mutex_t mutexPool;
    pthread_cond_t isEmpty;
    bool shutdown;

    static const int NUMBER = 2;

};

#endif