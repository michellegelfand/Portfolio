#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

/**
 * Thread Pool follows Object Pool Design Pattern.
 * Threads perform the tasks according to their priority. 
 * 
 * A Task must provide:
 *      1) execute() function 
 *      2) operator < (for std::less)
 */

#include <thread>               // std::thread
#include <vector>               // vector
#include <chrono>               // std::chrono::seconds
#include <mutex>                // std::mutex
#include <condition_variable>   // std::condition_variable
#include <list>                 // std::list
#include <atomic>               // std::atomic
#include <utility>              // std::pair
#include <unordered_map>

#include "../include/tptask.hpp"
#include "../include/waitable_pqueue.hpp"
#include "../include/lock_guard.hpp"


namespace ilrd
{

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
    // If the new ammount is less than the prev. tpthread_cancel(pt);hus the <delta> threads that 
    // finish their tasks first will be removed from the pool.
    void set_size(size_t size);

    // Returns the total number of threads in the pool
    size_t get_size() const;

    // Permenantly stops after timeout, 
    // (!) caution:resources may be lost.
    void stop(std::chrono::seconds timeout);
    void stop(); //violent shut dount

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
    enum class ThreadState
    {
        RUNNING,
        SUSPENDED,
        FINISHED
    };

    // std::function is a general-purpose polymorphic function wrapper.
    // will be usd by WaitablePQueue to compare std::unique_ptrs'
    using Compare = std::function <bool (std::unique_ptr<TPTask>& task1, 
                                         std::unique_ptr<TPTask>& task2)>;
    
    WaitablePQueue<std::unique_ptr<TPTask>,
                    std::vector<std::unique_ptr<TPTask>>, 
                    Compare> m_queue;

    size_t m_finished_counter;
    bool m_suspended;
    std::condition_variable m_cv;
    mutable std::mutex m_mutex;
    
    std::unordered_map<std::thread::id,std::pair<std::thread, ThreadState>>m_pool;
    
    void thread_func();
    void resume_threads();
    void add_threads(size_t num);
    void add_stops(size_t num);
    void add_suspend(size_t num);
    void collect_threads(std::chrono::seconds sec, bool violent);
    void erase_threads(std::vector<std::thread::id>& to_erase);
    void join_finished_threads(std::vector<std::thread::id>& to_erase);
    void violent_join_threads(std::vector<std::thread::id>& to_erase);
};

} // ilrd

#endif //__THREAD_POOL_HPP__