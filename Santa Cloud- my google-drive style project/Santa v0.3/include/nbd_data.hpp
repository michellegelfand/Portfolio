#ifndef __NBD_DATA_HPP__
#define __NBD_DATA_HPP__

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

#include "driver_data.hpp"

namespace ilrd
{

class NbdData : public DriverData
{
public:

    NbdData(size_t offset,
            int length,
            action_type_t req_type,
            int req_id,
            char* handle);

    NbdData(const NbdData& other) = default;
    NbdData& operator=(const NbdData& other) = default;  
    NbdData(NbdData&& other) = default;                  
    NbdData& operator=(NbdData&& other) = default; 

    ~NbdData() = default; 

    const char* get_handle() const;

    int get_status() const;
    void set_status(int status);
    
private:
    static const size_t HANDLE_SIZE = 8; //moved here from DateDriver
    
    char m_handle[HANDLE_SIZE];  //moved here from DateDriver
    int m_status;           //0 success, -1 failure

};

}   //namespace ilrd

#endif //__NBD_DATA_HPP__
