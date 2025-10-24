#include <sys/socket.h>		//recvfrom, sendto	
#include <sys/types.h>		//recvfrom, sendto	
#include <stdexcept>        //std::runtime_error, std::exception
#include <unistd.h>         //close
#include <memory>           //std::unique_ptr, std::make_unique
#include <strings.h>        //bzero
#include <arpa/inet.h>		//INADDR_ANY	
#include <string.h>		    //strerror

#include "../include/slave_driver.hpp"
#include "../include/handleton.hpp"
#include "../include/driver_data.hpp"
#include "../include/logger.hpp"

namespace ilrd
{

const char* IP = "10.3.0.28";

SlaveDriver::SlaveDriver(int port_num)
{


    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(-1 == sockfd)
    {
        
        throw(std::runtime_error("UDP socket creation failed"));
    }

    struct sockaddr_in name;

    bzero(&name, sizeof(name));

    name.sin_family = AF_INET;
    name.sin_port = htons(port_num);
    name.sin_addr.s_addr = inet_addr(IP);

    if(-1 == connect(sockfd, (struct sockaddr*)&name, sizeof(name))) 
    {
        throw(std::runtime_error("UDP socket bind failed"));
    }

    set_request_fd(sockfd);
}

SlaveDriver::~SlaveDriver()
{

    try
    {
        close(get_request_fd());
    }
    catch(const std::runtime_error& e)
    {
  

        std::cerr << e.what() << std::endl;
    }
}

std::unique_ptr<DriverData> SlaveDriver::receive_request()
{
std::cout << "|||||||||||||recieved request" << std::endl;

    size_t offset = 0;
    int req_id = 0;
    int len = 0;
    int req_type = 0;
    char buff[4136];

    int n_bytes = 0;
    read_all(buff, 4136);
    
    sscanf(buff, "%lu;%d;%d;%d;", &offset, &len, &req_id, 
                                        &req_type);



    char *iter = buff;
    while('\0' != *iter)
    {
        ++iter;
    }
    ++iter;

    std::cout << "|||||||||||||req_type" << req_type << std::endl;

       std::unique_ptr<DriverData> data(
        new DriverData(offset, len, static_cast<DriverData::action_type_t>(req_type), req_id));
    
    //If the request is WRITE, then we need to read the data and fill
    //the DriverData buffer with the information to be written to storage
    if(DriverData::action_type_t::WRITE == (data->get_type()))
    {
        std::copy(iter, iter + data->get_length(),
                    data->access_buffer().data());
    }

    return data;
} 

void SlaveDriver::send_reply(std::unique_ptr<DriverData> data)
{
    if(((67108864 > data->get_offset()) || 
        (data->get_type() != DriverData::action_type_t::WRITE)))
    {

        
        const size_t max_size = 4136;
        std::vector<char> reply_msg(max_size);

        sprintf(reply_msg.data(), "%d;%d;%d;%c",
                                    data->get_length(),
                                    data->get_request_id(),
                                    static_cast<int>(data->get_type()),
                                    '\0');
        
        Lockguard<std::mutex> lock(&m_mutex);

        auto iter = reply_msg.data() + strlen(reply_msg.data()) + 1;
        
        std::copy(data->access_buffer().data(), 
                data->access_buffer().data() + data->get_length(),
                iter);
        
        write_all(reply_msg.data(), max_size);
    }
}

void SlaveDriver::disconnect()
{}

//helper functions
//ensures read fully finished its operation, not interrupted midway
void SlaveDriver::read_all(char* buffer, size_t count)
{
    int bytes_read = 0;

    while(count) 
    {
        bytes_read = read(get_request_fd(), buffer, count);

        if(0 < bytes_read)
        {
            buffer += bytes_read;
            count -= bytes_read;
        }
        else
        {
            throw(std::runtime_error("read_all failed"));
        }
    }
}

//ensures write fully finished its operation, not interrupted midway
void SlaveDriver::write_all(char* buffer, size_t count)
{
    int bytes_written = 0;

    while(count) 
    {
        bytes_written = write(get_request_fd(), buffer, count);

        if(0 < bytes_written)
        {
            buffer += bytes_written;
            count -= bytes_written;
        }
        else
        {

            throw(std::runtime_error("write_all failed"));
        }
    }
}

}//namespace ilrd

