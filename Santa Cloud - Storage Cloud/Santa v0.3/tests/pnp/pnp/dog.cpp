#include <iostream>
#include <memory>

#include "dog.hpp"
#include "../include/factory.hpp"

void dog::execute(/* args */)
{
    std::cout << "dog execute" << std::endl;
}

std::unique_ptr<animal> dog::create()
{
    return std::unique_ptr<animal>(new dog());
}

dog::dog()
{

}

dog::~dog()
{
    
}


static void __attribute__((constructor)) func_dog()
{
    using namespace ilrd;
    using Factory_t = Factory<animal, std::string>;

    Handleton<Factory_t>::get_instance()->add("dog", dog::create);
}
