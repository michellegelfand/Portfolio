#include <iostream>
#include <typeinfo>
#include <unistd.h>

#include "request_engine.hpp"
#include "retask.hpp"
#include "gateway.hpp"
#include "handleton.hpp"
#include "factory.hpp"
#include "santa_tools.hpp"


#include <sys/types.h> // mkfifo
#include <sys/stat.h>
#include <fcntl.h> // O
#include <string>

using namespace ilrd;

using FactoryRE = Factory<RETask, std::string, std::string>;

init_handleton(FactoryRE)

class MyTask : public RETask 
{
public:
    MyTask() = default;
    ~MyTask() = default;
    MyTask(const std::string& str)
      : RETask(Priority::LOW)
      , m_string(str)
    {}
        
    static std::unique_ptr<MyTask> create(const std::string& str)
    {
        return std::unique_ptr<MyTask>(new MyTask(str));
    }

private:    
    void execute()
    {
        std::cerr << GRN "Execute: " NRM << m_string << std::endl;
    }
    
    std::string m_string;
};

class MyGate : public GateWay<std::string, std::string>
{
public:
    MyGate(int fd)
      :GateWay(fd)
    {
        
    }

    std::pair<std::string, std::string>read() 
    override
    {
        char buff[128] = {0};
        std::string str;
        
        std::cerr << "in gw" << std::endl;
        
        ::read(get_fd(), buff, 128);
        str = buff;
        str = str.substr(0, str.size()-1);
        
        //std::cout << RED "str: " NRM << str << std::endl;

        return std::make_pair(str, str);
    }
};

int main()
{
    RequestEngine<std::string, std::string> rq("/home/student/git/olga-kondrashova/projects/santacloud_0.3/test/tmp");
    
    rq.add_gateway(new MyGate(0));
    rq.add_task("task", MyTask::create);
    //rq.set_threads_num(1);
    
    rq.run();
    
    
    return 0;
}
