#include <iostream>     /* cout,cin,endl     */
#include <cstdlib>      /* EXIT_SUCCESS      */

#include "handleton.hpp"
#include "logger.hpp"

using namespace ilrd;

extern "C"
{
    Logger* foo_so(void)
    {   
        Logger* ptr_1 = Handleton<Logger>::get_instance();
        return (ptr_1);
    }
}

