#ifndef __TASKQUEUE__
#define __TASKQUEUE__

#include <deque>
#include <pthread.h>

using callback = void (*)(void* arg);

struct Task{
    inline explicit Task():function(nullptr),arg(nullptr){}
    inline explicit Task(callback f,void* arg):function(f),arg(arg){}
    callback function;
    void* arg;
};

class TaskQueue{
public:
    inline explicit TaskQueue();
    inline ~TaskQueue();

    inline void addTask(const Task& task);
    inline void addTask(callback f,void* arg);
    inline const Task takeTask();
    inline const int taskNum(){
        return m_taskQ.size();
    }
private:
    pthread_mutex_t m_mutex;    
    std::deque<Task> m_taskQ;   //任务队列
};

#endif