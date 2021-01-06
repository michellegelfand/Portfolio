#include "DenominatorIsZeroException.h"


const char* DenominatorIsZeroException::what() const 
{
	return "Exception: denominator is zero\n";
};