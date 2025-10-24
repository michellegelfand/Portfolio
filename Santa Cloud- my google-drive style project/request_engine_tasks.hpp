#ifndef __REQUEST_ENGINE_TASKS__
#define __REQUEST_ENGINE_TASKS__

#include "tptask.hpp"
#include "driver_data.hpp"
#include "nbd_driver_proxy.hpp"
#include "driver_proxy.hpp"
#include "storage.hpp"

namespace ilrd
{

using tp_priority = TPTask::Priority; 
using tp_request = std::unique_ptr<DriverData>; 

class ReadTask : public TPTask
{
public:
    ReadTask(tp_priority priority, tp_request request, ProxyDriver& driver,
             Storage& storage);

    void execute();

    static std::unique_ptr<TPTask> create(tp_request request, 
                                          ProxyDriver& driver,
                                          Storage& storage,  
                                          int running);
    
private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    ProxyDriver& m_driver;
    Storage& m_storage;
};

class WriteTask : public TPTask
{
public:
    WriteTask(tp_priority priority, tp_request request, ProxyDriver& driver,
             Storage& storage);

    void execute();

    static std::unique_ptr<TPTask> create(tp_request request, ProxyDriver& driver, Storage& storage, int running);

private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    ProxyDriver& m_driver;
    Storage& m_storage;
};


class DisconnectTask : public TPTask
{
public:
    DisconnectTask(tp_priority priority, tp_request request, ProxyDriver& driver, int running);

    void execute();

    static std::unique_ptr<TPTask> create(tp_request request, 
                                          ProxyDriver& driver,
                                          Storage& storage, 
                                          int running);
    
private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    ProxyDriver& m_driver;
    int m_running;
};


class ReplyTask : public TPTask
{
public:
    ReplyTask(tp_priority priority, tp_request request, ProxyDriver& driver);

    void execute();

    static std::unique_ptr<TPTask> create(tp_request request, 
                                          ProxyDriver& driver,
                                          Storage& storage,
                                          int running);
    
private:
    std::unique_ptr<DriverData> m_request;
    std::unique_ptr<DriverData> m_reply;
    ProxyDriver& m_driver;

};




}//ilrd











#endif //__REQUEST_ENGINE_TASKS__