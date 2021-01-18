#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "type.h"

class Boolean : public Type
{
public:
	Boolean(bool var);
	bool isPrintable() const;
	std::string toString() const;
private:
	bool _var;
};
#endif // BOOLEAN_H