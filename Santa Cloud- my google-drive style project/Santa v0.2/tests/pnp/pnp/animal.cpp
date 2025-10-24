#include <iostream>
#include <memory>

#include "animal.hpp"
#include "../include/factory.hpp"



void animal::execute(/* args */)
{
    std::cout << "animal execute" << std::endl;
}

std::unique_ptr<animal> animal::create()
{
    return std::unique_ptr<animal>(new animal());
}

static void __attribute__((constructor)) func_animal()
{
    using namespace ilrd;
    using Factory_t = Factory<animal, std::string>;

    Handleton<Factory_t>::get_instance()->add("animal", animal::create);
}
