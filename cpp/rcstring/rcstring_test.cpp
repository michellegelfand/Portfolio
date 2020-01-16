
#include <cstring>
#include <iostream>

#include "test_tools.h"
#include "rcstring.h"

using namespace std;
using namespace ilrd;

void copyonwrite()
{
    RCString string1(" mushishi ");
    RCString string2(string1);
    RCString string3("sjiojf"); 
    cin >> string2; 
    string2[5] = 'k';

    string2 = string3;
    cout <<BLUE""<< "string1: " << string1 << "string 2 "<< string2 <<WHITE"" << endl;
}

int main()
{
    const char *text = "mushles";
    RCString string(text);

    cout << string.ToCStr() << endl;
    RCString string2(string);
    cout << string2.Length() <<endl;
    cout << string2[3] << endl;
    RCString string3;
    string3 = string2;
    string3[0] = 'n';
    cout << string3.ToCStr() << endl;
    std::cin >> string3;
    cout << string3.ToCStr() << endl;

    cout <<YELLOW"this line with << operator"WHITE<< string3 <<endl;

    RCString string4(string3);

    cout << (string == string4) << endl;
    cout << (string3 == string4) << endl;

    cout << (string != string4) << endl;
    cout << (string3 != string4) << endl;

    RCString string5("aaa1");
    RCString string6("aaa2");

    cout <<"expected 0 " << (string5 > string6) << endl;
    cout <<"expected 1 " << (string5 < string6) << endl; 

    copyonwrite();

    return 0;
}