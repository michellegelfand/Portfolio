#include <iostream>         //cout
#include <sys/inotify.h>    //inotify
#include <unistd.h>         //read
#include <thread>

#include "dir_monitor.hpp"
#include "logger.hpp"               
#include "handleton.hpp"  
#include "monitor.hpp"
#include "epoll_wrapper.hpp"


namespace ilrd
{

const size_t MAX_NAME = 256;

DirMonitor::DirMonitor(const std::string& path)
    : m_path(path), m_running(true), m_thread(&DirMonitor::monitor, this)
{
                                        //thread func^, ^argument

   /* Handleton<Logger>::get_instance()->Log((Logger::Severity::DEBUG), std::this_thread::get_id(),"~", __FILE__, __LINE__, "Dir monitor ctor");  */
                                          
}

DirMonitor::~DirMonitor()
{
   /*  Handleton<Logger>::get_instance()->Log((Logger::Severity::DEBUG), std::this_thread::get_id(),"~", __FILE__, __LINE__, "Dir monitor dtor");  */

    m_running = false;
    m_thread.join();

}

Dispatcher<std::string>* DirMonitor::get_dispatcher()
{
    return &m_dispatcher;
}

void close_dir_monitor(int inotify_fd, int watch_fd)
{
    inotify_rm_watch(inotify_fd, watch_fd);
    close(watch_fd);
    close(inotify_fd);
}

void DirMonitor::monitor()
{

    int inotify_fd = 0;
    int watch_fd = 0;
    try
    {
        std::unique_ptr<Monitor> dir_epoll(new epoll_wrapper(4));

        if(-1 == (inotify_fd = inotify_init1(0)))
        {
            //create inotify, return its file descriptor

            //0 for no flags
            throw std::runtime_error("Failed inotify_init");
        }

        watch_fd = inotify_add_watch(inotify_fd, m_path.c_str(), 
                                                    IN_CREATE | IN_MODIFY);

        if(-1 == watch_fd)
        {
            //add directory we want to monitor

            //report on events of create and modify

            throw std::runtime_error("Failed inotify_add_watch");
        }

        dir_epoll->add(inotify_fd, Monitor::event_type::READ);

        while(true == m_running)
        {
            std::cout << "in while" << std::endl;
            //number of file descriptors
            int nfds = dir_epoll->wait(5000);


            std::cout << "after wait " << nfds << m_path << std::endl;
           /*  Handleton<Logger>::get_instance()->Log((Logger::Severity::INFO), std::this_thread::get_id(),"~", __FILE__, __LINE__, "Dir monitor: change occured in shared folder");  */
            if(-1 == nfds)
            {
                std::cout << "nfds == -1" <<std::endl;
                throw std::runtime_error("nfds = -1\n");
            }
            if(0 < nfds)
            {
                std::cout << "change noted" << std::endl;
                struct inotify_event event;

                //read from watch_fd into event
                //src, dest, size( size set recommended in man page)
                read(inotify_fd, &event, 
                                sizeof(struct inotify_event) + MAX_NAME + 1);
                //read is blocking until event occurs

                //based on "return" value of read (placed in event struct" we know what type of event occured
                m_dispatcher.notify_all(event.name);
            }

        }

        close_dir_monitor(inotify_fd, watch_fd);
    }
    catch(const std::exception& e)
    {/* 
        Handleton<Logger>::get_instance()->Log((Logger::Severity::DEBUG), std::this_thread::get_id(),"exception", __FILE__, __LINE__, "Dir monitor: monitor: exception. calling close"); */
      
        std::cout << e.what() << std::endl;

        close_dir_monitor(inotify_fd, watch_fd);
    }
}


}//ilrd

