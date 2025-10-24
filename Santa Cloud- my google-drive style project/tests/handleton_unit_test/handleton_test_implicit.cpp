/*
  Project: Singleton Test for implicit load of functions
  Date: 14.11.19
  Author: Alex Raihel

  
  REQUIREMENTS for type 'T':
  T is expected to supply a default private constructor
  T has to name Singleton a friend class
  T pointer will be deleted automatically upon the program's termination
  (DO NOT DELETE IT YOURSELF)

*/


#include <iostream>             //cout, cin, endl  
#include <cstdlib>              //EXIT_SUCCESS  
#include <unistd.h>             //sleep
#include <thread>               //thread
#include <condition_variable>   //condition variable, wait, notify all             

#include "handleton.hpp"
#include "santa_tools.hpp"

// Forward Declarations   
template<typename T>
void Test(const char *test, T value, T expected_val); 

void TestThread();
void thread_func();
void ImplicitLinking();

extern "C"
{
    int* foo_so(void);
}


// Global variables       
int count = 0;
int total = 0; 
static const size_t NUM_OF_THREADS = 20;


using namespace ilrd;


int main()
{
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
    int *ptr_1 = Handleton<int>::get_instance();
    Test("Test IMPLICIT dynamic Handleton",ptr_2, ptr_1);
}


// ****************************************************************************
template<typename T>
void Test(const char *test, T value, T expected_val)
{   
    ++total;
    std::cout<< test << std::endl;
    
    if(value == expected_val)
    {
        ++count;
        std::cout << GRN "PASSED" NRM<<std::endl;
    }
    else
    {
        std::cout << RED "FAILED" NRM<<std::endl;
    }
}



