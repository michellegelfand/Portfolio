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
 * 
 * File:   driver_data.hpp
 * Date:   07.11.19
 * Author: Michelle Gelfand
 * */

#include <string> // std:string
#include <thread> // std::thread
#include <vector> //std::vector

namespace ilrd
{

class DriverData
{
public:

    typedef enum struct action_type 
    {
        READ = 0,
        WRITE,
        DISCONNECT,
        FLUSH,
        TRIM
    }action_type_t;

    ~DriverData(); 

    DriverData(action_type type, 
               char* handle, 
               size_t offset,
               unsigned int length);

    DriverData(const DriverData& other) = default;
    DriverData& operator=(const DriverData& other) = default;  
    DriverData(DriverData&& other) = default;                  
    DriverData& operator=(DriverData&& other) = default; 


    action_type get_type() const;

    //const char* get_handle() const;
    char *get_handle(); //npon const because requires conversion to char*
    size_t get_offset() const;
    unsigned int get_length() const;
    int get_status() const;

    void set_status(int status);


    std::vector<char>& access_buffer(); 
    static size_t get_handle_size(); 

private:
    
    static const size_t m_HANDLE_SIZE = 8; 
    action_type m_type;
    char m_handle[m_HANDLE_SIZE]; 
    size_t m_offset;
    unsigned int m_length;
    std::vector<char> m_buffer;
    int m_status;           //0 success, -1 failure
    int m_disconnect;
};

}   //namespace ilrd

#endif //__DRIVER_DATA_HPP__
