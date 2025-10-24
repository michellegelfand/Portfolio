#ifndef __ERR_H__
#define __ERR_H__

#include <string>
#include <functional>//std::runtime error, std::logical error


namespace ilrd
{

class BadCreate : public std::runtime_error
{
public:
    BadCreate(std::string orig, std::string error);
    ~BadCreate() = default;
private:
    std::string m_orig;
};

//------------------------------------------------------------------------------
class BadKey : public std::logic_error
{
public:
    BadKey(std::string orig, std::string error);
    ~BadKey() = default;
private:
    std::string m_orig;
};

//------------------------------------------------------------------------------
class NBDError : public std::runtime_error
{
public:
    NBDError(std::string orig, std::string error);
    ~NBDError() = default;
private:
    std::string m_orig;
};

}//ilrd
#endif //__ERR_H__
