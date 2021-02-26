#ifndef __ARG_DATA_HPP__
#define __ARG_DATA_HPP__

#include "driver_data.hpp"
#include "driver_proxy.hpp"
#include "storage.hpp"

namespace ilrd
{

struct MasterData
{
    std::unique_ptr<DriverData> m_request;  //nbd parmeter
    std::unique_ptr<DriverProxy>& m_driver; //nbd parmeter
    std::unique_ptr<Storage>& m_storage;    //nbd parmeter
    int* m_running;                      //nbd parmeter
    bool m_stdin_flag;                      //flag for the use of stdin gateway

    MasterData(std::unique_ptr<DriverProxy>& driver,
            std::unique_ptr<Storage>& storage,
            int* running);
            
    ~MasterData() = default;

    MasterData(const MasterData& other) = delete;
    MasterData& operator=(const MasterData& other) = delete;
    MasterData(MasterData&& other) = default;
    MasterData& operator=(MasterData&& other) = default;
};

}//namespace ilrd

#endif //__ARG_DATA_HPP__
