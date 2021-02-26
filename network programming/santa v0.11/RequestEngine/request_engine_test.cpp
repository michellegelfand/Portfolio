#include <iostream>

#include "request_engine.hpp"
#include "gateway.hpp"
#include "retask.hpp"

using namespace ilrd;
                                    //key(fd), &arguments for create
class STDINGateWay : public GateWay<int, int> 
{
public:
    STDINGateWay(int fd = 0) : GateWay(fd) {}
    ~STDINGateWay() = default;
    
    std::pair<int, int> read()
    {
        int x = 5;
        return std::make_pair(GateWay::get_fd(), x);
    }
};

using re_priority = RETask::Priority;

class TestTask1 : public RETask
{
public:
    TestTask1(re_priority priority);

    void execute();

    static std::unique_ptr<RETask> create(int num);
    
private:

};

TestTask1::TestTask1(re_priority priority)
    : RETask(priority)
{}

void TestTask1::execute()
{
    std::cout << " :-( :-) ;-)) ()())" << std::endl;
}

std::unique_ptr<RETask> TestTask1::create(int num)
{
    (void)num;
    return std::unique_ptr<RETask>(new TestTask1(re_priority::HIGH));
} 

int main()
{
    RequestEngine<int, int> re(
        "/home/student/monitorme",//folder to monitor
        3);//number of threads
    
    STDINGateWay gw(0); //listen to 0: STDIN.

    re.add_gateway(dynamic_cast<GateWay<int, int>*>(&gw));

    re.add_task(0, TestTask1::create); 

    re.run();

    return 0;
}







