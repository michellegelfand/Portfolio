#include <dlfcn.h>
#include <iostream>

#include "../include/dll_loader.hpp"

namespace ilrd
{

DllLoader::DllLoader(DirMonitor& monitor)
: m_callback(monitor.get_dispatcher(), *this, 
                &DllLoader::dll_load,
                &DllLoader::on_stop)
{
    std::cout << "DllLoader Ctor" << std::endl;
}


void DllLoader::dll_load(const std::string& msg)
{
    auto handle = dlopen(msg.c_str(), RTLD_LAZY | RTLD_GLOBAL | RTLD_NODELETE);


    std::cout << (msg) << std::endl;

    if (!handle)
    {
        throw std::runtime_error("Cannot open library");
    }
 
    if(dlclose(handle))
    {
        throw std::runtime_error("Cannot close library");
    }
}


void DllLoader::on_stop()
{
    std::cout << "DllLoader Stop" << std::endl;
}


}// ilrd
