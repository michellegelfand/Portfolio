/**
 * Implementation of pure virtual destractor as well as the getter and 
 * setter for the private data member.
 * 
 * File:   driver_proxy.cpp
 * Date:   07.11.19
 * Author: Olga Komarovsky Chashka
 * */

#include "../include/driver_proxy.hpp"

namespace ilrd
{
//Pure virtual destructor implementation
DriverProxy::~DriverProxy()
{ }

int DriverProxy::get_request_fd() const
{
    return m_request_fd;
} 

void DriverProxy::set_request_fd(int fd)
{
    m_request_fd = fd;
}

}   //namespace ilrd

