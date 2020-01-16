#ifndef __RCSTRING_H__
#define __RCSTRING_H__

#include <iosfwd> // std::cin, std::cout
#include <cstring> // string

namespace ilrd
{
class RCString
{
public:
    explicit RCString(const char *str = "");
    RCString(const RCString& other);
    ~RCString();

    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;
    RCString& operator=(const RCString& other);
    size_t Length() const;
    const char* ToCStr() const;
    bool IsShared() const;

private:
    char* m_buffer; 
    friend std::istream& operator>>(std::istream& i_stream, RCString& str);
    void DeleteAssist();
};




std::ostream& operator<<(std::ostream& o_stream, const RCString& str);
std::istream& operator>>(std::istream& i_stream, RCString& str);
bool operator==(const RCString& lhs, const RCString& rhs);
bool operator!=(const RCString& lhs, const RCString& rhs);
bool operator>(const RCString& lhs, const RCString& rhs);
bool operator<(const RCString& lhs, const RCString& rhs);


}//ilrd

#endif // __RCSTRING_H__

