#ifndef __NBD_DRIVE_HPP__
#define __NBD_DRIVE_HPP__

/**
 * File:   nbd_drive.hpp
 * Date:   07.11.19
 * Author: Michelle Gelfand*/
 
 /*
    Sets up nbd driver proxy;
    ntohl & ntohll for transforming little endian to big endian 
    for network and vice versa.
    request: READ writes from storage to request buffer
             WRITE writes from request buffer to storage
    reply:  WRITE: returns reply OK
            READ: returns OK + buffer read  

*/


#include <string> // std:string
#include <thread> // std::thread

#include "driver_proxy.hpp"

namespace ilrd
{

class NBDDriverProxy;         // instead of NBDOptions
class Storage; 
class DriverData;


class NBDDriverProxy: public ProxyDriver
{
public:
    NBDDriverProxy(const std::string& dev_file, size_t storage_size);
    NBDDriverProxy(const std::string& dev_file, 
                   size_t block_size,  
                   size_t num_blocks);

    ~NBDDriverProxy() override; 

    std::unique_ptr<DriverData> receive_request() override;  
    void send_reply(std::unique_ptr<DriverData> data) override;
    void disconnect() override;
    
    
    NBDDriverProxy(const NBDDriverProxy& other) = delete;            
    NBDDriverProxy& operator=(const NBDDriverProxy& other) = delete;  
    NBDDriverProxy(NBDDriverProxy&& other) = delete;                  
    NBDDriverProxy& operator=(NBDDriverProxy&& other) = delete;       
    
private:

    int m_nbd_fd;//socket, other socket is in driver proxy
    int m_dev_fd;//open file
    std::thread m_nbd_thread;
    int m_disconnect;
    void m_thread_func();
    void set_flags();
    void read_all(int fd, char* buf, size_t len);
    void write_all(int fd, char* buf, size_t len);
};

}   //namespace ilrd

#endif //__NBD_DRIVE_HPP__
