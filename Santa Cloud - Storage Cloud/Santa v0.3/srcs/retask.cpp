
#include "retask.hpp"
#include "tptask.hpp"

namespace ilrd
{


RETask::RETask(Priority p)
    :   TPTask::TPTask(static_cast<TPTask::Priority>(p))
{
    //static cast: convert priority from priority of tptask to priority of retask
}

RETask::Priority RETask::get_priority() 
{
    return RETask::Priority(TPTask::get_priority());
}


}//namespace ilrd

