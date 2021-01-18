#include <iostream>

#include "type.h"
#include "InterperterException.h"
#include "parser.h"
#include "SyntaxException.h"


#define WELCOME "Welcome to Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "[Michelle Gelfand]"


int main(int argc,char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);
	
	while (input_string != "quit()")
	{
		try
		{
			// prasing command
			Type* t = Parser::parseString(input_string);
			if (t != nullptr)
			{
				if (t->isPrintable())
				{
					std::cout << t->toString() << std::endl;
				}
				if (t->getIsTemp())
				{
					delete t;
				}
			}
			else
			{
				throw SyntaxException();
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}


		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
		
		
	}

	Parser::cleanVarsFromMemory();

	return 0;
}


