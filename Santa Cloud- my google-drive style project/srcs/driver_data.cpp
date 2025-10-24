
/**
 * This class encapsulates the requests and replies.
 * It is passed through the program inside a a std::unique_ptr.
 * 
 * Access to buffer is provided for read and write access.
 * 
 * write_to_buffer recieves char* to the data that needs to be transfered
 * and the number of bytes.
 * 
 * File:   driver_data.hpp
 * Date:   07.11.19
 * Author: Michelle Gelfand
 * */

#include<iostream> // std::cout
#include<string.h> // memcpy

#include "../include/logger.hpp"
#include "../include/driver_data.hpp"

namespace ilrd
{
//handle is equivalent to uid for recognition


    DriverData::DriverData(action_type type, char* handle, 
                           size_t offset, unsigned int length)	
    : m_type(type), m_offset(offset), m_length(length), m_status(-1)
    {

//copy handle recieved into DriverData handle
        memcpy(m_handle, handle, m_HANDLE_SIZE);
        m_buffer.resize(m_length);
    }


    DriverData::~DriverData()
    {


    }


    DriverData::action_type DriverData::get_type() const
    {
        return m_type;
    }


    char* DriverData::get_handle()
    {
        return m_handle;
    }


    size_t DriverData::get_offset() const
    {
        return m_offset;
    }


    unsigned int DriverData::get_length() const
    {
        return m_length;
    }


    int DriverData::get_status() const
    {
        return m_status;
    }


    void DriverData::set_status(int status)
    {
        m_status = status;
    }


    std::vector<char>& DriverData::access_buffer()
    {
        return m_buffer;
    }


    size_t DriverData::get_handle_size() 
    {
        return m_HANDLE_SIZE;
    }

} // namespace ilrd
