#include "../include/dll_loader.hpp"
#include "../include/dir_monitor.hpp"
#include "../include/factory.hpp"
#include "../include/err.hpp"

#include "animal.hpp"

#include <memory> 
#include <string>

using namespace ilrd;

using Factory_t = Factory<animal, std::string>;

auto factory =  Handleton<Factory_t>::get_instance();

int main()
{
    std::cout << "waed" << std::endl;
    
    DirMonitor mon("/home/student/Desktop/michelle-gelfand/projects/santa v0.2/tests/pnp/pnp/monitored");
    
    DllLoader dll(mon);

    
    std::cout << "waed2" << std::endl;
    static const size_t rounds = 20;
    size_t i = 0;
    while(i < rounds)
    {

        try
        {

            std::cout << "waed3" << std::endl;
            auto anim  = factory->create("animal");
            anim->execute();
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "waed4" << std::endl;
            
        }

        try
        {
            auto puppy = factory->create("dog");
            puppy->execute();
    
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "waed4" << std::endl;
            
        } 

        std::this_thread::sleep_for(std::chrono::seconds(2));
        ++i;
    }

    return 0;
}
