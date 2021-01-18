#include <iostream>
#include <string>

#include "parser.h"
#include "Integer.h"
#include "Boolean.h"
#include "Void.h"
#include "String.h"
#include "IndentationException.h"
#include "Helper.h"
#include "List.h"

std::unordered_map<std::string, Type*> Parser::_variables;

Type* Parser::parseString(std::string str) 
{
	Type* t;
	if (str.length() > 0)
	{

		if (str[0] == ' ' || str[0] == '\t')
		{
			throw IndentationException();
		}
		Helper::rtrim(str);

		t = getVariableValue(str);
		if ( t != nullptr)
		{//if user typed existing variable return its value
			
			return t;
		}

		t = getType(str);
		if ( t != nullptr)
		{
			t->setIsTemp(true);
			return t;
		}
		if (makeAssignment(str))
		{
			t = new Void();
			return t;
		}
		else if (isLegalVarName(str))
		{
			throw NameErrorException(str);
		}
		
	}

	return nullptr;
	
}

List* Parser::getTypeListHelper(std::string str)
{
	std::vector<Type*> holdMembers;

	Type* t; //will be used to push created members into vector
	std::string member_substr;
	std::istringstream iss(str.substr(1, str.size() - 2));

	while (std::getline(iss, member_substr, ','))
	{
		Helper::trim(member_substr);
		t = getType(member_substr);

		if (t == nullptr) //member in list is invalid type
		{
			for (Type* ty : holdMembers)
			{
				delete ty;
				ty = nullptr;
			}
			holdMembers.clear();
			return nullptr;
		}
		holdMembers.push_back(t);

	}

	List* list = new List(holdMembers);
	return list;
}


String* Parser::getTypeStringHelper(std::string str)
{
	bool hasSingleQuationMark = false;
	if (str[0] == '\"')
	{
		for (unsigned int i = 1; i < str.size() - 1; i++)
		{
			if (str[i] == '\"')
			{
				return nullptr; //invalid string
			}
			if (str[i] == '\'')
			{
				hasSingleQuationMark = true;
			}
		}
	}
	if (str[0] == '\'')
	{
		for (unsigned int i = 1; i < str.size() - 1; i++)
		{
			if (str[i] == '\'')
			{
				return nullptr; //invalid string
			}
		}

	}
	//string will be saved with ' mark even if originally was written with "
	//unless it has a ' char within it, then saved with double quatation marks
	if (!hasSingleQuationMark)
	{
		str[0] = '\'';
		str[str.size() - 1] = '\'';
	}
	String* s = new String(str);
	return s;
}

Void* Parser::callDelHelper(std::string str)
{
	std::string var_to_delete = str.substr(str.find("del ") + 4);

	if (_variables.find(var_to_delete) == _variables.end())
	{
		throw NameErrorException(var_to_delete);
	}
	_variables.erase(var_to_delete);
	Void* v = new Void();
	v->setIsTemp(true);
	return v;
}

String* Parser::TypeFunc(std::string str)
{
	//call type func
	std::string typeTocheck = str.substr(str.find("type(") + 5);
	typeTocheck[typeTocheck.length() - 1] = ' '; //replace )
	Helper::trim(typeTocheck);
	std::unordered_map<std::string, Type*>::iterator findExisting = _variables.find(typeTocheck);
	if (findExisting != _variables.end())
	{
		if (Helper::isInteger(findExisting->second->toString()))
		{
			String* s = new String("<type 'int'>");
			s->setIsTemp(true);
			return s;
		}
		if (Helper::isString(findExisting->second->toString()))
		{
			String* s = new String("<type 'String'>");
			s->setIsTemp(true);
			return s;
		}
		if (Helper::isBoolean(findExisting->second->toString()))
		{
			String* s = new String("<type 'Boolean'>");
			s->setIsTemp(true);
			return s;
		}
		if (findExisting->second->toString()[0] == '[' &&
			findExisting->second->toString()[findExisting->second->toString().length() - 1] == ']')
		{
			std::vector<Type*> holdMembers;
			Type* t;
			std::string member_substr;
			std::istringstream iss(findExisting->second->toString().substr(1, findExisting->second->toString().size() - 2));

			while (std::getline(iss, member_substr, ','))
			{
				Helper::trim(member_substr);
				t = getType(member_substr);

				if (t == nullptr) //member in list is invalid type
				{
					return nullptr;
				}
			}

			String* s = new String("<type 'List'>");
			s->setIsTemp(true);
			return s;
		}
	}
	else
	{
		if (Helper::isInteger(typeTocheck))
		{
			String* s = new String("<type 'int'>");
			s->setIsTemp(true);
			return s;
		}
		if (Helper::isString(typeTocheck))
		{
			String* s = new String("<type 'String'>");
			s->setIsTemp(true);
			return s;
		}
		if (Helper::isBoolean(typeTocheck))
		{
			String* s = new String("<type 'Boolean'>");
			s->setIsTemp(true);
			return s;
		}
		if (typeTocheck[0] == '[' && typeTocheck[typeTocheck.length() - 1] == ']')
		{
			std::vector<Type*> holdMembers;
			Type* t;
			std::string member_substr;
			std::istringstream iss(typeTocheck.substr(1, typeTocheck.size() - 2));

			while (std::getline(iss, member_substr, ','))
			{
				Helper::trim(member_substr);
				t = getType(member_substr);

				if (t == nullptr) //member in list is invalid type
				{
					return nullptr;
				}
			}

			String* s = new String("<type 'List'>");
			s->setIsTemp(true);
			return s;
		}
		return nullptr;
	}
}


Type* Parser::getType(std::string& str)
{
	if (str == "True")
	{
		//check for bool
		Boolean* b = new Boolean(1);
		return b;
	}
	else if (str == "False")
	{
		//check for bool
		Boolean* b = new Boolean(0);
		return b;
	}
	if (Helper::isInteger(str))
	{
		//check for int
		Helper::removeLeadingZeros(str);
		Integer* i = new Integer(atoi(str.c_str())); 
		return i;
	}
	if (Helper::isString(str))
	{
		//check for string
		return getTypeStringHelper(str);
	}
	if (str[0] == '[' && str[str.length() -1] == ']')
	{
		//check for list
		return getTypeListHelper(str);
	}
	if ((str.rfind("del ", 0) == 0))
	{
		//check if calling del func
		return callDelHelper(str);
	}
	if ((str.rfind("type(", 0) == 0) && str[str.length() - 1] == ')')
	{//check if calling type func
		return TypeFunc(str);
	}
	String* s = getFunctionInfo(str);
	if (s != nullptr)
	{//get function definition
		return s;
	}

	return nullptr;
}
String* Parser::getFunctionInfo(std::string str)
{
	String* s;
	if (str == "type" || str == "del" || str == "len")
	{
		s = new String("<built-in function " + str + ">");
		s->setIsTemp(true);
		return s;
	}

	return nullptr;
}

void Parser::cleanVarsFromMemory()
{
	for (std::pair<std::string, Type*> v : _variables)
	{
		delete v.second;
		v.second = nullptr;
	}

	_variables.clear();
}

bool Parser::isLegalVarName(const std::string& str)
{
	if (Helper::isDigit(str[0]))
	{
		return false;
	}

	for (const char& c : str)
	{
		if (!Helper::isLetter(c) && !Helper::isDigit(c) && !Helper::isUnderscore(c))
		{
			return false;
		}
	}

	return true;
}

bool Parser::makeAssignment(const std::string& str)
{
	if (str.find('=') == std::string::npos)
	{
		return false;
	}
	std::string var_name;
	std::string value;

	value = str.substr(str.find('=')+1, str.size() - str.find('='));
	
	int i = 0;
	while(str[i] != '=')
	{
		var_name += str[i];
		i++;
	}


	Helper::trim(value);
	Helper::trim(var_name);

	if (!isLegalVarName(var_name))
	{
		throw SyntaxException();
	}
	

	if (_variables.find(value) != _variables.end())
	{
		//variable = variable
		if (_variables.find(value)->second->toString()[0] == '[')
		{
			//if list 
			//does NOT deep copy in python
			_variables[var_name] = _variables.find(value)->second;
			return true;
		}
		Type* t = _variables.find(value)->second;
		if (_variables.find(var_name) != _variables.end())
		{//if var already exists delete old value
			_variables.erase(var_name);
		}
		std::string getValueFromVar = t->toString();
		Type* assign = getType(getValueFromVar);
		_variables.insert(std::pair<std::string, Type*>(var_name, assign));
		return true;
	}
	else if(nullptr == getType(value))
	{
		
		throw NameErrorException(value);
		
	}
	else
	{//variable = value

	
		if (_variables.find(var_name) != _variables.end())
		{//if variable name already exists replace its value 
			_variables.erase(_variables.find(var_name));
		}
		Type* t = getType(value);
		t->setIsTemp(0);
		_variables[var_name] = t;
		return true;
	}

}

Type* Parser::getVariableValue(const std::string& str)
{
	std::unordered_map<std::string, Type*>::iterator it = _variables.find(str);
	if (it == _variables.end())
	{
		return nullptr;
	}
	return it->second;
}








