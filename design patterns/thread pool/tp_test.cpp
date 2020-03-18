#include <iostream>//cout


#include "tptask.hpp"
#include "thread_pool.hpp"

using namespace std;
using namespace ilrd;

class task1: public TPTask
{
public:
    task1(Priority p)
        :TPTask(p)
    {

    }
    ~task1(){}

    

    void execute() override
    {
        std::cout << "\n lets get it started in here" <<std::endl;
    }

};


class task2: public TPTask
{
public:
    task2(Priority p)
        :TPTask(p)
    {

    }
    ~task2(){}

    

    void execute() override
    {
        std::cout << "\n- HAA!!" <<std::endl;
    }

};


class task3: public TPTask
{
public:
    task3(Priority p)
        :TPTask(p)
    {

    }
    ~task3(){}

    

    void execute() override
    {
        std::cout << "\n ...lets get it started" <<std::endl;
    }

};


int main()
{
    ThreadPool threadpool(1);

    unique_ptr<task1> last(new task1(TPTask::Priority::LOW));
    unique_ptr<task2> middle(new task2(TPTask::Priority::MEDIUM));
    unique_ptr<task3> first(new task3(TPTask::Priority::HIGH));

    threadpool.add_task(std::move(last));
    threadpool.add_task(std::move(middle));
    threadpool.add_task(std::move(first));  

    std::chrono::seconds timeout(1);

    threadpool.stop(timeout);

    return 0;
}