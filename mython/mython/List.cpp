#include "List.h"

List::List(const std::vector<Type*>& members)
{
	for (Type* t: members)
	{
		_members.push_back(t);
	}
}

bool List::isPrintable() const
{
    return true;
}

std::string List::toString() const
{
	std::string stringedList = "[ ";
	for (Type* t : _members)
	{
		stringedList += t->toString();
		stringedList.append(" , ");
	}
	
	stringedList.erase(stringedList.end()-2);
	stringedList += ']';

	return stringedList;
}
