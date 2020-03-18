#include <iostream>
#include<unistd.h>

#include "epoll_wrapper.hpp"

using namespace ilrd;

epoll_wrapper::epoll_wrapper(size_t max_events) 
: m_max_events(max_events), m_epoll_fd(epoll_create1(0))
{
    if (-1 == m_epoll_fd)
    {
        throw std::runtime_error("\nfailed creating epoll");
    }

    m_events.resize(max_events);
}


epoll_wrapper::~epoll_wrapper()
{
    close(m_epoll_fd);
}

void epoll_wrapper::add(int fd, uint32_t flag)
{
#ifdef DO_DEBUG
	std::cout << "\tfd " << fd << "added to event array\n"  ;
#endif
    struct epoll_event event;
    event.data.fd = fd;
    event.events  = flag;

//add fd to event array
    if(-1 == epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, fd, &event)) 
    {
        throw std::runtime_error("EPOLL_CTL_ADD failed");
    }
}

void epoll_wrapper::remove(int fd)
{
    //remove fd from event array
    if(-1 == epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, fd, NULL))
    {
        throw std::runtime_error("EPOLL_CTL_DEL failed");
    }

    close(fd);
}

int epoll_wrapper::wait(int timeout)
{
#ifdef DO_DEBUG
	std::cout << "\nepoll waiting"<< std::endl;
#endif
//number of file descriptors
    int nfds = 0;

//wait for event to pop up
    nfds = epoll_wait(m_epoll_fd, m_events.data(), m_max_events, timeout);
    if (-1 == nfds) 
    {
        //if wait was interrupted by signal ctrl C, nfds also returns -1
        perror("Epoll wait failed");
	
        if(errno != EINTR)
	    {
            //if NOT interrupted by ctrl C, so genuine error occured
	        throw(std::runtime_error("Epoll wait failed" ));
		}
    }

    return nfds;
}

int epoll_wrapper::operator[] (int idx) 
{
    //return fd of event @idx
    return m_events[idx].data.fd;
}
