#ifndef __SLAVE_DRIVER_HPP__
#define __SLAVE_DRIVER_HPP__

/**
 * We are creating a driver to manage requests to store and get data on the 
 * slave computers.
 * 
 * The function receive_request creates and returns a std::unique_ptr to a  
 * DriverData object.
 * 
 * The function send_reply receives a std::unique_ptr to a DriverData object.
 * 
 * ?
 * The disconnect function allows to initiate a disconnect process in a 
 * controlled manner : activated upon a SIG_TERM, keypress 'Q', or at end of 
 * programm.
 * 
 * This class provides getter and setter for the data.
 * 
 * This class is uncopyable and unmovable.
 * 
 * File:   slave_driver.hpp
 * Date:   07.12.19
 * Author: Michelle Gelfand
 * */

#include <mutex>        //std::mutex

#include "driver_proxy.hpp"
#include "driver_data.hpp"

namespace ilrd
{

class SlaveDriver : public DriverProxy
{
public:
    explicit SlaveDriver(int port_num);

    ~SlaveDriver() override; 

    std::unique_ptr<DriverData> receive_request() override;  
    void send_reply(std::unique_ptr<DriverData> data) override;
    void disconnect() override;
    
    SlaveDriver(const SlaveDriver& other) = delete;             
    SlaveDriver& operator=(const SlaveDriver& other) = delete;  
    SlaveDriver(SlaveDriver&& other) = delete;                  
    SlaveDriver& operator=(SlaveDriver&& other) = delete;       
    
private:
    std::mutex m_mutex;
    size_t m_msg_size;
    
    void read_all(char* buffer, size_t count);
    void write_all(char* buffer, size_t count);
};

}//namespace ilrd

#endif //__SLAVE_DRIVER_HPP__
