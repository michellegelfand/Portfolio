/**********************************************************************;
* Project           : Data Structures
*
* Program name      : task.c
*
* Author            : Michelle Gelfand
*
* Date created      : 07.07.19
*
* Purpose           : This program provides the user
					  with a memory segment managing infrastructure.
*
* Version           : 1.2
*
* Review Status		: 
*
* Date Approved       Author	 	             Reviewer 
* 08/07/2019       	  Michelle Gelfand           Saar Y. *														  
*******************************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/

#include "fsm.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

#define SUCCESS {printf(GREEN"\nSuccess\n"WHITE);} 
#define FAIL {printf(RED"\n!!Fail!!\n"WHITE);test_result+=1;}; 
#define SUCCESSORFAIL {SUCCESS}else{FAIL} 

int FsmInit_test();
int FsmCountFree_test();
int FsmAlloc_test();
int FsmFree_test();
int FsmSuggestedSize_test();

int main()
{
	int test_result = 0;
	test_result |= FsmInit_test();
	test_result |= FsmCountFree_test();
	test_result |= FsmAlloc_test();
	test_result |= FsmFree_test();
	test_result |= FsmSuggestedSize_test();

	(0 == test_result)? printf(KCYN"\n\nALL TESTS PASSED\n\n"WHITE) :
						printf(RED"\n\nFailed on some tests\n\n"WHITE);
	return 0;
}

int FsmInit_test()
{
	int test_result = 0;
	void* mem_area = malloc(40);

	mem_area = FsmInit(mem_area, 40, 7);

	printf(YELLOW"\nI N I T   T E S T\n"WHITE);

	if( 4 == FsmCountFree(mem_area))
	SUCCESSORFAIL;

	if( 4 != FsmCountFree(mem_area))
	{
		printf(BLUE"\nexpected count 4, but counted: %lu\n",
		FsmCountFree(mem_area));
	}
	free(mem_area);
	return test_result;
}
int FsmCountFree_test()
{
	int test_result = 0;
	void* mem_area = malloc(88);

	mem_area = FsmInit(mem_area, 88, 7);

	printf(YELLOW"\nC O U N T   T E S T\n"WHITE);

	if( 10 == FsmCountFree(mem_area))
	SUCCESSORFAIL;

	if( 10 != FsmCountFree(mem_area))
	{
		printf(BLUE"\nexpected count 10, but counted: %lu\n",
		FsmCountFree(mem_area));
	}
	free(mem_area);
	return test_result;

}
int FsmAlloc_test()
{
	int test_result = 0;
	void* data = NULL;
	void* mem_area = malloc(88);
	mem_area = FsmInit(mem_area, 88, 7);

	printf(YELLOW"\nA L L O C  T E S T\n"WHITE);
	
	data = FsmAlloc(mem_area);

	if( 9 == FsmCountFree(mem_area))
	SUCCESSORFAIL;

	if( 9 != FsmCountFree(mem_area))
	{
		printf(BLUE"\nfailed to alloc 1 block: should be 9 left, left: %lu\n",
		FsmCountFree(mem_area));
	}
	(void)data;
	free(mem_area);
	return test_result;
}
int FsmFree_test()
{
	
	int test_result = 0;
	void* data = NULL;
	void* mem_area = malloc(88);
	mem_area = FsmInit(mem_area, 88, 7);

	printf(YELLOW"\nF R E E  T E S T\n"WHITE);
	
	data = FsmAlloc(mem_area);

	FsmFree(mem_area, data);

	if( 10 == FsmCountFree(mem_area))
	SUCCESSORFAIL;

	if( 10 != FsmCountFree(mem_area))
	{
		printf(BLUE"\nfailed to free 1 block: should be 10 free, free: %lu\n",
		FsmCountFree(mem_area));
	}
	(void)data;
	free(mem_area);
	return test_result;

}
int FsmSuggestedSize_test()
{
	int test_result = 0;
	printf(YELLOW"\nS U G G E S T E D    S I Z E   T E S T\n"WHITE);
	if( 1608 == FsmSuggestedSize(15, 100))
	SUCCESSORFAIL;

	if( 1608 != FsmSuggestedSize(15, 100))
	{
		printf("\n size suggested: %lu\n", FsmSuggestedSize(15, 100));
	}
	return test_result;
}



