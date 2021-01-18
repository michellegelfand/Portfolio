#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "type.h"

//This class represents a sequence of another type
class Sequence: public Type
{
public:
	virtual bool isPrintable() const = 0;
	virtual std::string toString() const = 0;
	virtual ~Sequence() {};
};
#endif // SEQUENCE_H