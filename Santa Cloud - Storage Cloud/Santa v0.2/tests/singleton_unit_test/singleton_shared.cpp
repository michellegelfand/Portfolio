#include <iostream>     /* cout,cin,endl     */
#include <cstdlib>      /* EXIT_SUCCESS      */

#include "singleton.hpp"
 
using namespace ilrd;

extern "C"
{
    //extern c for explicit linking,
    //doesnt matter for implicit

    
    //func that creates singleton
    int* foo_so(void)
    {   
        int* ptr_1 = Singleton<int>::get_instance();
        return (ptr_1);
    }
}

