#ifndef __NBD_GATEWAY_HPP__
#define __NBD_GATEWAY_HPP__

#include <memory> //std::unique_ptr

#include "gateway.hpp"
#include "master_data.hpp"

namespace ilrd
{

class NBDGateWay : public GateWay<unsigned int, MasterData>
{
public:
    NBDGateWay(int fd, 
               std::unique_ptr<DriverProxy>& driver,
               std::unique_ptr<Storage>& storage,
               int* running);
                
    ~NBDGateWay() = default;
    
    std::pair<unsigned int, MasterData> read() override;

private:
    std::unique_ptr<DriverProxy>& m_driver;
    std::unique_ptr<Storage>& m_storage;
    int* m_running;
};

}//ilrd

#endif //__NBD_GATEWAY_HPP__

