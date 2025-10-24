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

    class Event; // forward declaration

    enum event_type
	{
		READ = 0,
		WRITE,
		READ_WRITE,
		EXCEPTION
	};



    Monitor() = default;
    ~Monitor() = default;

    //virtual int get_fd()=0;
    
    virtual void add(int fd, event_type ops) = 0;
    virtual void remove(int fd) = 0;
    virtual int wait(int timeout) = 0; //for requests
    virtual Event operator[](size_t index) = 0; //access ready events array

};

}

#endif //__MONITOR_HPP__
