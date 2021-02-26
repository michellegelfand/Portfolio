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
#include "dir_monitor.hpp"
#include "dll_loader.hpp"
#include "retask.hpp"
#include "gateway.hpp"
#include "monitor.hpp"
#include "epoll_wrapper.hpp"

namespace ilrd
{

template <typename Key, typename Args>
class RequestEngine final
{
public:
    //if hardware_concurrency() not supported, default to 4
    explicit RequestEngine(const std::string& monitor_path, size_t num_of_threads = std::thread::hardware_concurrency());
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

private:
    Factory<RETask, Key, Args>* m_factory;
    ThreadPool m_pool;
    std::unordered_map<int, GateWay<Key, Args>*> m_gateways;
    std::unique_ptr<Monitor> m_monitor;
    DirMonitor m_dir_monitor; 
    DllLoader m_dll_loader;
    bool m_active;     
};


template <typename Key, typename Args>
RequestEngine<Key, Args>::RequestEngine(const std::string& monitor_path, 
                                           size_t num_of_threads)
    : m_pool(num_of_threads),
      m_monitor(new epoll_wrapper(100)), 
      m_dir_monitor(monitor_path),
      m_dll_loader(m_dir_monitor), 
      m_active(true)
{
#ifdef DO_DEBUG
      std::cout << "request engine ctor" << std::endl;
#endif
}


template <typename Key, typename Args>
RequestEngine<Key, Args>::~RequestEngine()
{ 
#ifdef DO_DEBUG
    std::cout << "request engine dtor" << std::endl;
#endif
}


template <typename Key, typename Args>
void RequestEngine<Key, Args>::add_task(const Key& key, CreatorFunc creator)
{
#ifdef DO_DEBUG
    std::cout << "request engine add_task" << std::endl;
#endif
    m_factory->add(key, creator);
}



template <typename Key, typename Args>
void RequestEngine<Key, Args>::add_gateway(GateWay<Key, Args>* gateway)
{   //m_gateways is unorderedmap. fd is key
    m_gateways.emplace(gateway->get_fd(), gateway);
}



template <typename Key, typename Args>
void RequestEngine<Key, Args>::set_threads_num(size_t num)
{
   // m_pool.set_size(num);
}


template <typename Key, typename Args>
void RequestEngine<Key, Args>::run()
{
    for(auto& gateway : m_gateways)
    {
        //m_monitor  : base class epoll derives from 
        m_monitor->add(gateway->get_fd());
    }

    while(m_active)
    {
        //epoll wait
        int nfds = m_monitor->wait(-1);
        
        if(-1 == nfds)
        {
            m_active = false;
            return;
        }

        for(int i = 0 ; i < nfds ; ++i)
        {
            auto fd = (*m_monitor)[i];
                                            //returns what factory needs
            auto new_task = m_factory->create(m_gateways[fd]->read());
            
            m_pool.add_task(std::move(new_task));
        }
    }
}




}//namespace ilrd

#endif //__REQUEST_ENGINE_HPP__
