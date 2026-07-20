#ifndef __TPTASK_HPP__
#define __TPTASK_HPP__


#include <memory> //std::unique ptr
#include <functional>

namespace ilrd
{



class TPTask
{
public:
    enum Priority
    {
        LOW,
        MEDIUM,
        HIGH,
        SUSPEND,
        STOP
    };

    TPTask(Priority p);
    virtual ~TPTask() = default;

    bool operator<(const TPTask& other);
    TPTask::Priority get_priority() const;

    TPTask(const TPTask& other)             = delete;
    TPTask& operator=(const TPTask& other)  = delete;
    TPTask(TPTask&& other)                  = default;
    TPTask& operator=(TPTask&& other)       = default;

private:

    virtual void execute() = 0;
    friend class ThreadPool;

    Priority m_p;
};


}//ilrd

#endif //__TPTASK_HPP__
