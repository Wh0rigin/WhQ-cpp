#ifndef __TASKQUEUE__
#define __TASKQUEUE__

#include <deque>
#include <pthread.h>

using callback = void (*)(void* arg);

template <typename T>
struct Task{
    inline explicit Task<T>():function(nullptr),arg(nullptr){}
    inline explicit Task<T>(callback f,void* arg):function(f),arg(static_cast<T*>(arg)){}
    callback function;
    T* arg;
};

template <typename T>
class TaskQueue{
public:
    explicit TaskQueue();
    ~TaskQueue();

    void addTask(const Task<T>& task);
    void addTask(callback f,void* arg);
    const Task<T> takeTask();
    inline const size_t taskNum(){
        return m_taskQ.size();
    }
private:
    pthread_mutex_t m_mutex;    
    std::deque<Task<T>> m_taskQ;   //任务队列
};

#endif