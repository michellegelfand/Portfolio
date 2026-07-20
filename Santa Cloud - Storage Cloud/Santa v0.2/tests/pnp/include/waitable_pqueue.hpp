#ifndef _WAITABLE_PQUEUE_H_
#define _WAITABLE_PQUEUE_H_

//wrapper over priority queue
//with waitable pop,and with the addition of timeout 
//
//Author:

#include <chrono>   //std::chrono
#include <mutex>    //std::mutex, unique_lock
#include <vector>   //std::vector
#include <queue>    //std::pqueue
#include <condition_variable> //std::condition_variable

#include "lock_guard.hpp"
#include "inbar_tools.hpp"

namespace ilrd
{

//How to get Container and Compare ???
template <class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>>
class WaitablePQueue
{
public:
    WaitablePQueue() = default;
    explicit WaitablePQueue(const Compare& compare_func);
    ~WaitablePQueue() = default;

    void push(const T& data);
    void push(T&& data);
    void pop(T& return_obj);
    bool pop(T& return_obj, std::chrono::seconds seconds);
    bool empty() const;
    size_t size() const;

    WaitablePQueue(const WaitablePQueue& other) = delete;
    WaitablePQueue(WaitablePQueue&& other) = delete;
    WaitablePQueue& operator=(const WaitablePQueue& other) = delete;
    WaitablePQueue& operator=(WaitablePQueue&& other) = delete;

private:
    std::priority_queue<T, Container, Compare> m_pqueue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
};



//******************************************************************************
template <class T, class Container, class Compare >
WaitablePQueue<T, Container, Compare>::
WaitablePQueue(const Compare& compare_func) 
    : m_pqueue(compare_func) 
{
}

//******************************************************************************
template <class T, class Container, class Compare>
void WaitablePQueue<T, Container, Compare>::push(const T& data)
{
    std::unique_lock<std::mutex>lock(m_mutex);
    m_pqueue.push(std::move(data));
    m_cv.notify_one();
    DEBUG_ONLY(std::cout << "Push const T&" << std::endl);
}

//******************************************************************************
template <class T, class Container, class Compare>
void WaitablePQueue<T, Container, Compare>::push(T&& data)
{
    std::unique_lock<std::mutex>lock(m_mutex);
    m_pqueue.push(std::move(data));
    m_cv.notify_one();
    DEBUG_ONLY(std::cout << "Push T&&" << std::endl);
}

//******************************************************************************
template <class T, class Container, class Compare>
void WaitablePQueue<T, Container, Compare>::pop(T& return_obj)
{
    std::unique_lock<std::mutex>lock(m_mutex);

    m_cv.wait(lock, [this]{return !m_pqueue.empty();});

    return_obj = std::move(const_cast<T&>(m_pqueue.top()));

    m_pqueue.pop();
    DEBUG_ONLY(std::cout << "Pop without timeout" << std::endl);
}

//******************************************************************************
template <class T, class Container, class Compare>
bool WaitablePQueue<T, Container, Compare>::pop(T& return_obj, std::chrono::seconds seconds)
{
    std::unique_lock<std::mutex>lock(m_mutex);
 
    if(m_cv.wait_for(lock, seconds,[this]{return !m_pqueue.empty();}))
    {
        return_obj = std::move(const_cast<T&>(m_pqueue.top()));

        m_pqueue.pop();
        DEBUG_ONLY(std::cout << "Timeout Pop - succeded" << std::endl);
        return true;

    }
    //timed out
    DEBUG_ONLY(std::cout << "Timeout Pop - timed-out" << std::endl);
    return false;
}

//******************************************************************************
template <class T, class Container, class Compare>
bool WaitablePQueue<T, Container, Compare>::empty() const
{
    std::unique_lock<std::mutex>lock(m_mutex);
    DEBUG_ONLY(std::cout << "empty" << std::endl);
    return m_pqueue.empty();
}

template <class T, class Container, class Compare>
size_t WaitablePQueue<T, Container, Compare>::size() const
{
    DEBUG_ONLY(std::cout << "size" << std::endl);
    std::unique_lock<std::mutex>lock(m_mutex);
    return m_pqueue.size();
}

}//namespace ilrd

#endif //_WAITABLE_PQUEUE_H_
