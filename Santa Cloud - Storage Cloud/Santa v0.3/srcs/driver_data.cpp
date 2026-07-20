

#include <algorithm>    // std::copy
#include <iostream>

#include "../include/driver_data.hpp"


namespace ilrd
{

DriverData::DriverData(size_t offset, int length, action_type_t req_type,
                        int req_id)
    :   m_offset(offset),
        m_length(length), 
        m_type(req_type),
        m_req_id(req_id),
        m_buffer(static_cast<size_t>(length)) 
{
    
}

DriverData::action_type_t DriverData::get_type() const
{
    std::cout << "get_type" << m_type << std::endl;
    return m_type;
}

void DriverData::set_type(DriverData::action_type_t type) 
{
    m_type = type;
}

size_t DriverData::get_offset() const
{
    return m_offset;
}

void DriverData::set_offset(size_t offset) 
{
    m_offset = offset;
}

int DriverData::get_request_id() const
{
    return m_req_id;
}

void DriverData::set_request_id(int req_id)
{
    m_req_id = req_id;
}

int DriverData::get_length() const
{
    return m_length;
}

void DriverData::set_length(int length) 
{
    m_length = length;
}

std::vector<char>& DriverData::access_buffer()
{
    return m_buffer;
}

}   //namespace ilrd
