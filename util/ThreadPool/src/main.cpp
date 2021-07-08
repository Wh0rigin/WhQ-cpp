#include "ThreadPool.hpp"
#include "ThreadPool.cpp"

void taskFunc(void* arg){
    int num = *(int*)arg;
    printf("thread %ld is working...,number = %d\n",pthread_self(),num);
    sleep(1);
}

int main(){
    ThreadPool<int>* pool = new ThreadPool<int>(3,10);
    for(int i = 0; i< 100;++i){
        int* num = new int(i + 10);
        pool->addTask(taskFunc,num);
    }

    sleep(30);

    return 0;
}