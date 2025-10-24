#include <algorithm>    // copy
#include <sys/mman.h>   // mmap  
#include <unistd.h>     // close
#include <sys/types.h>  // open
#include <sys/stat.h>   // open
#include <fcntl.h>      // open

#include "../include/mmap_storage.hpp"
#include "../include/lock_guard.hpp"


namespace ilrd
{
MmapStorage::MmapStorage(size_t size, const std::string& path)
    : m_fd(open(path.c_str(), O_CREAT, 0660)),
      m_length(size),
      m_memory(nullptr)         
{
    if (-1 == m_fd)
    {

        throw std::runtime_error("faled to open file");
    }

    if(-1 == truncate64(path.c_str(), size))
    {

        close(m_fd);
        throw std::runtime_error("fail to truncate64");
    }

    m_memory = static_cast<char*>(mmap(0,                //allignment address
                                       m_length,         //memory size
                                       PROT_READ | PROT_WRITE,  //protection
                                       MAP_PRIVATE | MAP_POPULATE,  //flag
                                       m_fd,                    //file fd
                                       0));     //offset from beginning of file

    if (MAP_FAILED == m_memory)
    {   

        close(m_fd);
        throw std::runtime_error("mmap failed");
    }

}




MmapStorage::~MmapStorage()
{
    if(-1 == munmap(m_memory, m_length))
    {

    }

    close(m_fd);
}

std::unique_ptr<DriverData> MmapStorage::read(std::unique_ptr<DriverData> data)
{   
    std::copy(m_memory + data->get_offset(), 
              m_memory + data->get_offset() + data->get_length(), 
              data->access_buffer().begin());

#ifdef DO_DEBUG
	std::cout << GREEN"\nmmap Storage - read " << std::endl;
	std::cout << GREEN"offset- " << data->get_offset();
	std::cout << GREEN" length- " << data->get_length()<< WHITE << std::endl;
#endif


    return data;
}

std::unique_ptr<DriverData> MmapStorage::write(std::unique_ptr<DriverData> data)
{
    std::copy(data->access_buffer().begin(), 
              data->access_buffer().begin() + data->get_length(), 
              m_memory + data->get_offset());

#ifdef DO_DEBUG
	std::cout << GREEN"\nmmap Storage - write " << std::endl;
	std::cout << GREEN"offset- " << data->get_offset();
	std::cout << GREEN" length- " << data->get_length()<< WHITE << std::endl;
#endif

    return data;

}


}// namespace ilrd
