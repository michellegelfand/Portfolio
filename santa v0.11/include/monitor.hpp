/*abstract base class epoll wrapper derives from

File:   monitor.hpp
Date:   07.11.19
Author: Michelle Gelfand*/


#ifndef __MONITOR_HPP__
#define __MONITOR_HPP__


namespace ilrd
{

class Monitor
{
private:
    /* data */
public:
    Monitor() = default;
    ~Monitor() = default;

    virtual void add(int fd, uint32_t val) = 0;
    virtual void remove(int fd) = 0;
    virtual int wait(int timeout) = 0; //for requests
    virtual int operator[] (int) = 0; //access ready events array
};

}

#endif //__MONITOR_HPP__