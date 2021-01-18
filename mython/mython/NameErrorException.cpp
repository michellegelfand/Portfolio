#include "NameErrorException.h"

NameErrorException::NameErrorException(std::string name)
{
    _name = "NameError : name \'" + name + "\' is not defined";
    _c_str = (char*)_name.c_str();
}

const char* NameErrorException::what() const throw()
{
    return _c_str;
}
