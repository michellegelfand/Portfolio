#ifndef __DIR_MONITOR_HPP__
#define __DIR_MONITOR_HPP__


#include <string>
#include <thread>

#include "callback_dispatcher.hpp"

namespace ilrd
{

class DirMonitor
{
public:
    explicit DirMonitor(const std::string& path);
    ~DirMonitor();

    Dispatcher<std::string>* get_dispatcher();

    DirMonitor(const DirMonitor&) = delete;
    DirMonitor& operator=(const DirMonitor&) = delete;
    DirMonitor(DirMonitor&&) = delete;
    DirMonitor& operator=(DirMonitor&&) = delete;

private:

    void monitor(); 
    Dispatcher<std::string> m_dispatcher;
    std::string m_path; 
    std::thread m_thread;
    bool m_running;

	void clean_up(int inotify_fd, int watch_fd);
};

} //ilrd


#endif //__DIR_MONITOR_HPP__
