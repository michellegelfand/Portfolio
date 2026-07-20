#ifndef __TASKS_HPP__
#define __TASKS_HPP__

#include <memory>       //std::unique_ptr
#include <utility>      //std::move, std::ref
#include <mutex>        //std::mutex

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

//ReadTask_________________________________________________________________
class ReadTask : public RETask
{
public:
    ReadTask(re_priority priority, re_request request, re_driver driver,
             re_storage storage);

    void execute();

    static std::unique_ptr<RETask> create(ArgData args);
    
private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    std::unique_ptr<DriverProxy>& m_driver;
    std::unique_ptr<Storage>& m_storage;
};


//WriteTask_________________________________________________________________
class WriteTask : public RETask
{
public:
    WriteTask(re_priority priority, re_request request, re_driver driver,
             re_storage storage);

    void execute();

    static std::unique_ptr<RETask> create(ArgData args);

private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    std::unique_ptr<DriverProxy>& m_driver;
    std::unique_ptr<Storage>& m_storage;
};

//DisconnectTask_________________________________________________________________
class DisconnectTask : public RETask
{
public:
    DisconnectTask(re_priority priority, re_request request, re_driver driver,
                    re_run running);

    void execute();

    static std::unique_ptr<RETask> create(ArgData args);
    
private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    std::unique_ptr<DriverProxy>& m_driver;
    int* m_running;
};

//ReplyTask_________________________________________________________________
class ReplyTask : public RETask
{
public:
    ReplyTask(re_priority priority, re_request request, re_driver driver);

    void execute();

    static std::unique_ptr<RETask> create(ArgData args);
    
private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    std::unique_ptr<DriverProxy>& m_driver;
};

//StdinTask_________________________________________________________________
class StdinTask : public RETask
{
public:
    StdinTask(re_priority priority, re_driver driver, re_run running, 
                bool stdin_flag);

    void execute();

    static std::unique_ptr<RETask> create(ArgData args);
    
private:
    std::unique_ptr<DriverProxy>& m_driver;
    int* m_running;
    bool m_stdin_flag;
};

} //namespace ilrd

#endif //__TASKS_HPP__
