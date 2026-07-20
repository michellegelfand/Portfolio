
#include "tptask.hpp"

namespace ilrd
{

TPTask::TPTask(Priority p)
	: m_p(p) { }



bool TPTask::operator<(const TPTask& other)
{
	return (m_p <= other.m_p);
}

TPTask::Priority TPTask::get_priority() const
{
    return m_p;
}


}//ilrd

