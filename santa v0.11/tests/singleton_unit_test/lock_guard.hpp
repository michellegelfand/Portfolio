#ifndef __LOCK_GUARD_H__
#define __LOCK_GUARD_H__


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
Lockguard<M>::Lockguard(M *mutex)
    :m_mutex(mutex)
{
    std::cout << "lock" << std::endl;
    mutex->lock();
}

template<typename M>
Lockguard<M>::~Lockguard()
{
    std::cout << "unlock" << std::endl;
    m_mutex->unlock();
}

template<>
Lockguard<pthread_mutex_t>::Lockguard(pthread_mutex_t *pmt)
    :m_mutex(pmt)
{
    std::cout << "pthread lock yaa" << std::endl;
    pthread_mutex_lock(m_mutex);
}

template<>
Lockguard<pthread_mutex_t>::~Lockguard()
{
    std::cout << "naowww unlock it pthread" << std::endl; 
    pthread_mutex_unlock(m_mutex);
}

}
#endif //lock_guard.h