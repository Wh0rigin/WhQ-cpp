#include "TaskQueue.h"

inline TaskQueue::TaskQueue(){
    pthread_mutex_init(&m_mutex,NULL);
}

inline TaskQueue::~TaskQueue(){
    pthread_mutex_destroy(&m_mutex);
}

//添加任务
inline void TaskQueue::addTask(const Task& task){
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push_back(task);
    pthread_mutex_unlock(&m_mutex);
}

inline void TaskQueue::addTask(callback f,void* arg){
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push_back(Task(f,arg));
    pthread_mutex_unlock(&m_mutex);
}

//拿出任务
inline const Task TaskQueue::takeTask(){
    Task t;
    pthread_mutex_lock(&m_mutex);
    if(!m_taskQ.empty()){
        t = m_taskQ.front();
        m_taskQ.pop_front();
    }
    pthread_mutex_unlock(&m_mutex);
    return t;
}