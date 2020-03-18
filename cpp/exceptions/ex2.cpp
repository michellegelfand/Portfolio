
#include <cstdlib> //exit
#include <iostream>
#include <exception> //set_terminate
#include <stdexcept>

struct Loo
{
    int a;
    char b;
    char c;
};

int Foo() throw(int)
{
    int a;
    Loo b;
    throw(a);

    return 0;
}

void Choo()
{
    std:: cout << "Choo" << std::endl;
}

void Goo()
{
    std:: cout << "Goo" << std::endl;
}

int main()
{
    int a;
   /*  throw(a); */
    std::set_terminate(Goo); 
    std::set_unexpected(Choo);
    try
    {
        Foo();
    }
    catch(int a)
    {
        std::cerr << "catch" << '\n';
        /* std::terminate(); */
        std::unexpected();
    }
    
    /* std::terminate(); */

    return 0;
}