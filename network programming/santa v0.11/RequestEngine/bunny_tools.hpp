#ifndef  __BUNNY_TOOLS_HPP__
#define  __BUNNY_TOOLS_HPP__

#ifndef NDEBUG
	#include <iostream>
	#define DEBUG_ONLY(code) code
#else
	#define DEBUG_ONLY(code)
#endif

#define BLU  "\x1B[34m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define NRM  "\x1B[0m"
#define YELLOW "\033[33m"
#define BOLD "\033[01m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

#define RED_BACKGRND "\033[41;41m"
#define WHITE_BACKGRND "\033[47;47m"
#define BLACK_BACKGRND "\033[40;40m"
#define GREEN_BACKGRND "\033[42;42m"
#define BLUE_BACKGRND "\033[44;44m"

#define TITLE(str) std::cout << MAGENTA << BOLD << str << NRM << std::endl;




#endif /*__BUNNY_TOOLS_HPP__*/
