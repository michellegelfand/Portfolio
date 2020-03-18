#include <exception> //set_terminate
#include <iostream>

void unexpected_func()
{
    std::cout << "That was unexpected!" << '\n';
}

int main() throw()
{
    /* std::unexpected(); */

    std::set_unexpected(unexpected_func);
    int a;


    /* std::unexpected(); */
    /* throw(a); */
    try
    {
        throw(a);
    }
    catch(float)
    {
        std::cout << "caught" << '\n';
    } 
    
    return 0;
}