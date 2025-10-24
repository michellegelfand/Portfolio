#ifndef __LOCK_GUARD__
#define __LOCK_GUARD__
/* TODO add debug only for prints */
#include <iostream>
extern "C"
{
	#include <pthread.h>
}

namespace ilrd
{
    template<typename T>
    class LockGuard
    {
    public:
        explicit LockGuard(T* lock);
        ~LockGuard();
        void Lock();
        void Unlock();
        T* GetReasource();

    private:
        T* m_lock;
        LockGuard(const LockGuard&); //no copy
        LockGuard& operator=(const LockGuard&); //no op=
    };

    template <typename T>
    inline LockGuard<T>::LockGuard(T *lock) 
        : m_lock(lock)
    {
        Lock();
    }
    
    template <typename T>
    inline LockGuard<T>::~LockGuard()
    {
        Unlock();
    }

    template <typename T>
    inline void LockGuard<T>::Lock()
    {
        (m_lock->lock)();
        //std::cout << m_lock << " mutex locked"<< std::endl;
    }

    template <>
    inline void LockGuard<pthread_mutex_t>::Lock()
    {
        pthread_mutex_lock(m_lock);
        std::cout << m_lock << " pthread mutex locked"<< std::endl;
    }

    template <typename T>    
    inline void LockGuard<T>::Unlock()
    {
        (m_lock->unlock)();
        //std::cout << m_lock << " mutex unlocked"<< std::endl;
    }

    template <>    
    inline void LockGuard<pthread_mutex_t>::Unlock()
    {
        pthread_mutex_unlock(m_lock);
        std::cout << m_lock << " pthread mutex unlocked"<< std::endl;
    }

    template<typename T>
    inline T* LockGuard<T>::GetReasource()
    {
        return m_lock;
    }

}//ilrd
#endif// __LOCK_GUARD__

