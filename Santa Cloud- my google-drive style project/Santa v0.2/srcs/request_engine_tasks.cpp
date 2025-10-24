#include "../include/request_engine_tasks.hpp"
#include "../include/handleton.hpp"
#include "../include/logger.hpp"

namespace ilrd
{

extern Logger* logger;

ReadTask::ReadTask(tp_priority priority, tp_request request, ProxyDriver& driver,
                    Storage& storage)
    : TPTask(priority), m_request(std::move(request)), m_reply(nullptr), 
      m_driver(std::ref(driver)), m_storage(std::ref(storage))
{
    //blank
}

void ReadTask::execute()
{
    m_reply = m_storage.read(std::move(m_request));

    logger->Log(Logger::Severity::INFO, 
                std::this_thread::get_id(),
                std::string("~"),
                __FILE__,
                __LINE__, 
                std::string("ReadTask"));

    m_driver.send_reply(std::move(m_reply));
}

std::unique_ptr<TPTask> ReadTask::create(tp_request request, 
                                          ProxyDriver& driver,
                                          Storage& storage,
                                          int running)
{
    (void)running;

    return std::unique_ptr<TPTask>(new ReadTask(tp_priority::MEDIUM,
                                                std::move(request),
                                                std::ref(driver),
                                                std::ref(storage)));
}


WriteTask::WriteTask(tp_priority priority, tp_request request, ProxyDriver& driver,
                    Storage& storage)
    : TPTask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver)),
      m_storage(std::ref(storage))
{
    //blank
}

void WriteTask::execute()
{
    m_reply = m_storage.write(std::move(m_request));

    logger->Log(Logger::Severity::INFO, 
                std::this_thread::get_id(),
                std::string("~"),
                __FILE__,
                __LINE__, 
                std::string("WriteTask"));

    m_driver.send_reply(std::move(m_reply));
}

std::unique_ptr<TPTask> WriteTask::create(tp_request request, 
                                          ProxyDriver& driver,
                                          Storage& storage,
                                          int running)
{
    (void) running;

    return std::unique_ptr<TPTask>(new WriteTask(tp_priority::MEDIUM,
                                                 std::move(request),
                                                 std::ref(driver),
                                                 std::ref(storage)));
}


DisconnectTask::DisconnectTask(tp_priority priority, tp_request request, 
                                ProxyDriver& driver, int running)
    : TPTask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver)),
      m_running(running)
{
    //blank
}
                    
void DisconnectTask::execute()
{
    m_reply = std::move(m_request);
    m_running = false;

    logger->Log(Logger::Severity::INFO, 
                std::this_thread::get_id(),
                std::string("~"),
                __FILE__,
                __LINE__, 
                std::string("DisconnectTask"));
    
    m_driver.send_reply(std::move(m_reply));
}

std::unique_ptr<TPTask> DisconnectTask::create(tp_request request, 
                                                ProxyDriver& driver,
                                                Storage& storage,
                                                int running)
{
    (void) storage;

    return std::unique_ptr<TPTask>(new DisconnectTask(tp_priority::MEDIUM,
                                                      std::move(request),
                                                      std::ref(driver),
                                                      running));
}


ReplyTask::ReplyTask(tp_priority priority, tp_request request, 
                             ProxyDriver& driver)
    : TPTask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver))
{
    //blank
}

void ReplyTask::execute()
{
    m_reply = std::move(m_request);

    logger->Log(Logger::Severity::INFO, 
                std::this_thread::get_id(),
                std::string("~"),
                __FILE__,
                __LINE__, 
                std::string("ReplyTask"));

    m_driver.send_reply(std::move(m_reply));
}

std::unique_ptr<TPTask> ReplyTask::create(tp_request request, 
                                              ProxyDriver& driver,
                                              Storage& storage,
                                              int running)
{
    (void) storage;
    (void) running;

    return std::unique_ptr<TPTask>(new ReplyTask(tp_priority::MEDIUM,
                                                     std::move(request),
                                                     std::ref(driver)));
}





}//ilrd