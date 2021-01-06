#pragma once

#include <exception>

class DenominatorIsZeroException : public std::exception
{
public:
	virtual const char* what() const throw();
};

