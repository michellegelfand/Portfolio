#ifndef __REQUEST_ENGINE_HPP__
#define __REQUEST_ENGINE_HPP__

/**
 * Request Engine needs be configured to create different RETasks, using a 
 * different number of threads, and monitoring to different file descriptors
 * for new requestd to be handled.
 * */

#include <unordered_map>

#include "handleton.hpp"
#include "factory.hpp"
#include "thread_pool.hpp"
#include "retask.hpp"
#include "gateway.hpp"
#include "epoll_wrapper.hpp"

namespace ilrd
{

template <typename Key, typename Args>
class RequestEngine final
{
public:
    //if hardware_concurrency() not supported, default to 4
    explicit RequestEngine(const std::string& monitor_path, 
                size_t num_of_threads = std::thread::hardware_concurrency());

    ~RequestEngine();

    RequestEngine(const RequestEngine& other) = delete;
    RequestEngine& operator=(const RequestEngine& other) = delete;
    RequestEngine(const RequestEngine&& other) = delete;
    RequestEngine& operator=(const RequestEngine&& other) = delete;
    
    using CreatorFunc = std::function<std::unique_ptr<RETask>(Args args)>; 

    void add_gateway(GateWay<Key, Args>* gateway);
    void add_task(const Key& key, CreatorFunc creator);
    void set_threads_num(size_t num);
    
    void run();

    int* get_running_flag();

private:
    Factory<RETask, Key, Args>* m_factory;
    ThreadPool m_pool;
    std::unordered_map<int, GateWay<Key, Args>*> m_gateways;
    std::unique_ptr<Monitor> m_monitor;
    int m_running;
};

template <typename Key, typename Args>
RequestEngine<Key, Args>::RequestEngine(const std::string& monitor_path, 
                                            size_t num_of_threads)
    : m_factory(Handleton<Factory<RETask, Key, Args>>::get_instance()), 
      m_pool(num_of_threads), m_monitor(new epoll_wrapper(10)) 
      ,m_running(1)
{
    //blank
}

template <typename Key, typename Args>
RequestEngine<Key, Args>::~RequestEngine()
{
    m_running = 0;
    m_pool.set_size(0);

}

template <typename Key, typename Args>
void RequestEngine<Key, Args>::add_gateway(GateWay<Key, Args>* gateway)
{

    m_gateways.emplace(gateway->get_fd(), gateway);
}

template <typename Key, typename Args>
void RequestEngine<Key, Args>::add_task(const Key& key, CreatorFunc creator)
{

    m_factory->add(key, creator);
}

template <typename Key, typename Args>
void RequestEngine<Key, Args>::set_threads_num(size_t num)
{

    m_pool.set_size(num);
}

template <typename Key, typename Args>
void RequestEngine<Key, Args>::run()
{
    //add gateways containing file descriptors for epoll to wait on
    for(auto& iter : m_gateways)
    {
        m_monitor->add(iter.first, Monitor::event_type::READ);
    }
std::cout << "gateways added" << std::endl;
    while(m_running)
    {
        //returns num of fd that popped up with request
        int num_of_fds_ready = m_monitor->wait(-1);
        std::cout << "waited" << std::endl;
        //if thread - nbd_do_it got stuck
        if(-1 == num_of_fds_ready)
        {
            std::cout << "wait failed 1" << std::endl;
            m_running = 0;
        }

        if(0 == num_of_fds_ready)
        {
            std::cout << "wait failed 2" << std::endl;
            m_running = 0;
        }

    //run over popped file descriptors
        for(int i = 0 ; i < num_of_fds_ready ; ++i)
        {
            //read gateway's filedescriptor, the gateway key is the place in hash
             std::cout << "before read" << std::endl;
                std::pair<Key, Args> new_pair = 
                        m_gateways[(*m_monitor)[i].get_fd()]->read();
                std::cout << "read" << std::endl;
                std::unique_ptr<RETask> new_task = 
                                m_factory->create(new_pair.first, 
                                                std::move(new_pair.second));
                std::cout << "new task made" << std::endl;
                m_pool.add_task(std::move(new_task));
                std::cout << "task added" << std::endl;
            
        }
    }
}

template <typename Key, typename Args>
int* RequestEngine<Key, Args>::get_running_flag()
{
    return &m_running;
}

}//namespace ilrd

#endif //__REQUEST_ENGINE_HPP__
