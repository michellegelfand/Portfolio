#include "Integer.h"

Integer::Integer(int var)
	:_var(var)
{
}

bool Integer::isPrintable() const
{
	return true;
}

std::string Integer::toString() const
{
	return std::to_string(_var);
}
