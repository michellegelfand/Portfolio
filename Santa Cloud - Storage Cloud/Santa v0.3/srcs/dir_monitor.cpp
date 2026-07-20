#include <unistd.h>         //read
#include <iostream>         //std::cout
#include <sys/inotify.h>    //inotify
#include <memory>           // std::unique_ptr

#include "../include/logger.hpp"               
#include "../include/handleton.hpp"            
#include "../include/monitor.hpp"
#include "../include/dir_monitor.hpp"
#include "../include/epoll_wrapper.hpp"

namespace ilrd
{

DirMonitor::DirMonitor(const std::string& path)
    :   m_dispatcher(),
        m_path(path),
        m_running(true),
        m_thread(&DirMonitor::monitor, this)
{ 
    //blank
}


DirMonitor::~DirMonitor()
{
    m_running = false;
    m_thread.join();
}


Dispatcher<std::string>* DirMonitor::get_dispatcher()
{
    return (&m_dispatcher);
}


void DirMonitor::monitor()
{
    int inotify_fd = 0;
    int watch_fd = 0;

    try
    {
        constexpr int NAME_MAX = 180;

        std::unique_ptr<Monitor> fd_monitor(new epoll_wrapper(1));

        if(-1 == (inotify_fd = inotify_init1(0)))
        {
            throw std::runtime_error("failed monitor: inotify_init");
        }

        if(-1 == (watch_fd = inotify_add_watch(inotify_fd, m_path.c_str(), 
                                            IN_MOVED_TO | IN_CLOSE_WRITE)))
        {
            throw std::runtime_error("failed monitor: inotify_add watch");
        }

        fd_monitor->add(inotify_fd, Monitor::READ);

        while(m_running)
        {
            int num_of_fds = fd_monitor->wait(6000);

 

            if(0 < num_of_fds)
            {


                const size_t length = sizeof(struct inotify_event) + NAME_MAX + 1;

                char* buff = new char[length];

                read(inotify_fd, buff, length);



                m_dispatcher.notify_all(m_path + "/" + 
                            reinterpret_cast<inotify_event*>(buff)->name + "\0");
            }
        }

        clean_up(inotify_fd, watch_fd);
    }
    catch(const std::exception& e)
    {
        clean_up(inotify_fd, watch_fd);

    }
    
}

//----- clean_up ---------------------------------------------------------------
void DirMonitor::clean_up(int inotify_fd, int watch_fd)
{
    //inotify_rm_watch(inotify_fd, watch_fd);
    close(watch_fd);
    close(inotify_fd);
}

} // namespace ilrd

