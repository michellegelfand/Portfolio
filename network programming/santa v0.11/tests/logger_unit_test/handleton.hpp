#ifndef __HANDLETON_HPP__
#define __HANDLETON_HPP__

/*
  Project: Handleton.hpp
  Date: 14.11.19
  Author: Michelle Gelfand


  Handleton is an object ensures to have once instance per program.
  This is an expansion upon the classic static 2004 Meyers implementation,
  also implemented using the DCLP. 
  
  REQUIREMENTS for type 'T':
  T is expected to supply a default private constructor
  T has to name Handleton a friend class
  T pointer will be deleted automatically upon the program's termination
  (DO NOT DELETE IT YOURSELF)

*/






#include <mutex> //mutex, std::lock_guard
#include <atomic> // atomic
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

    class Destroyer; //nested class

};

#define init_handleton(type)\
template <>\
std::atomic<type*> Handleton<type>::s_instance(nullptr);\
template <>\
std::mutex Handleton<type>::s_mutex{};


/* #define INIT(T) \
{\
template <typename T> \
std::atomic<T*> Handleton<T>::s_instance(nullptr);\
\
template <typename T> \
std::mutex Handleton<T>::s_mutex;\
} */

// template <typename T> 
// std::atomic<T*> Handleton<T>::s_instance(nullptr);

// template <typename T> 
// std::mutex Handleton<T>::s_mutex;


template<typename T>
T* Handleton<T>::get_instance()
{
	static Destroyer s_destroyer;

//READ
   T* temp = s_instance.load(std::memory_order_relaxed);

//ACQUIRE FENCE
 	atomic_thread_fence(std::memory_order_acquire);

   if (!temp)//check #1
   {
       /* std::lock_guard<std::mutex> lock(&s_mutex); */
       Lockguard<std::mutex>lock(&s_mutex);

       temp = s_instance.load(std::memory_order_relaxed);

       if (!temp)//check #2
       {
           temp = new T;

            //RELEASE FENCE
 			atomic_thread_fence(std::memory_order_release);


           // WRITE
           s_instance.store(temp, std::memory_order_relaxed);
       }
   }

   return temp;
}


/* Destroyer ************************************8 */
template<typename T>
class Handleton<T>::Destroyer
{
public: 
    ~Destroyer(); 
private:
};

template<typename T>
Handleton<T>::Destroyer::~Destroyer()
{
    delete s_instance.load(std::memory_order_relaxed);
    s_instance = nullptr;
}



} //ilrd


#endif //__Handleton_HPP__

