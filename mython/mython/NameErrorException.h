#ifndef NAME_ERROR_EXCEPTION_H
#define NAME_ERROR_EXCEPTION_H

#include <exception>
#include <string>
class NameErrorException : public std::exception
{
public:
	NameErrorException(std::string name);
	virtual const char* what() const throw();

private:
	std::string _name;
	char* _c_str;
};
#endif // NAME_ERROR_EXCEPTION_H