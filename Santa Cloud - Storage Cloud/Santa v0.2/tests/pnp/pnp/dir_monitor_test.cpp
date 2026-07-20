
#include <memory>       // unique_ptr
#include <exception>    //std::error
#include <string>       //string
#include <iostream>     //std::cout

#include "../include/factory.hpp"
#include "../include/handleton.hpp"
#include "../include/logger.hpp"

#include "../include/dir_monitor.hpp"
#include "../include/dll_loader.hpp"
#include "../include/inbar_tools.hpp"

using namespace ilrd;

int main()
{   
    bool monitoring = true;
    DirMonitor dm(std::string("monitored"), &monitoring);
    DllLoader dl(dm);
    
    /* while(1)
    {
        try
        {
            auto one = Handleton<Factory<Base, std::string>>::get_instance()->create("One");
            one->execute();
        }
        catch(const exceptions& e)
        {
            // Handleton<Logger>::get_instance()->log(Logger::INFO, "no such class One",
            //     __FILE__,__LINE__);
        }
        
        try
        {
            auto two = Handleton<Factory<Base, std::string>>::get_instance()->create("Two");
            two->execute();
        }
        catch(bad_key& e)
        {
            // Handleton<Logger>::get_instance()->log(Logger::INFO, "no such class Two",
            //     __FILE__,__LINE__);
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
    }//neverending
    
    return 0; */
}

