
#ifndef __TEST_TOOLS_H_
#define __TEST_TOOLS_H_

#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
#define CT_ASSERT(e) enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }


#define GREEN "\033[32m"
#define RED "\033[31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[33m"
#define KCYN "\033[96m"

#ifndef NDEBUG
	#include <stdio.h>
	#define DEBUG_ONLY(code) code
#else
#define DEBUG_ONLY(code) 
#endif


typedef int make_iso_compilers_happy;

#endif /* __TEST_TOOLS_H__ */
