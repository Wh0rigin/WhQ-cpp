#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <queue>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

//任务队列
struct Task;

class ThreadPool{
public:
    inline ThreadPool();
    inline ~ThreadPool();
    inline ThreadPool(const int& min , const int& max , const int& queueSize);
private:
    std::queue<Task*> task;
    int queueSize;
    pthread_t managerID;        //管理者线程
    pthread_t *workerIDs;       //工作者线程
    int minNum;     //最小线程数
    int maxNum;     //最大线程数
    int busyNum;    //工作中线程
    int liveNum;    //存活线程
    int exitNum;    //需要杀死的线程数

    pthread_mutex_t mutexPool;  //线程池锁
    pthread_mutex_t mutexBusy;  //busyNum单独锁

    bool shutdown;      //是否销毁线程池

    pthread_cond_t isFull;      //任务队列是否满了
    pthread_cond_t isEmpty;     //任务队列是否为空
};


#endif