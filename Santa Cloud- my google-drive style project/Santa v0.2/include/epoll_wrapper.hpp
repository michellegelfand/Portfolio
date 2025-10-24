#ifndef __EPOLL_WRAPPER_HPP__
#define __EPOLL_WRAPPER_HPP__

#include <vector>
#include <sys/epoll.h>

#include "monitor.hpp"

namespace ilrd
{

class epoll_wrapper: public Monitor
{
public:
    epoll_wrapper(size_t max_events );
    ~epoll_wrapper();

    void add(int fd, uint32_t flag) override;
    void remove(int fd) override;
    int wait(int timeout) override;
    int operator[] (int) override;

private:
    size_t m_max_events;
    int m_epoll_fd;
    std::vector<struct epoll_event> m_events;
};



}



#endif //__EPOLL_WRAPPER_HPP__
