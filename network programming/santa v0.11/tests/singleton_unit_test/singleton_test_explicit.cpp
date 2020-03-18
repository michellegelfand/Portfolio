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
*  Test for explicit load of functions

do the exact same only binding is explicit
*/

#include <iostream>             //cout, cin, endl
#include <dlfcn.h>              //dlopen    
#include <cstdlib>              //EXIT_SUCCESS  
#include <unistd.h>             //sleep
#include <thread>               //thread
#include <condition_variable>   //condition variable, wait, notify all             

#include "singleton.hpp"


template<typename T>
void Test(const char *test, T value, T expected_val); 

typedef int *(*foo_so_t)();

void TestThread();
void thread_func();

     
int count = 0;
int total = 0; 
static const size_t NUM_OF_THREADS = 20;
foo_so_t foo_so_dy = nullptr;
int *ptr_1 = nullptr; 

extern "C"
{
    int* foo_so(void);
}

int ExplicitLinking();

using namespace ilrd;

int main()
{
    std::cout << (ExplicitLinking()) << std::endl;
    return 0;
}

int ExplicitLinking()
{
    using namespace std;

    // open the library
    cout << "Opening libsingleton_shared.so...\n";
    void* handle = dlopen("libsingleton_shared.so", RTLD_LAZY);
    
    if (!handle) 
    {
        cerr << "Cannot open library: " << dlerror() << endl;
        return 1;
    }
    
    // load the symbol
    cout << "Loading symbol foo_so..." << endl;

    // reset errors
    dlerror();
    foo_so_dy = (foo_so_t)dlsym(handle, "foo_so");

    const char *dlsym_error = dlerror();

    if(dlsym_error) 
    {
        cerr << "Cannot load symbol 'foo_so': " << dlsym_error << endl;
        dlclose(handle);
        return 1;
    }
    
    // use it to do the calculation
    cout << "Calling foo_so...\n";
    
    ptr_1 = Singleton<int>::get_instance(); 
    TestThread();
    
    // close the library
    cout << "Closing library...\n";
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

    int *ptr_2 = foo_so_dy();
    std::cout << "ptr_2: " << *ptr_2 << std::endl;
    Test("Test dynamic singleton",ptr_2, ptr_1);
    read_write.lock();
    std::cout << "ptrs in thread_func: " << ptr_2 << "  " << ptr_1 << std::endl;
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
        std::cout << "PASSED" <<std::endl;
    }
    else
    {
        std::cout <<"FAILED" <<std::endl;
    }
}

