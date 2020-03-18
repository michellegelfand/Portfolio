#include "scope_guard.h"

#include <iostream>


using namespace ilrd;

class Resource
{
public:

    void acquire();
    void release();
   
};

void Resource::acquire()
{
    std::cout << "acquired" << std::endl;
}

void Resource::release()
{
    std::cout << "released" << std::endl;
}


int main()
{
    Resource resource;
    ScopeGuard<Resource, &Resource::acquire, &Resource::release> test_obj(&resource);

    return 0;
}