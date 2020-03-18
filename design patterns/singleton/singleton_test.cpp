/*
*  Project: Singleton.hpp
*  Date: 14.11.19
*  Author:Michelle Gelfand
*
*  Test File
*  
*  REQUIREMENTS for T:
*  T is expected to supply a default private constructor
*  T has to name Singleton a friend class
*
*  T pointer will be deleted automatically upon the program's termination
*  (DO NOT DELETE IT YOURSELF)
*/

#include <iostream>             //cout
#include <memory>               //unique lock
#include <unistd.h>             //sleep
#include <thread>               //thread
#include <condition_variable>   //condition variable   
           

#include "singleton.hpp"


// Forward Declarations     
template<typename T>
void Test(const char *test, T value, T expected_val); 

// Global variables       
int count = 0;
int total = 0; 
static const size_t NUM_OF_THREADS = 20;

int* foo_so2(void);

void TestCreate();
void TestThread();
void thread_func();
// int ExplicitLinking();
void ImplicitLinking();

using namespace ilrd;

class Dog
{
public:
    ~Dog()
    {
        std::cout << "Dtor dog m_i = " << m_i << std::endl;
    }
private:
    int m_i;
    Dog(int i = 10) : m_i(i) 
    {
        std::cout << "Ctor dog m_i = " << m_i << std::endl;
    }
    friend class Singleton<Dog>;
};

int main()
{
    TestCreate();
    TestThread();

    return 0;
}

void TestCreate()
{
    Dog *d = Singleton<Dog>::get_instance();
    Dog *f = Singleton<Dog>::get_instance();
    Dog *g = Singleton<Dog>::get_instance();

    std::cout<< "d add =" << d << std::endl;
    std::cout<< "f add =" << f << std::endl;
    std::cout<< "g add =" << g << std::endl;
}

void TestThread()
{
    for(size_t i = 0; i < NUM_OF_THREADS; ++i)   
    {
        if(i == NUM_OF_THREADS - 1)
        {
            sleep(1);
            std::thread t(thread_func);
            t.join();
        }
        else
        {
            std::thread t(thread_func);
            t.detach();
        }        
    }
}

static std::mutex m;
static std::mutex read_write;

void thread_func()
{
    static size_t counter = 0;
    static std::condition_variable cv;

    read_write.lock();
    std::cout << "counter: " << counter << std::endl;
    ++counter;
    read_write.unlock();

    std::unique_lock<std::mutex> mutex(m); 

    if(counter == NUM_OF_THREADS)
    {
        cv.notify_all();
    }
    else
    {
        cv.wait(mutex);
    }

    Dog *d = Singleton<Dog>::get_instance();
    read_write.lock();
    std::cout << "d in thread_func" << d << std::endl;
    std::flush(std::cout);
    read_write.unlock();
}

/*****************************************************************************/
template<typename T>
void Test(const char *test, T value, T expected_val)
{   
    ++total;
    std::cout<<test;
    
    if(value == expected_val)
    {
        ++count;
        std::cout <<"PASSED" <<std::endl;
    }
    else
    {
        std::cout <<"FAILED" <<std::endl;
    }
}

