#ifndef __DRIVER_PROXY_HPP__
#define __DRIVER_PROXY_HPP__

/*
//TODO finish the description
 * !! ADD DESCRIPTION
 * we want to build a generic driver that recieves and returns ......
 * 
 * File:   driver_proxy.hpp
 * Date:   07.11.19
 * Author: Michelle Gelfand
 * 
 */

#include <string> // std:string
#include "../include/driver_data.hpp"

namespace ilrd
{

class NBDDriverProxy;   
class DriverData;


class ProxyDriver
{
public:
    ProxyDriver() = default;
    virtual ~ProxyDriver() = 0; 

    virtual std::unique_ptr<DriverData> receive_request() =  0;  
    virtual void send_reply(std::unique_ptr<DriverData> data) = 0;
    virtual void disconnect() = 0;
    int get_fd() const; //request fd
    void set_fd(int fd);

    ProxyDriver(const ProxyDriver& other) = delete;             
    ProxyDriver& operator=(const ProxyDriver& other) = delete;  
    ProxyDriver(ProxyDriver&& other) = delete;                  
    ProxyDriver& operator=(ProxyDriver&& other) = delete;       
    
private:
    int m_request_fd;
};


} // namespace ilrd

#endif //__DRIVER_PROXY_HPP__
