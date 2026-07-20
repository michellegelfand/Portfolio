#ifndef __Handleton_HPP__
#define __Handleton_HPP__

/*
  Project: Handleton.hpp
  Date: 14.11.19
  Author: Michelle Gelfand


  Handleton is an object which occurs once per program, across all threads.
  This is an expansion upon the classic static 2004 Meyers implementation,
  also implemented using the dclp 
  
  REQUIREMENTS for T:
  T is expected to supply a default private constructor
  T has to name Handleton a friend class
  T pointer will be deleted automatically upon the program's termination
  (DO NOT DELETE IT YOURSELF)

*/

#include <mutex>    // std::mutex
#include <atomic>   // std::atomic
#include <memory>   // std::unique

#include "lock_guard.hpp"

namespace ilrd
{

template<typename T>
class Handleton
{
public:
    static T* get_instance();

    Handleton() = delete;
    ~Handleton() = delete;

    Handleton(Handleton& other) = delete; 
    Handleton& operator=(Handleton& other) = delete; 

    Handleton(Handleton&& other) = delete; 
    Handleton&& operator=(Handleton&& other) = delete; 

private:
    static std::atomic<T*> s_instance;
    static std::mutex s_mutex;
};

//macro Init to create instances..
#define INITHANDLETON(T)\
    template <>\
    std::atomic<T*> Handleton<T>::s_instance(nullptr);\
    template <> \
    std::mutex Handleton<T>::s_mutex{};\


//------------------------------------------------------------------------------
template<typename T>
T* Handleton<T>::get_instance()
{
    /* load = read , store = write */

    static std::unique_ptr<T> destroyer;

    T* temp = s_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);

    if (temp == nullptr) 
    {
        LockGuard<std::mutex> lock(&s_mutex);

        /* read current status of s_instance */
        temp = s_instance.load(std::memory_order_relaxed);
    
        if (temp == nullptr) 
        {
            temp = new T;
            destroyer.reset(temp);
            std::atomic_thread_fence(std::memory_order_release);
            s_instance.store(temp, std::memory_order_relaxed);
        }
    }

    return temp;
}

}//ilrd


#endif //__Handleton_HPP__
