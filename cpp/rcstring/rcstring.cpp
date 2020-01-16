 #include <cstring>
#include <iostream>

#include "test_tools.h"
#include "rcstring.h"

namespace ilrd
{
RCString::RCString(const char *str)
{
    size_t length = strlen(str) +1;
    size_t sizeof_size_t = sizeof(size_t);

    m_buffer = new char[length + sizeof_size_t];
    size_t size = 1;
    memcpy(m_buffer, &size, sizeof_size_t);
    memcpy(m_buffer + sizeof_size_t, str, length);

    DEBUG_ONLY(std::cout << GREEN"ctor: "WHITE << (size_t)*m_buffer;);
    DEBUG_ONLY(std::cout << " "<< (char*)(m_buffer + sizeof_size_t) << std::endl;);
}

RCString::RCString(const RCString& other)
    :m_buffer(other.m_buffer)
{
    *m_buffer+=1;
    DEBUG_ONLY(std::cout << GREEN"cctor: count "WHITE << (size_t)*m_buffer << std::endl;);
}

RCString::~RCString()
{
   DeleteAssist();    
}

const char* RCString::ToCStr() const
{
    return (m_buffer+(sizeof(size_t)));
}

bool RCString::IsShared() const
{
    DEBUG_ONLY(std::cout << "IsShared returned " << (*m_buffer > 1)<<
    std::endl;);
    return (*m_buffer > 1);
}

size_t RCString::Length() const
{
    return strlen((m_buffer + sizeof(size_t)) );
}

char& RCString::operator[](std::size_t index)
{
    if(IsShared())
    {
        RCString temp(ToCStr());
        *this = temp;
    }

    return *(m_buffer + sizeof(size_t) + index);
}

const char& RCString::operator[](std::size_t index) const
{
    return *(m_buffer + sizeof(size_t) + index);
}

void RCString::DeleteAssist() 
{
    if( !IsShared() )
    {
        delete[] m_buffer;
        DEBUG_ONLY(std::cout << RED"deleter: m_buffer deleted"WHITE << std::endl);
    }
    else
    {
        *m_buffer -= 1;
        DEBUG_ONLY(std::cout << RED"deleter: new count: " WHITE<< (size_t)*m_buffer << std::endl);
    }
}

RCString& RCString::operator=(const RCString& other)
{
    DeleteAssist();
    m_buffer = other.m_buffer;
    *m_buffer += 1;

    return *this;
}

std::istream& operator>>(std::istream& i_stream, RCString& str)
{
    std::string buffer;
    i_stream >> buffer;
    RCString rcbuffer(buffer.c_str());
    str = rcbuffer;

    return i_stream;
}

std::ostream& operator<<(std::ostream& o_stream, const RCString& str)
{
    o_stream << str.ToCStr();

    return o_stream;
}

bool operator==(const RCString& lhs, const RCString& rhs)
{
    return !(strcmp(lhs.ToCStr(), rhs.ToCStr()));
}

bool operator!=(const RCString& lhs, const RCString& rhs)
{
    return !(lhs == rhs);
}

bool operator>(const RCString& lhs, const RCString& rhs)
{
    return ( 0 < strcmp(lhs.ToCStr(), rhs.ToCStr()));
}

bool operator<(const RCString& lhs, const RCString& rhs)
{
    return ( 0 > strcmp(lhs.ToCStr(), rhs.ToCStr()));
}



}//ilrd