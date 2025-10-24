#include "../include/arg_data.hpp"

namespace ilrd
{

ArgData::ArgData(std::unique_ptr<DriverProxy>& driver,
                    std::unique_ptr<Storage>& storage,
                    int* running)
    : m_request(nullptr), m_driver(driver), m_storage(storage), 
        m_running(running), m_stdin_flag(true)
{}


}//namespace ilrd

