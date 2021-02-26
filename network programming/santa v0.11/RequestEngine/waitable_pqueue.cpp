
#include <iostream>
#include <thread>
#include <chrono>

#include "waitable_pqueue.hpp"

using namespace ilrd;

void MultiThread();
void PushData(int num);
void Pop();
void WaitingPop();

WaitablePQueue<int> wpq;

const int MAGIC_NUM = 30;

int main()
{
    MultiThread();

    return 0;
}

void MultiThread()
{
    std::thread pushes[MAGIC_NUM];
    std::thread pops[MAGIC_NUM];

    for (int i = 0; i < MAGIC_NUM; ++i)
    {
        pushes[i] = std::thread(PushData, i);
    }
    
    for (int n = 0; n < MAGIC_NUM; ++n)
    {
        pops[n] = std::thread(Pop);
    }

    for (int n = 0; n < MAGIC_NUM; ++n)
    {
        pushes[n].join();
    }

    for (int n = 0; n < MAGIC_NUM; ++n)
    {
        pops[n].join();
    }
}

void PushData(int num)
{
    wpq.push(num);
}

void Pop()
{
    int res;
    wpq.pop(res);  
}

void WaitingPop()
{
    int res;
    wpq.pop(res, std::chrono::seconds(1));      
}
