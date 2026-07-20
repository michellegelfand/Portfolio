#ifndef __DRIVER_PROXY_HPP__
#define __DRIVER_PROXY_HPP__

/**
 * We are creating a generic driver to manage requests to store and get data.
 * 
 * The function receive_request creates and returns a std::unique_ptr to a  
 * DriverData object.
 * 
 * The function send_reply receives a std::unique_ptr to a DriverData object.
 * 
 * The disconnect function allows to initiate a disconnect process in a 
 * controlled manner : activated upon a SIG_TERM, keypress 'q', or at end of 
 * programm.
 * 
 * This class provides getter and setter for the data.
 * 
 * This class is uncopyable and unmovable.
 * 
 * File:   driver_proxy.hpp
 * Date:   07.11.19
 * Author: Michelle Gelfand
 * */

#include <string>       // std:string
#include <exception>    //std::runtime

#include "driver_data.hpp"

namespace ilrd
{

class DriverProxy
{
public:
    DriverProxy() = default;

    virtual ~DriverProxy() = 0;

    virtual std::unique_ptr<DriverData> receive_request() =  0;  
    virtual void send_reply(std::unique_ptr<DriverData> data) = 0;
    virtual void disconnect() = 0;
    int get_request_fd() const; 
    void set_request_fd(int fd);

    DriverProxy(const DriverProxy& other) = delete;             
    DriverProxy& operator=(const DriverProxy& other) = delete;  
    DriverProxy(DriverProxy&& other) = delete;                      
    DriverProxy& operator=(DriverProxy&& other) = delete;           
    
private:
    int m_request_fd;
};

}   //namespace ilrd

#endif //__DRIVER_PROXY_HPP__
