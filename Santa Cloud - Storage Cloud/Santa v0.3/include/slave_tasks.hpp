#ifndef __SLAVE_TASKS_HPP__
#define __SLAVE_TASKS_HPP__

#include <mutex>        //std::mutex
#include <memory>       //std::unique_ptr
#include <utility>      //std::move, std::ref

#include "retask.hpp"
#include "storage.hpp"
#include "driver_data.hpp"
#include "driver_proxy.hpp"
#include "nbd_gateway.hpp"


namespace ilrd
{

using re_priority = RETask::Priority; 
using re_request = std::unique_ptr<DriverData>; 
using re_driver = std::unique_ptr<DriverProxy>&;
using re_storage = std::unique_ptr<Storage>&;
using re_run = int*;

class SlaveReadTask : public RETask
{
public:
    SlaveReadTask(re_priority priority, re_request request, re_driver driver,
             re_storage storage);

    void execute();

    static std::unique_ptr<RETask> create(ArgData args);
    
private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    std::unique_ptr<DriverProxy>& m_driver;
    std::unique_ptr<Storage>& m_storage;
};



class SlaveWriteTask : public RETask
{
public:
    SlaveWriteTask(re_priority priority, re_request request, re_driver driver,
             re_storage storage);

    void execute();

    static std::unique_ptr<RETask> create(ArgData args);

private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    std::unique_ptr<DriverProxy>& m_driver;
    std::unique_ptr<Storage>& m_storage;
};

} //namespace ilrd

#endif //__SLAVE_TASKS_HPP__
