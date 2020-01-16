#include "../include/driver_proxy.hpp"

namespace ilrd
{

int ProxyDriver::get_fd() const
{
    return m_request_fd;
}

void ProxyDriver::set_fd(int fd) 
{
    m_request_fd = fd;
}

ProxyDriver::~ProxyDriver()
{
   //blank
}


}//ilrd