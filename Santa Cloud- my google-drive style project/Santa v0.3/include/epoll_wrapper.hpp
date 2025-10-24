#ifndef __epoll_wrapper_HPP__
#define __epoll_wrapper_HPP__

/**
 * We are implementing a Monitor Base Class interfce that allows us to monitor
 * a number of file descriptors at once using epoll_wrapper.
 * 
 * The nested class Event is a wrapper for struct epoll_wrapper_event, which is used by
 * the epoll_wrapper system utility.
 * 
 * File:   epoll_wrapper.hpp
 * Date:   13.11.19
 * Author: Michelle Gelfand
 * */

#include <vector>           //vector
#include <sys/epoll.h>      //epoll struct


#include "epoll_wrapper.hpp"      //epoll_wrapper
#include "monitor.hpp"

namespace ilrd
{
    
class epoll_wrapper: public Monitor
{
public:	
	epoll_wrapper(size_t max_events);
	~epoll_wrapper();
	//should we have an enum for read/write to allow portability?
	void add(int fd, event_type ops) override;
	void remove(int fd) override;
	int wait(int timeout) override;
	Event operator[](size_t index)  override;
    //should we keep Event or return fd?
	
private:
    int m_epoll_fd;
    size_t m_max_events;
    std::vector<struct epoll_event> m_events;
};


class epoll_wrapper::Event
{
public:
    Event(int fd, uint32_t events);
    explicit Event(struct epoll_event event);
    ~Event() = default;

    int get_fd() const;
    uint32_t get_event() const;

private:
    friend class epoll_wrapper;

    struct epoll_event m_event;
};

}

#endif //__epoll_wrapper_HPP__
