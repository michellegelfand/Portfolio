#ifndef _LOCK_GUARD_H_
#define _LOCK_GUARD_H_

#include <pthread.h>
#include "olga_tools.hpp"

namespace ilrd
{

template <typename M>
class LockGuard
{
public:
	LockGuard(M* lock);
	~LockGuard();

private:
	M* m_lock;
    LockGuard(const LockGuard&);            //uncopyable
    LockGuard& operator=(const LockGuard&); //uncopyable
};

/******************************************************************************/
template <typename M>
inline LockGuard<M>::LockGuard(M* lock) : m_lock(lock)
{
	(m_lock->lock)();
    DEBUG_ONLY(std::cout << "Ctor" << std::endl;)
}

/******************************************************************************/
// pthread_mutex_t specializetion
template < >
inline LockGuard<pthread_mutex_t>::LockGuard(pthread_mutex_t* lock) : m_lock(lock)
{
	pthread_mutex_lock(m_lock);
    DEBUG_ONLY(std::cout << "pthread_mutex Ctor" << std::endl;)
}

/******************************************************************************/
template <typename M>
inline LockGuard<M>::~LockGuard()
{
    DEBUG_ONLY(std::cout << "Dtor" << std::endl;)
	(m_lock->unlock)();
}

/******************************************************************************/
// pthread_mutex_t specializetion
template < >
inline LockGuard<pthread_mutex_t>::~LockGuard()
{
    DEBUG_ONLY(std::cout << "pthread_mutex Dtor" << std::endl;)
	pthread_mutex_unlock(m_lock);
}

/******************************************************************************/
// LockGuard template instantiation examples
//template class LockGuard<std::mutex>;
//template class LockGuard<std::recursive_mutex>;

}   //namespace ilrd

#endif //_LOCK_GUARD_H_
