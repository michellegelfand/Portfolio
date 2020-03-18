#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

namespace ilrd
{

struct Bad_Create : public std::runtime_error
{
	Bad_Create(const std::string& s = "bad create")
		: std::runtime_error(s) { }
};

struct Bad_Key : public std::logic_error
{
	Bad_Key(const std::string& s = "bad key")
		: std::logic_error(s) { }
};


}//ilrd

#endif //__EXCEPTIONS_HPP__