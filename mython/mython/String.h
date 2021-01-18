#ifndef STRING_H
#define STRING_H



#include "Sequence.h"

class String : public Sequence
{
public:
	String(std::string var);
	bool isPrintable() const;
	std::string toString() const;
	
private:
	std::string _var;
};
#endif // STRING_H