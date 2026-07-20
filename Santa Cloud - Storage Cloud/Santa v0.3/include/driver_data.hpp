#ifndef __DRIVER_DATA_HPP__
#define __DRIVER_DATA_HPP__

/**
 * This class holds the data pertaining to requests to the driver and its
 * replies to them.
 * This class is passed through the program as a std::unique_ptr.
 * 
 * Each data member has a getter.
 * 
 * A setter for status is provided.
 * 
 * Access to buffer is provided for read and write access.
 * 
 * write_to_buffer recieves char* to the data that needs to be transfered
 * and the number of bytes.

 * */

#include <string> // std:string
#include <thread> // std::thread
#include <vector> //std::vector

#include "linux/nbd.h"  

namespace ilrd
{

class DriverData
{
public:

    typedef enum action_type_t 
    {
        READ = 0,
        WRITE,
        DISCONNECT,
        FLUSH,
        TRIM
    }action_type_t;

    DriverData( size_t offset,
                int length,
                action_type_t req_type,
                int req_id = -1);

    ~DriverData() = default;

    DriverData(const DriverData& other) = default;
    DriverData& operator=(const DriverData& other) = default;  
    DriverData(DriverData&& other) = default;                  
    DriverData& operator=(DriverData&& other) = default; 

    action_type_t get_type() const;
    void set_type(DriverData::action_type_t type);

    size_t get_offset() const;
    void set_offset(size_t offset);

    int get_request_id() const;
    void set_request_id(int req_id);
    
    int get_length() const;
    void set_length(int length);
    
    std::vector<char>& access_buffer();

private:   
    size_t m_offset;
    int m_length;
    action_type_t m_type;
    int m_req_id;
    std::vector<char> m_buffer;
};



}   //namespace ilrd

#endif //__DRIVER_DATA_HPP__
