#include <iostream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <exception>
#include <typeinfo>

int Foo(int) {throw std::bad_alloc();}

void Bar() { throw std::bad_cast();}

struct X
{
    ~X();
    int m_a;
};

X::~X()
{
    std::cerr << Foo(m_a) << std::endl;
}

void Fishi()
{
    X x1;
    Bar();
    
}

int main()
{
    Fishi();

    return 0;
}

