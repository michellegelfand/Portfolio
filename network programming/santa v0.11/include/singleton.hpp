#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

/*
  Project: Singleton.hpp
  Date: 14.11.19
  Author: Michelle Gelfand


  Singleton is an object ensures to have once instance per program.
  This is an expansion upon the classic static 2004 Meyers implementation,
  also implemented using the DCLP. 
  
  REQUIREMENTS for type 'T':
  T is expected to supply a default private constructor
  T has to name Singleton a friend class
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
class Singleton
{
public:
    static T* get_instance();

    Singleton() = delete;
    ~Singleton() = delete;

    Singleton(Singleton& other) = delete; 
    Singleton& operator=(Singleton& other) = delete; 

    Singleton(Singleton&& other) = delete; 
    Singleton&& operator=(Singleton&& other) = delete; 

private:
    static std::atomic<T*> s_instance;
    static std::mutex s_mutex;

    class Destroyer; //nested class

};

template <typename T> 
std::atomic<T*> Singleton<T>::s_instance(nullptr);

template <typename T> 
std::mutex Singleton<T>::s_mutex;


template<typename T>
T* Singleton<T>::get_instance()
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


/* Destroyer ************************************ */
template<typename T>
class Singleton<T>::Destroyer
{
public: 
    ~Destroyer(); 
private:
};

template<typename T>
Singleton<T>::Destroyer::~Destroyer()
{
    delete s_instance.load(std::memory_order_relaxed);
    s_instance = nullptr;
}



} //ilrd


#endif //__SINGLETON_HPP__

