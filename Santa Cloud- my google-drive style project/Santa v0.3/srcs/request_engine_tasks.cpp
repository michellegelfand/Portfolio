#include <utility>      //std::move, std::ref

#include "../include/arg_data.hpp"
#include "../include/request_engine_tasks.hpp"

namespace ilrd
{

//ReadTask______________________________________________________________________
ReadTask::ReadTask(re_priority priority, re_request request, re_driver driver,
                    re_storage storage)
    : RETask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver)),
      m_storage(std::ref(storage))
{}

void ReadTask::execute()
{
    m_reply = m_storage->read(std::move(m_request));

    m_driver->send_reply(std::move(m_reply));
}

std::unique_ptr<RETask> ReadTask::create(ArgData args)
{
    return std::unique_ptr<RETask>(new ReadTask(re_priority::HIGH,
                                                std::move(args.m_request),
                                                args.m_driver,
                                                args.m_storage));
}

//WriteTask_____________________________________________________________________
WriteTask::WriteTask(re_priority priority, re_request request, re_driver driver,
                    re_storage storage)
    : RETask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver)),
      m_storage(std::ref(storage))
{}

void WriteTask::execute()
{
    m_reply = m_storage->write(std::move(m_request));

    m_driver->send_reply(std::move(m_reply));
}

std::unique_ptr<RETask> WriteTask::create(ArgData args)
{
    return std::unique_ptr<RETask>(new WriteTask(re_priority::HIGH,
                                                std::move(args.m_request),
                                                args.m_driver,
                                                args.m_storage));
}

//DisconnectTask________________________________________________________________
DisconnectTask::DisconnectTask(re_priority priority, re_request request, 
                                re_driver driver, re_run running)
    : RETask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver)),
      m_running(running)
{}
                    
void DisconnectTask::execute()
{

    m_driver->send_reply(std::move(m_reply));
    *m_running = 0;
}

std::unique_ptr<RETask> DisconnectTask::create(ArgData args)
{
    return std::unique_ptr<RETask>(new DisconnectTask(re_priority::HIGH,
                                                      std::move(args.m_request),
                                                      args.m_driver,
                                                      args.m_running));
}

//ReplyTask_________________________________________________________________
ReplyTask::ReplyTask(re_priority priority, re_request request, 
                             re_driver driver)
    : RETask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver))
{}

void ReplyTask::execute()
{
    m_reply = std::move(m_request);


    m_driver->send_reply(std::move(m_reply));
}

std::unique_ptr<RETask> ReplyTask::create(ArgData args)
{
    return std::unique_ptr<RETask>(new ReplyTask(re_priority::HIGH,
                                                     std::move(args.m_request),
                                                     args.m_driver));
}


//StdinTask_________________________________________________________________

StdinTask::StdinTask(re_priority priority, re_driver driver, re_run running, 
                        bool stdin_flag)
    : RETask(priority), 
      m_driver(driver),
      m_running(running),
      m_stdin_flag(stdin_flag)
{}

void StdinTask::execute()
{
    if(false == m_stdin_flag)
    {
        m_driver->disconnect();
    }
}

std::unique_ptr<RETask> StdinTask::create(ArgData args)
{
    return std::unique_ptr<RETask>(new StdinTask(re_priority::HIGH,
                                                 args.m_driver,
                                                 args.m_running,
                                                 args.m_stdin_flag));
}

} //namespace ilrd
