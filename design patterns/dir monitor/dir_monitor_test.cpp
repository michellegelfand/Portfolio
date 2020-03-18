#include <iostream>//cout
#include <unistd.h>//sleep


#include "dir_monitor.hpp"
#include "dll_loader.hpp"

using namespace ilrd;

int main()
{
 
    //bool is_monitoring = true;
    DirMonitor monitor("monitor_me");
std::cout << "+++++++++++++++++++++++++++++++++++++" <<std::endl;
    sleep(30);
std::cout << "+++++++++++++++++++++++++++++++++++++" <<std::endl;
    return 0;
}



