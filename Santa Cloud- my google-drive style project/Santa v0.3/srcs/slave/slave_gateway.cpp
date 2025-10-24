#include <unistd.h>     //read
#include <iostream>

#include "../../include/slave_gateway.hpp"

namespace ilrd
{

SlaveGateWay::SlaveGateWay(int fd, 
                            std::unique_ptr<DriverProxy>& driver,
                            std::unique_ptr<Storage>& storage,
                            int* running)
    : GateWay(fd), m_driver(driver), m_storage(storage), m_running(running)
{}

std::pair<unsigned int, ArgData> SlaveGateWay::read()
{
  std::cout << "entered slave read" << std::endl;
    ArgData args(m_driver, m_storage, m_running);
std::cout << "created argdata" << std::endl;
    args.m_request = m_driver->receive_request();
std::cout << "recieved request" << std::endl;
    unsigned int key = static_cast<unsigned int>(args.m_request->get_type());
std::cout << "got type" << std::endl;
    return std::make_pair(key, std::move(args));

}

} //namespace ilrd
