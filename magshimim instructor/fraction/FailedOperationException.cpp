#include "FailedOperationException.h"



const char* FailedOperationException::what() const
{
	return "Exception: operation failed. May be a result of deviding by 0\n";
};