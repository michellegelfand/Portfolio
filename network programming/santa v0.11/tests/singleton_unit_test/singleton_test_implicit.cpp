/*
*  Project: Singleton.hpp
*  Date: 14.11.19
*  Author: Michelle Gelfand
*
*  Test File
*  
*  REQUIREMENTS for T:
*  T is expected to supply a default private constructor
*  T has to name Singleton a friend class
*
*  T pointer will be deleted automatically upon the program's termination
*  (DO NOT DELETE IT YOURSELF)
*
*
*/

#include <iostream>             //cout, cin, endl   
#include <unistd.h>             //sleep
#include <thread>               //thread
#include <condition_variable>   //condition variable all             

#include "singleton.hpp"
 
template<typename T>
void Test(const char *test, T value, T expected_val); 

void TestThread();
void thread_func();
void ImplicitLinking();

extern "C"
{
    int* foo_so(void);
}
      
int count = 0;
int total = 0; 
static const size_t NUM_OF_THREADS = 20;
int *ptr_1 = nullptr;


using namespace ilrd;

//regular thread test, only implicitly linking and calling func in singleton_shared

int main()
{
    ptr_1 = Singleton<int>::get_instance();
    TestThread();
    return 0;
}


void TestThread()
{
    std::thread arr[NUM_OF_THREADS];

    for(size_t i = 0; i < NUM_OF_THREADS; ++i)   
    {
        arr[i] = std::thread(thread_func);
    }

    for(size_t i = 0; i < NUM_OF_THREADS; ++i)   
    {
        arr[i].join();
    }
}

static std::mutex m;
static std::mutex read_write;

void thread_func()
{
    int *ptr_2 = foo_so();
    
    Test("Test IMPLICIT dynamic singleton",ptr_2, ptr_1);
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
        std::cout << "PASSED" <<std::endl;
    }
    else
    {
        std::cout << "FAILED"<<std::endl;
    }
}



