#include "String.h"

String::String(std::string var)
	:_var(var)
{
}

bool String::isPrintable() const
{
	return true;
}

std::string String::toString() const
{
	return _var;
}
