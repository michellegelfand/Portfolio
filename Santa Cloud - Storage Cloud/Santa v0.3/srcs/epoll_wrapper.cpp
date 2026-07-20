/**
 * We are implementing the epoll_wrapper class functions to allow us to monitor
 * a number of file descriptors at once using the epoll utility.
 * 
 * File:   epoll_wrapper.hpp
 * Author: Michelle Gelfand
 * */

#include <sys/epoll.h>      //epoll
#include <vector>           //vector
#include <exception>        //runtime_error
#include <unistd.h>         //close
#include <string.h>         //strerror
#include <exception> //runtime error
#include <iostream>//runtime error
#include <sys/epoll.h> //epoll struct
#include <stdexcept>


#include "../include/monitor.hpp"
#include "../include/epoll_wrapper.hpp"


namespace ilrd
{

//calls epoll_ctl function to setup epoll
// variadic template ..   var1 = str for error, var2... = args to ioctl
template <typename T, typename... Types>
void call_epoll_ctl(T var1, Types... var2)
{
    if(-1 == epoll_ctl(var2...))
    {
       
        throw(std::runtime_error(var1));
    }
}
    
epoll_wrapper::epoll_wrapper(size_t max_events)
        : m_epoll_fd(epoll_create1(0)),
          m_max_events(max_events),
          m_events(std::vector<struct epoll_event>(max_events))  
{
    if(-1 == m_epoll_fd)
    {
     
        throw(std::runtime_error("epoll_wrapper Ctor failed"));
    }
}

epoll_wrapper::~epoll_wrapper()
{

    close(m_epoll_fd);
}

void epoll_wrapper::add(int fd, event_type ops)
{
    u_int32_t flags;

    switch (ops)
    {
    case READ:
        flags = EPOLLIN;
        break;
    
    case WRITE:
        flags = EPOLLOUT;
        break;

    case READ_WRITE:
        flags = EPOLLIN | EPOLLOUT;
        break;

    default:
        break;
    }

    epoll_wrapper::Event new_event(fd, flags);


    call_epoll_ctl("epoll_wrapper::add failed", m_epoll_fd, EPOLL_CTL_ADD, fd,
                                                        &new_event.m_event);
}

void epoll_wrapper::remove(int fd)
{
    epoll_wrapper::Event new_event(fd, 0);

    call_epoll_ctl("epoll_wrapper::remove failed", m_epoll_fd, EPOLL_CTL_DEL, fd, 
                                                        &new_event.m_event);
}

int epoll_wrapper::wait(int timeout)
{
    std::cout << "entered epoll wait func" <<std::endl;
    int num_of_ready_fds = epoll_wait(m_epoll_fd, m_events.data(), 
                                      m_max_events, timeout);
std::cout << "num of ready fds returned" <<std::endl;
    if((-1 == num_of_ready_fds) && (errno != EINTR)) 
	{
        //blank
	}
	
	return num_of_ready_fds;
}

epoll_wrapper::Event epoll_wrapper::operator[](size_t index)
{
    return (Event(m_events[index]));
}

//Event class implementation for epoll_wrapper (epoll_wrapper events)
epoll_wrapper::Event::Event(int fd, uint32_t events)
{
    bzero(&m_event, sizeof(m_event));
    
    m_event.data.fd = fd;
    m_event.events = events;
}

epoll_wrapper::Event::Event(struct epoll_event event) : m_event(event)
{}

int epoll_wrapper::Event::get_fd() const
{
    std::cout << "epoll: got fd" << std::endl;
    return m_event.data.fd;
}

uint32_t epoll_wrapper::Event::get_event() const
{
    return m_event.events;
}

}
