/**
 * Michelle Gelfand
 * 
 * Thread Pool follows Object Pool Design Pattern.
 * Threads perform the tasks according to their priority. 
 * 
 * A Task must provide:
 *      1) execute() function 
 *      2) operator < (for std::less)
 */


#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <unordered_map>        //hash
#include <thread>               // std::thread
#include <vector>               // vector
#include <chrono>               //std::chrono::seconds
#include <atomic>               // std::atomic
#include <utility>              // std::pair
#include <condition_variable>   // std::condition_variable
#include <mutex>                // std::mutex

#include "tptask.hpp"
#include "tptask.hpp"
#include "waitable_pqueue.hpp"

namespace ilrd
{

/* class Compare
{
public:
    bool operator()(const std::unique_ptr<TPTask>& task1,
                    const std::unique_ptr<TPTask>& task2)
    {
        return *task1 < *task2;
    }
};
 */


/* bool compare(std::unique_ptr<TPTask>& task1, std::unique_ptr<TPTask>& task2)
{
    return *task1 < *task2;
}  */
class ThreadPool
{

public:
    static const size_t DEFAULT_NUM_OF_THREADS = 4;
    
    //if hardware_concurrency not supported please enter value manually
    explicit ThreadPool(size_t thread_num = std::thread::hardware_concurrency());

    ~ThreadPool();

    // Adding Task to the queue (when task finished its exex. it's removed from 
    // the queue)
    void add_task(std::unique_ptr<TPTask> task);

    // Setting new ammount of threads (incrementing / decrementing). 
    // If the new ammount is less than the prev. thus the <delta> threads that 
    // finish their tasks first will be removed from the pool.
    void set_size(size_t size);

    // Returns the total number of threads in the pool
    size_t get_size() const;

    // Permenantly stops after timeout, 
    // (!) caution:resources may be lost.
    void stop(std::chrono::seconds timeout);

    // Temporarily pauses the threads immediately after finnishing of the 
    // currently running tasks, without danger of losing resources.
    void suspend();

    // Resumes the suspended threads.
    void resume();

    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool& other) = delete;
    ThreadPool(ThreadPool&& other) = delete;
    ThreadPool& operator=(ThreadPool&& other) = delete;

private:

    friend class SuspendTask; //friend to grant private access to s_active
    friend class TaskStop;
   
    enum class ThreadStatus
    {
        RUNNING,
        SUSPENDED,
        STOPPED
    };

    static const std::chrono::milliseconds stop_timeout;
    
    // std::function is a general-purpose polymorphic function wrapper.
    // will be usd by WaitablePQueue to compare std::unique_ptrs'
    using Compare = std::function <bool (std::unique_ptr<TPTask>& lhs, 
                                         std::unique_ptr<TPTask>& rhs)>;
    
    //task queue
    WaitablePQueue<std::unique_ptr<TPTask>, 
                        std::vector<std::unique_ptr<TPTask>>, Compare> m_queue;

    //thread hash
    std::unordered_map<std::thread::id, std::pair<std::thread, ThreadStatus>> m_pool;

   // bool m_stop;
    //unsigned int m_busy;

    static const std::chrono::milliseconds s_stop_timeout;

    /* static */ std::atomic<bool>m_active;
    /* static */ std::condition_variable m_cv;
    /* static */ std::mutex m_mutex;

    void thread_func();

};





} // ilrd

#endif //__THREAD_POOL_HPP__


