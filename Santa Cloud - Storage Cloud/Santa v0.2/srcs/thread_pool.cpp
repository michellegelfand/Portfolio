//michelle gelfand


#include <memory>       //unique_ptr
#include <utility>      //std::move
#include <chrono>       //std::chrono
#include <thread>       //std::thread

#include "lock_guard.hpp"
#include "thread_pool.hpp"
#include "tptask.hpp"


namespace ilrd
{

bool compare_func(std::unique_ptr<TPTask>& task1, std::unique_ptr<TPTask>& task2)
{
    return *task1 < *task2;
} 


class StopCall : public std::runtime_error
{   
public:
    StopCall(std::string str) : std::runtime_error(str) { }
};

//******************************************************************************
class StopTask : public TPTask
{
public:
	StopTask(): TPTask(TPTask::Priority::STOP) { }
    ~StopTask() = default;

	inline void execute() override 
    {
        throw StopCall("Stop");
    }
};


ThreadPool::ThreadPool(size_t thread_num)
    :m_active(true), m_queue(compare_func)
{
    if ( 0 == thread_num)
	{
		thread_num = DEFAULT_NUM_OF_THREADS;
	}

    for(size_t i=0; i< thread_num; ++i)
    {
        //new thread
		std::thread new_thread(&ThreadPool::thread_func, this);
        // std::thread::id my_id = std::this_thread::get_id();
		//pair thread and status for vector 
		std::pair<std::thread, ThreadStatus> new_pair(std::move(new_thread), ThreadStatus::RUNNING);
        
        m_pool[new_pair.first.get_id()] = std::move(new_pair);
    }
}

ThreadPool::~ThreadPool()
{
    for(auto& pair : m_pool)
    {
        m_pool[pair.first].first.join();
    }
}


void ThreadPool::thread_func()
{
    try
    {
        while((true == m_active.load(std::memory_order_relaxed)) &&
        m_pool[std::this_thread::get_id()].second == ThreadStatus::RUNNING) 
        {

            std::unique_ptr<TPTask> task;
            m_queue.pop(task);
            
            task->execute();            
        } 
    }
    catch(const StopCall& e)
    {
        Lockguard<std::mutex> lock(&m_mutex);
        m_pool[std::this_thread::get_id()].second = ThreadStatus::STOPPED;
        m_cv.notify_all();
        m_active = false;

    }
    catch(const std::exception& e)
    {
        std::cerr << "  ThreadPool::thread_func: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "caught unknown error in ThreadPool::thread_func" 
        << std::endl;

    }
}

void ThreadPool::add_task(std::unique_ptr<TPTask> task)
{
   Lockguard<std::mutex> lock(&m_mutex);
    m_queue.push(std::move(task));
}


void ThreadPool::set_size(size_t size)
{
  /*   size_t curr_thread_count = get_size();
    ssize_t delta = size - curr_thread_size;
    
    if(delta < 0)
    {
        delta *= -1;

        for(ssize_t i=0; i<delta; ++i)
        {
           // m_queue.push(std::move(//badapple));//bad apples
        }
    }
    else
    {
        
        for(ssize_t i=0; i<delta; ++i)
        {
            //add thread
            /* m_pool.push(std::thread::);
             */
       // }
   // } 
}




size_t ThreadPool::get_size() const
{
	return m_pool.size();
}


void ThreadPool::stop(std::chrono::seconds timeout)
{
    try
    {
        std::this_thread::sleep_for(timeout);
        size_t thread_num = get_size();

        for(size_t i = 0 ; i < thread_num ; ++i)
        {
            std::unique_ptr<TPTask> stop_task(new StopTask());
            
            add_task(std::move(stop_task));
        }
        for (auto& itr : m_pool)
        {
            if (itr.second.second ==  ThreadPool::ThreadStatus::STOPPED)
            {
                itr.second.first.join();
            }
        }

        std::cout << "\n\n\n\n\n\nnum of threads: " << get_size() << std::endl;

    }
    
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    /* size_t thread_num = get_size();

    for(size_t i = 0 ; i < thread_num ; ++i)
    {
        std::unique_ptr<TPTask> stop(new TaskStop());
        
        add_task(std::move(stop));
    } */
}

void ThreadPool::suspend()
{
 /*    m_active = false;

    size_t size = m_pool.size();

    for (size_t i = 0; i < size; ++i)
    {
        std::unique_ptr<SuspendTask>suspend_task (new SuspendTask(*this));
        add_task(std::move(suspend_task));
    } */
}

void ThreadPool::resume()
{

}


}//ilrd
