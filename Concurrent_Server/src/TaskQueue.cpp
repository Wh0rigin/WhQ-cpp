#include "TaskQueue.hpp"

template <typename T>
inline TaskQueue<T>::TaskQueue(){
    pthread_mutex_init(&m_mutex,NULL);
}

template <typename T>
inline TaskQueue<T>::~TaskQueue(){
    pthread_mutex_destroy(&m_mutex);
}

//添加任务
template <typename T>
inline void TaskQueue<T>::addTask(const Task<T>& task){
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push_back(task);
    pthread_mutex_unlock(&m_mutex);
}

template <typename T>
inline void TaskQueue<T>::addTask(callback f,void* arg){
    pthread_mutex_lock(&m_mutex);
    m_taskQ.push_back(Task<T>(f,arg));
    pthread_mutex_unlock(&m_mutex);
}

//拿出任务
template <typename T>
inline const Task<T> TaskQueue<T>::takeTask(){
    Task<T> t;
    pthread_mutex_lock(&m_mutex);
    if(!m_taskQ.empty()){
        t = m_taskQ.front();
        m_taskQ.pop_front();
    }
    pthread_mutex_unlock(&m_mutex);
    return t;
}