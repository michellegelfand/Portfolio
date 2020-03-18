
#include <cstdlib> //exit
#include <iostream>

using namespace std;

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "this is a bad dog")
        : runtime_error(s_){}
};
class Add: public runtime_error
{
public:
    Add(const string& s_);
    ~Add();
};

Add::Add(const string& s_)
    : runtime_error(s_)
{
    cout << "Add ctor" << endl;
}
Add::~Add()
{
    cout << "Add dtor" << endl;
}

void Fifi(){throw Add("hi"); cerr << "Fifi() after throw" << endl;}
void Foo(){ Add a(); Fifi(); cerr << "Foo() after Fifi()" << endl; }
void Bar(){ Foo(); cerr << "Bar() after Foo()" << endl;}


int main()
{
    try
    {
        Bar();
    }
    catch(bad_alloc)
    {
        cerr << "out of memory! exiting."; exit(2);
    }
   /*  catch(BadDog& b)
    {
        cerr <<"Bad dog exception: " <<b.what(); exit(3);
    } */
    catch(Add &a)
    {
        cout << "new catch block" << a.what()<< endl;
    }
    catch( exception& r)
    {
        cerr << "unknown excpetion " <<r.what(); exit(4);
    }
    
    return 0;
}