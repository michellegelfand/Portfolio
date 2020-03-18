#ifndef  __SANTA_TOOLS_HPP__
#define  __SANTA_TOOLS_HPP__

#define BLU  			"\x1B[34m"
#define RED  			"\x1B[31m"
#define GRN  			"\x1B[32m"
#define NRM  			"\x1B[0m"
#define YELLOW 			"\033[93m"
#define BOLD 			"\033[01m"
#define MAGENTA 		"\033[35m"
#define CYAN 			"\033[36m"
#define LIGHT_CYAN      "\x1b[36m\x1b[1m"
#define PURPLE 			"\033[35m"
#define LIGHT_BLU 		"\033[94m"
#define LIGHT_PURPLE 	"\033[95m"
#define LIGHT_GRN 		"\033[92m"
#define TURQUOISE 		"\033[96m"
#define ORANGE    		"\x1b[33m"
#define WHITE     		"\x1B[37m"

#define RED_BACKGRND 	"\033[41;41m"
#define WHITE_BACKGRND 	"\033[47;47m"
#define BLACK_BACKGRND 	"\033[40;40m"
#define GREEN_BACKGRND 	"\033[42;42m"
#define BLUE_BACKGRND 	"\033[44;44m"
#define KCYN 			"\x1B[40;96m"
#define MINTBCK     	"\x1b[46m"

#define SIZE_OF_ARRAY(a)    sizeof(a)/sizeof(a[0])

#ifdef DEBUG
	#include <iostream>
	#define DEBUG_ONLY(code) code
#else
#define DEBUG_ONLY(code) 
#endif

#endif /*__SANTA_TOOLS_HPP__*/




