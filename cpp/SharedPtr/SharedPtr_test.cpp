#include <iostream>

#include "SharedPtr.h"

using namespace ilrd;

typedef class X
{
public:
    X();
    X(char i, int j);
    ~X();
    char m_i;
    int m_j;
}X;

X::X(char i, int j)
  : m_i(i), m_j(j)
{
}

X::X()
{
}

X::~X()
{
}


typedef class Y: public X
{
public:



}Y;

void Phase1Test()
{
    SharedPtr<int>doron(new int(8));
    SharedPtr<X>michelle(new X('j', 2));
    SharedPtr<X>mush(new X('n', 5));
    SharedPtr<int>bon;

    std::cout << *(doron.GetPtr()) << std::endl;
    std::cout << (*(michelle.GetPtr())).m_i << std::endl;
    std::cout << (*(michelle.GetPtr())).m_j << std::endl;

    mush = michelle; 
    std::cout << (*mush).m_i << std::endl;
    *mush = X('p', 999);

    std::cout << (*mush).m_i << std::endl;
    std::cout << (*mush).m_j << std::endl;
    std::cout << mush->m_i << std::endl;

    std::cout << !bon << std::endl;
    std::cout << !doron << std::endl;

    std::cout << doron.GetPtr() << std::endl; 


    SharedPtr<X>inbar(michelle);

    std::cout << inbar->m_i << std::endl;
}

void consts()
{
    SharedPtr<const int>x(new int(3));
    const SharedPtr<int>y(new int(8));
    *y = 9;
    //*x = 9; wont compile 
    // y = x; wont compile 
}


void Phase2test()
{
    SharedPtr<Y>derived;
    SharedPtr<X>base;

    base = derived;
/* 
    derived = base;  */
}

void tries()
{
    SharedPtr<char*>Evgeni(new char*("mush"));
    SharedPtr<char*>Saar(new char*("slash"));

    std::cout << *Saar.GetPtr() << std::endl;
}

int main()
{
  
 Phase1Test();
  Phase2test(); 
  //consts(); 
    tries();



  return 0;

}


