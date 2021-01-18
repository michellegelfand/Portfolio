#include "Boolean.h"

Boolean::Boolean(bool var)
	:_var(var)
{
}

bool Boolean::isPrintable() const
{
	return true;
}

std::string Boolean::toString() const
{
	return _var? "True" : "False";
}
