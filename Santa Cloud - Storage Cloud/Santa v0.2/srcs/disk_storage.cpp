#include <sys/types.h> //truncate64
#include <iostream> // cout
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include "../include/disk_storage.hpp"
#include "../include/lock_guard.hpp"
#include "../include/logger.hpp"
#include "../include/test_tools.hpp"

namespace ilrd
{

DiskStorage::DiskStorage(const std::string& path, size_t f_size) :
m_fd(open(path.c_str(), O_RDWR | O_CREAT | O_TRUNC))
{

    if(-1 ==  m_fd)
    {

        throw(std::runtime_error("diskStorage open Failed"));
    }

    truncate64(path.c_str(), f_size);
}


DiskStorage::~DiskStorage()
{

    if(-1 == close(m_fd))
    {

        throw(std::runtime_error("diskStorage close failed"));
    }
}


std::unique_ptr<DriverData> DiskStorage::read(std::unique_ptr<DriverData> data)
{


   lseek(m_fd, data->get_offset(), SEEK_SET);

   if(-1 == ::read(m_fd, data->access_buffer().data(), data->get_length()))
   {

       throw(std::runtime_error("diskStorage read failed"));
   }
#ifdef DO_DEBUG
	std::cout << GREEN"\nDISK Storage - read " << std::endl;
	std::cout << GREEN"offset- " << data->get_offset();
	std::cout << GREEN" length- " << data->get_length()<< WHITE << std::endl;
#endif

    return data;
}


std::unique_ptr<DriverData> DiskStorage::write(std::unique_ptr<DriverData> data)
{

   lseek(m_fd, data->get_offset(), SEEK_SET);
    
   if(-1 == ::write(m_fd, data->access_buffer().data(), data->get_length()))
   {

       throw(std::runtime_error("diskStorage write failed"));
   }
   
   #ifdef DO_DEBUG
	std::cout << YELLOW"\nDisk Storage - write " << std::endl;
	std::cout << YELLOW"offset- " << data->get_offset();
	std::cout << YELLOW" length- " << data->get_length()<< WHITE << std::endl;
#endif
   return data;
}

} // namespace ilrd

