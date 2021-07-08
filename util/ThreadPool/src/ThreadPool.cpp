#include "ThreadPool.h"


inline ThreadPool::ThreadPool(const size_t& min,const size_t& max):minNum(min),maxNum(max),busyNum(0),liveNum(min),exitNum(0),shutdown(false){
    
    do{

        taskQ = new TaskQueue();
        if( taskQ == nullptr ){
            printf("new taskQ fail...\n");
            break;
        }

        workerIDs = new pthread_t[max];

        if( workerIDs == nullptr ){
            printf("new workerIDs fail...\n");
            break;
        }

        memset(workerIDs,0,sizeof(pthread_t) * max );

        if(pthread_mutex_init(&mutexPool,NULL) != 0 || pthread_cond_init(&isEmpty,NULL) != 0 ){
            printf("mutex or cond fail...\n");
            break;
        }

        pthread_create(&managerID,NULL,doManager,this);
        for(int i = 0; i < min; ++i ){
            pthread_create(&workerIDs[i],NULL,doWorker,this);
        }

        return;
    }while(0);

    if(workerIDs) delete[] workerIDs;
    if(taskQ)delete taskQ;
}

void* ThreadPool::doManager(void* arg){
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while(!pool->shutdown){
        sleep(3);
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->taskQ->taskNum();
        int liveNum = pool->liveNum;
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexPool);

        if(queueSize > liveNum && liveNum < pool->maxNum ){
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for(int i = 0; i < pool->maxNum && counter < NUMBER && pool->liveNum < pool->maxNum;++i){
                if(pool->workerIDs[i] == 0 ){
                    pthread_create(&pool->workerIDs[i],NULL,doWorker,pool);
                    counter++;
                    ++pool->liveNum;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }

        if( busyNum * 2 < liveNum && liveNum > pool->minNum){
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum - NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);
            for(int i = 0;i < NUMBER;++i){
                pthread_cond_signal(&pool->isEmpty);
            }
        }
    }
    return nullptr;
}

void* ThreadPool::doWorker(void* arg){
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while(1){
        pthread_mutex_lock(&pool->mutexPool);
        //当前任务队列是否为空
        while(pool->taskQ->taskNum() == 0 && !pool->shutdown){
            pthread_cond_wait(&pool->isEmpty,&pool->mutexPool);

            if(pool->exitNum > 0 ){
                --pool->exitNum;
                if(pool -> liveNum > pool -> minNum){
                    --pool->liveNum;
                    pthread_mutex_unlock(&pool->mutexPool);
                    pool->threadExit();
                }
            }
        }

        if(pool -> shutdown){
            pthread_mutex_unlock(&pool->mutexPool);
            pool->threadExit();
        }

        Task task = pool->taskQ->takeTask();
        ++pool->busyNum;
        pthread_mutex_unlock(&pool->mutexPool);

        printf("thread %ld start working...\n",pthread_self());

        task.function(task.arg);
        delete task.arg;
        task.arg = nullptr;

        printf("thread %ld end working...\n",pthread_self());

        pthread_mutex_lock(&pool->mutexPool);
        --pool->busyNum;
        pthread_mutex_unlock(&pool->mutexPool);
    }
    return nullptr;
}

inline void ThreadPool::threadExit(){
    pthread_t tid = pthread_self();
    for(int i = 0;i < maxNum;++i){
        if(workerIDs[i] == tid){
            workerIDs[i] = 0;
            printf("threadExit() called %ld exiting...",tid);
            break;
        }
    }
    pthread_exit(NULL);
}

inline void ThreadPool::addTask(callback func,void* arg){
    if(shutdown){
        return;
    }
    taskQ->addTask(Task(func,arg));
    pthread_cond_signal(&isEmpty);
}

inline void ThreadPool::addTask(const Task& t){
    if(shutdown){
        return;
    }
    taskQ->addTask(t);
    pthread_cond_signal(&isEmpty);
}

inline const int ThreadPool::getBusyNum(){
    pthread_mutex_lock(&mutexPool);
    int busy = busyNum;
    pthread_mutex_unlock(&mutexPool);
    return busy;
}

inline const int ThreadPool::getAliveNum(){
    pthread_mutex_lock(&mutexPool);
    int alive = liveNum;
    pthread_mutex_unlock(&mutexPool);
    return alive;
}