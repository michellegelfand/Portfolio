#ifndef __SLAVE_GATEWAY_HPP__
#define __SLAVE_GATEWAY_HPP__

#include <memory>   //std::unique_ptr

#include "gateway.hpp"
#include "arg_data.hpp"
#include "driver_data.hpp"
#include "driver_proxy.hpp"

namespace ilrd
{

class SlaveGateWay : public GateWay<unsigned int, ArgData>
{
public:
    SlaveGateWay(int fd, 
                std::unique_ptr<DriverProxy>& driver,
                std::unique_ptr<Storage>& storage,
                int* running);
                
    ~SlaveGateWay() = default;
    
            //request type   , arguments factory needs
    std::pair<unsigned int, ArgData> read() override;

private:
    std::unique_ptr<DriverProxy>& m_driver;
    std::unique_ptr<Storage>& m_storage;
    int* m_running;
};

}//namespace ilrd

#endif //__SLAVE_GATEWAY_HPP__

