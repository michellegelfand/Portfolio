#ifndef __SCOPE_GUARD_H__
#define __SCOPE_GUARD_H__

#include <iostream>

namespace ilrd
{

template <typename T, void(T::*acquire)(), void(T::*release)()>

class ScopeGuard
{

public:
    ScopeGuard(T* resource);
    ~ScopeGuard();
   
    void Acquire();
    void Release();

private:
    T* m_resource;
    ScopeGuard(const ScopeGuard&); //disable copy
    ScopeGuard& operator=(const ScopeGuard&); //disable copy
};

template <typename T, void(T::*acquire)(), void(T::*release)()>
ScopeGuard<T, acquire, release>::ScopeGuard(T *resource)
     : m_resource(resource)
{
    Acquire();
}

template <typename T, void(T::*acquire)(), void(T::*release)()>
ScopeGuard<T, acquire, release>::~ScopeGuard()
{
    Release();
}

template <typename T, void(T::*acquire)(), void(T::*release)()>
void ScopeGuard<T, acquire, release>::Acquire()
{
   (m_resource->*acquire)();
}

template <typename T, void(T::*acquire)(), void(T::*release)()>
void ScopeGuard<T, acquire, release>::Release()
{
    (m_resource->*release)();
}


}//ilrd

#endif //__SCOPE_GUARD_H__
