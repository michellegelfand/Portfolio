#ifndef INTEGER_H
#define INTEGER_H
#include "type.h"

class Integer : public Type
{
public:
	Integer(int var);
	bool isPrintable() const;
	std::string toString() const;
private:
	int _var;
};

#endif // INTEGER_H