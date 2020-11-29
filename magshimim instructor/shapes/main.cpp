#include "Menu.h"

using std::cin;
using std::cout;

const int EXIT = 9;

Menu m;

int main()
{
		
	try
	{
		m.mainMenu();		
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
		

	return 0;
}