#include "type.h"

Type::Type(bool isTemp)
	:_isTemp(isTemp)
{
}

void Type::setIsTemp(bool isTemp)
{
	_isTemp = isTemp;
}

bool Type::getIsTemp() const
{
	return _isTemp;
}
