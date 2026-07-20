#include <utility>      //std::move, std::ref

#include "../../include/slave_tasks.hpp"
#include "../../include/arg_data.hpp"

namespace ilrd
{

SlaveReadTask::SlaveReadTask(re_priority priority, re_request request, 
                                re_driver driver, re_storage storage)
    : RETask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver)),
      m_storage(std::ref(storage))
{}

void SlaveReadTask::execute()
{
    m_reply = m_storage->read(std::move(m_request));

    m_driver->send_reply(std::move(m_reply));
}

std::unique_ptr<RETask> SlaveReadTask::create(ArgData args)
{
    return std::unique_ptr<RETask>(new SlaveReadTask(re_priority::HIGH,
                                                std::move(args.m_request),
                                                args.m_driver,
                                                args.m_storage));
}

//----- SlaveWriteTask ---------------------------------------------------------
SlaveWriteTask::SlaveWriteTask( re_priority priority, re_request request, 
                                re_driver driver, re_storage storage)
    : RETask(priority), 
      m_request(std::move(request)), 
      m_reply(nullptr), 
      m_driver(std::ref(driver)),
      m_storage(std::ref(storage))
{}

void SlaveWriteTask::execute()
{
    m_reply = m_storage->write(std::move(m_request));

    m_driver->send_reply(std::move(m_reply));
}

std::unique_ptr<RETask> SlaveWriteTask::create(ArgData args)
{
    return std::unique_ptr<RETask>(new SlaveWriteTask(re_priority::HIGH,
                                                std::move(args.m_request),
                                                args.m_driver,
                                                args.m_storage));
}

} //namespace ilrd
