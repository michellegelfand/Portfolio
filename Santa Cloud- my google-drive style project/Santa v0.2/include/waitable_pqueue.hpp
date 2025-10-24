//thread safe wrapper over std::priority_queue
//with waitable pop,and with the addition of timeout 
//
//Author: Michelle Gelfand



#ifndef _WAITABLE_PQUEUE_H_
#define _WAITABLE_PQUEUE_H_

#include <chrono>		        // std::chrono
#include <mutex>		        // std::mutex, unique_lock
#include <queue>		        // std::priority_queue
#include <condition_variable>   // std::condition_variable
#include <vector>               // std::vector

namespace ilrd
{

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
    mutable std::mutex m_mutex; //mutable as to not hurt functions constness
    std::condition_variable m_cv;
};


template <class T, class Container, class Compare>
WaitablePQueue<T, Container, Compare>::WaitablePQueue(const Compare& compare_func) 
: m_pqueue(compare_func) 
{
    //blank
}



template <class T, class Container, class Compare >
void WaitablePQueue<T, Container, Compare>::push(const T& data)
{
    std::unique_lock<std::mutex> lock(m_mutex);


	m_pqueue.push(std::move(data));

   // std::cout << "\npushed: " << data;
    m_cv.notify_all();
}

template <class T, class Container, class Compare >
void WaitablePQueue<T, Container, Compare>::push(T&& data)
{
	std::unique_lock<std::mutex> lock(m_mutex);
    m_pqueue.push(std::move(data));
   // std::cout << "\npushed: " << data;

    m_cv.notify_all();
}


template <class T, class Container, class Compare >
bool WaitablePQueue<T, Container, Compare>::empty() const
{
	std::unique_lock<std::mutex> lock(m_mutex);
    return (m_pqueue.empty());
}

template <class T, class Container, class Compare >
size_t WaitablePQueue<T, Container, Compare>::size() const
{
    std::unique_lock<std::mutex> lock(m_mutex);
	return (m_pqueue.size());
}



template <class T, class Container, class Compare >
void WaitablePQueue<T, Container, Compare>::pop(T& return_obj)
{
    std::unique_lock<std::mutex> lock_for_pop(m_mutex);

    //wait until queue is not empty 
    m_cv.wait(lock_for_pop, [this]{return !m_pqueue.empty();});

    //pop by move
    return_obj = std::move( const_cast<T&>(m_pqueue.top()));

    //std::cout << "\npopped: " << return_obj;

	(m_pqueue.pop());

}

template <class T, class Container, class Compare >
bool WaitablePQueue<T, Container, Compare>::
pop(T& return_obj, std::chrono::seconds seconds)
{
    std::unique_lock<std::mutex> lock_to_pop(m_mutex);

    if(m_cv.wait_for(lock_to_pop, seconds, [this]{return !m_pqueue.empty();}))
    { 
        return_obj = std::move(const_cast<T&>(m_pqueue.top()));
	    (m_pqueue.pop());
        //std::cout << "\npopped: " << return_obj;
	    return true;
    }
    else
    {
        // std::cout << "\npop timed out";
        //timed out
        return false;
    }
}



}   //namespace ilrd

#endif //_WAITABLE_PQUEUE_H_

