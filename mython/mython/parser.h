#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "InterperterException.h"
#include "SyntaxException.h"
#include "type.h"
#include "Helper.h"
#include "NameErrorException.h"
#include "List.h"
#include "String.h"
#include "Void.h"

class Parser
{
public:
	static Type* parseString(std::string str);
	static Type* getType(std::string &str);
	
	static std::unordered_map<std::string, Type*> _variables;
	static void cleanVarsFromMemory();
private:

	static bool isLegalVarName(const std::string& str);
	static bool makeAssignment(const std::string& str);
	static Type* getVariableValue(const std::string &str);

	/*A helper function called by the getType method to return List data type
	* Recieves: list in string format given by user
	* Returns: Pointer to List object created or nullptr if list requested is invalid
	*/
	static List* getTypeListHelper(std::string str);
	static String* getTypeStringHelper(std::string str);
	static Void* callDelHelper(std::string str);
	static String* TypeFunc(std::string str);
	static String* getFunctionInfo(std::string str);
};

#endif //PARSER_H
