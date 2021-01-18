#ifndef VOID_H
#define VOID_H

#include "type.h"

class Void : public Type
{
public:
	Void(void) {};
	bool isPrintable() const;
	std::string toString() const;
};
#endif // VOID_H