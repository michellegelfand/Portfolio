#include <algorithm>    // std::copy

#include "nbd_data.hpp"

namespace ilrd
{

NbdData::NbdData(size_t offset, int length, action_type_t req_type, int req_id,
                    char* handle) 
    : DriverData(offset, length, req_type, req_id), m_status(0) 
{
    std::copy(handle, handle + HANDLE_SIZE, m_handle);  
}

const char* NbdData::NbdData::get_handle() const
{
    return (m_handle);
}

int NbdData::get_status() const
{
    return m_status;
}

void NbdData::set_status(int status)
{
    m_status = status;
}

} //namespace ilrd


