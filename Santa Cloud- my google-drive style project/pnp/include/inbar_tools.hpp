/******************************************************************************/
/*    @File:       olga_tools.h                                               */
/*    @Created:    09.08.19                                                   */
/*    @Version:    1.0	                                                      */
/*    @Author:     Olga Komarovsky Chashka                                    */
/******************************************************************************/

#ifndef  __INBAR_TOOLS_HPP__
#define  __INBAR_TOOLS_HPP__

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

#define LABEL(str) std::cout << CYAN << str << NRM << std::endl <<std::endl
#define FAIL(str) std::cout << RED << str << NRM << std::endl
#define PASS(str) std::cout << GRN << str << NRM << std::endl
#define FINAL_PASS(str) std::cout << GRN << BOLD << str << NRM << std::endl
#define FINAL_FAIL(str) std::cout << RED << BOLD << str << NRM << std::endl


#define SIZE_OF_ARRAY(a)    sizeof(a)/sizeof(a[0])


#ifndef NDEBUG
	#include <iostream>
	#define DEBUG_ONLY(code) code
#else
	#define DEBUG_ONLY(code) 
#endif



#endif /*__INBAR_TOOLS_HPP__*/

