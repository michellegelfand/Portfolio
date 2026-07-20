/*
  Project: Handleton Test for explicit load of functions
  Date: 14.11.19
  Author: Michelle Gelfand

  REQUIREMENTS for type 'T':
  T is expected to supply a default private constructor
  T has to name Handleton a friend class
  T pointer will be deleted automatically upon the program's termination
  (DO NOT DELETE IT YOURSELF)

*/

#include <iostream>             //cout, cin, endl
#include <dlfcn.h>              //dlopen    
#include <cstdlib>              //EXIT_SUCCESS  
#include <unistd.h>             //sleep
#include <thread>               //thread
#include <condition_variable>   //condition variable              

#include "handleton.hpp"
#include "santa_tools.hpp"
#include "logger.hpp"  


template<typename T>
void Test(const char *test, T value, T expected_val); 

typedef Logger *(*foo_so_t)();

void TestThread();
void thread_func();
     
int count = 0;
int total = 0; 
static const size_t NUM_OF_THREADS = 20;
foo_so_t foo_so_dy = nullptr;
Logger *ptr_1 = nullptr; 

//******************************************************************************
extern "C"
{
    int* foo_so(void);
}

int ExplicitLinking();

//******************************************************************************

using namespace ilrd;

//******************************************************************************
int main()
{
    std::cout << (ExplicitLinking()) << std::endl;
    return 0;
}

//******************************************************************************
int ExplicitLinking()
{
    // open the library
    std::cout << "Opening libhandleton_shared.so..." << std::endl;
    void* handle = dlopen("libhandleton_shared.so", RTLD_LAZY);
    
    if (!handle) 
    {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return 1;
    }
    
    // load the symbol
    std::cout << "Loading symbol foo_so..." << std::endl;

    // reset errors
    dlerror();
    foo_so_dy = (foo_so_t)dlsym(handle, "foo_so");

    const char *dlsym_error = dlerror();

    if(dlsym_error) 
    {
        std::cerr << "Cannot load symbol 'foo_so': " << dlsym_error << std::endl;
        dlclose(handle);
        return 1;
    }
    
    std::cout << "Calling foo_so..." << std::endl;
    
    ptr_1 = Handleton<Logger>::get_instance(); 
    TestThread();
    

    std::cout << "Closing library..." << std::endl;
    dlclose(handle);

    return (EXIT_SUCCESS);
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

    Logger *ptr_2 = foo_so_dy();
    std::cout << "ptr_2: " << ptr_2 << std::endl;
    Test("Test dynamic handleton",ptr_2, ptr_1);
    read_write.lock();
    std::cout << "ptrs in thread_func: " << ptr_2 << "  " << ptr_1 << std::endl;
    std::flush(std::cout);
    read_write.unlock();
}


// ****************************************************************************
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
        std::cout << "FAILED" <<std::endl;
    }
}

