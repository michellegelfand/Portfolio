#include <iostream> // cout
#include<vector>

#include "../include/test_tools.hpp"
#include "../include/ram_storage.hpp"
#include "../include/lock_guard.hpp"
#include "../include/logger.hpp"

namespace ilrd
{



RAMStorage::RAMStorage(std::size_t size)
{
    m_buffer.resize(size);
}


RAMStorage::~RAMStorage()
{
    //blank
}


std::unique_ptr<DriverData> RAMStorage::read(std::unique_ptr<DriverData> data)
{

#ifdef DO_DEBUG
	std::cout << GREEN"\nRAM Storage - read " << std::endl;
	std::cout << GREEN"offset- " << data->get_offset();
	std::cout << GREEN" length- " << data->get_length()<< WHITE << std::endl;
#endif

//read from storage(m_buffer) to buffer(data->access_buffer())

//2 first parameters: input- from where to where we read from
//final parameter is where we write to
    std::copy(m_buffer.begin() + data->get_offset(),
              m_buffer.begin() + data->get_offset()+ data->get_length(),
              data->access_buffer().begin());

    return data;
}


std::unique_ptr<DriverData> RAMStorage::write(std::unique_ptr<DriverData> data)
{

#ifdef DO_DEBUG
	std::cout << YELLOW"\nRAM Storage - write " << std::endl;
	std::cout << YELLOW"offset- " << data->get_offset();
	std::cout << YELLOW" length- " << data->get_length()<< WHITE << std::endl;
#endif

//write from buffer to storage
    std::copy((data->access_buffer().begin()) ,
              (data->access_buffer().begin()) +  data->get_length(),
              (m_buffer.begin()) + data->get_offset());

    return data;
}

} // namespace ilrd
