// Compile with c++11 flags and -pthread 

#include <pthread.h>
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono> 

#include "lock_guard.h"

using namespace ilrd;

std::size_t global_counter = 0;
std::mutex global_counter_mutex; 
std::recursive_mutex global_recursive_mutex;

void TestMutex();
void SafeIncrement();
void RecursiveIncrement();
void TestPthreadMutex();
void TestRecursiveMutex();
 
int main()
{
    TestMutex();
    TestRecursiveMutex();
    TestPthreadMutex();

    return 0;
}

void TestMutex()
{
    std::thread t1(SafeIncrement);
    std::thread t2(SafeIncrement);
    std::thread t3(SafeIncrement);
 
    t1.join();
    t2.join();
    t3.join();
}

void SafeIncrement()
{
    LockGuard<std::mutex> lg(&global_counter_mutex);
    ++global_counter;
    std::cout << "SafeIncrement " << global_counter <<  std::endl;
}

void TestRecursiveMutex()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    if(5 > global_counter)
    {
        std::thread t1(RecursiveIncrement);
        TestRecursiveMutex();
        t1.join();
    }
}

void RecursiveIncrement()
{  
    LockGuard<std::recursive_mutex> lg(&global_recursive_mutex);
    ++global_counter;
    std::cout << "RecursiveIncrement " << global_counter <<  std::endl;   
}


void TestPthreadMutex()
{
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    {
        LockGuard<pthread_mutex_t> guard(&mutex);
        std::cout << "end of scope" << std::endl;
    }

    std::cout << "end of main" << std::endl;
}

