#include<cstring>
#include<vector>
#include <iostream>

#include "../include/test_tools.hpp"
#include "../include/ram_storage.hpp"

namespace ilrd
{
RAMStorage::RAMStorage(size_t Storage_size)
	:m_buffer(std::vector<char>(Storage_size, 0))
{
	//blank
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
			  m_buffer.begin() + data->get_offset() + data->get_length(),
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
	std::copy(data->access_buffer().begin(), data->access_buffer().end(),
			m_buffer.begin() + data->get_offset() );  


	return data;
}

}//ilrd
