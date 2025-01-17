#include <exception>
#include <iostream>
#include <exception>
#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <string>

using namespace std;

struct ThrowAtDefCtor
{
    ThrowAtDefCtor()
    {
        cerr << "ThrowAtDefCtor DefCtor" << endl;
        throw bad_cast();
    }
    ThrowAtDefCtor(int){cerr << "ThrowAtDefCtor Ctor (int)" << endl;}
    ~ThrowAtDefCtor(){cerr << "ThrowAtDefCtor Dtor (int)" << endl;}
};

struct NoThrow
{
    NoThrow(){cerr << "NoThrow Ctor" << endl;}
    ~NoThrow(){cerr << "NoThrow Dtor" << endl;}
};

class X
{
public:
    X() : m_tdc(2) {cerr<< "X Ctor" << endl;}
    ~X() {cerr<< "X Dtor" << endl;}
private:
    NoThrow m_nt;
    ThrowAtDefCtor m_tdc;
};

class Y
{
public:
    Y()  {cerr<< "Y Ctor" << endl;}
    ~Y() {cerr<< "Y Dtor" << endl;}
private:
    ThrowAtDefCtor m_tdc;
    NoThrow m_nt;
};

class Z
{
public:
    Z(){cerr<< "Z Ctor" << endl;}
    ~Z(){cerr<< "Z Dtor" << endl;}
private:
    NoThrow m_nt;
    ThrowAtDefCtor m_tdc;
};


using namespace std;

class YPtrs
{
public:
    ~YPtrs()
    {
        std::cerr << "YPtrs Dtor"<<std::endl;
        delete m_nt;
        delete m_dtc;
    }
    YPtrs()
    : m_dtc(new ThrowAtDefCtor),m_nt(new NoThrow)
    {
            std::cerr << "YPtrs Ctor" <<std::endl;
    }
    
private:
    ThrowAtDefCtor *m_dtc;
    NoThrow *m_nt;
};

class ZPtrs
{
public:
    ZPtrs()
    {
        cerr << "ZPtrs Ctor" << endl; 
        m_nt = new NoThrow;
        m_dtc = new ThrowAtDefCtor;
    }
    ~ZPtrs()
    {
        cerr << "ZPtrs Dtor" <<endl;
        delete m_dtc;
        delete m_nt;
    }
private:
    NoThrow *m_nt;
    ThrowAtDefCtor *m_dtc;
};

int main()
{
    try
    {
        {
            ZPtrs var1;
            YPtrs var2;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0; 
}