#include <unistd.h> //read

#include "nbd_gateway.hpp"

namespace ilrd
{

NBDGateWay::NBDGateWay(int fd, 
                        std::unique_ptr<DriverProxy>& driver,
                        std::unique_ptr<Storage>& storage,
                        int* running)
    : GateWay(fd), m_driver(driver), m_storage(storage), m_running(running)
{}

std::pair<unsigned int, MasterData> NBDGateWay::read()
{

    MasterData args(m_driver, m_storage, m_running);

    //recieve request from nbd
    args.m_request = m_driver->receive_request();

    unsigned int key = static_cast<unsigned int>(args.m_request->get_type());

    return std::make_pair(key, std::move(args));
}

} //namespace ilrd
