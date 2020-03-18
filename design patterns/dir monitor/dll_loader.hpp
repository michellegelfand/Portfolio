#ifndef __DLL_LOADER_HPP__
#define __DLL_LOADER_HPP__



#include <string> //std::string
#include <vector> //std::vector

#include "callback_dispatcher.hpp"
#include "dir_monitor.hpp"

namespace ilrd
{

class DllLoader
{
public:

    explicit DllLoader(DirMonitor& dir_monitor);
   
    ~DllLoader();

    void dll_load(const std::string& msg);
    void on_stop();

    DllLoader(const DllLoader&) = delete;
    DllLoader& operator=(const DllLoader&) = delete;
    DllLoader(DllLoader&&) = delete;
    DllLoader& operator=(DllLoader&&) = delete;

private:
    Callback<std::string, DllLoader> m_callback;
    std::vector<void*> m_handlers;
};

} //ilrd


#endif //__DLL_LOADER_HPP__
