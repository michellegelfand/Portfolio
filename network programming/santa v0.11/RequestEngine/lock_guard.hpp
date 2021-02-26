#ifndef __LOCK_GUARD_HPP__
#define __LOCK_GUARD_HPP__


#include <iostream>//cout
#include <pthread.h>//pthread_mutex_t
#include <mutex>//mutex
#include <thread>//thread

namespace ilrd
{

template<typename M>
class Lockguard
{
public:
    explicit Lockguard(M *mutex);
    ~Lockguard();

private:
    M *m_mutex;
    Lockguard(Lockguard& other); //uncopyable
    Lockguard& operator =(const Lockguard& other); //uncopyable
};

template<typename M>
inline Lockguard<M>::Lockguard(M *mutex)
    :m_mutex(mutex)
{

    mutex->lock();
}

template<typename M>
inline Lockguard<M>::~Lockguard()
{

    m_mutex->unlock();
}

template<>
inline Lockguard<pthread_mutex_t>::Lockguard(pthread_mutex_t *pmt)
    :m_mutex(pmt)
{

    pthread_mutex_lock(m_mutex);
}

template<>
inline Lockguard<pthread_mutex_t>::~Lockguard()
{
  
    pthread_mutex_unlock(m_mutex);
}

}
#endif //lock_guard.h