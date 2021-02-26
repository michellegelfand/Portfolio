/**********************************************************************;
* Project           : Data Structures
*
* Program name      : vsm.c
*
* Author            : Michelle Gelfand
*
* Date created      : 09.07.19
*
* Purpose           : This program provides the user
					  with a dynamic size allocatable memory segment.
*
* Version           : 1.1.2
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 11/07/2019       	  Michelle Gelfand           Assaf B. *														  
*******************************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <malloc.h>/*malloc_stats*/

#include "vsm.h"

/*colours */
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

/*SUCCESSORFAIL */
#define SUCCESS {printf(GREEN"\nSuccess\n"WHITE);} 
#define FAIL {printf(RED"\n!!Fail!!\n"WHITE);test_result+=1;}; 
#define SUCCESSORFAIL {SUCCESS}else{FAIL} 

int VsmInit_test();
int VsmAlloc_test();
int VsmFree_test();

void PrintPool(void *memory);

int main()
{
	int test_result = 0;

    test_result |= VsmInit_test();
	test_result |= VsmAlloc_test();
	test_result |= VsmFree_test();

	(0 == test_result)? printf(KCYN"\n\nALL TESTS PASSED\n\n"WHITE) :
						printf(RED"\n\nFailed on some tests\n\n"WHITE);
	return 0;
}

int VsmInit_test()
{
	int test_result = 0;
	void *mem_pool = malloc(800);
	
	if(VsmInit(mem_pool, 800))
	SUCCESSORFAIL;

	printf(YELLOW"\n\nI N I T   T E S T\n\n"WHITE);
	malloc_stats();

	free(mem_pool);

	return test_result;
}
int VsmAlloc_test()
{
	int test_result = 0;
	void *mem_pool = malloc(800);
	vsm_mem_pool_t *block = NULL;
	vsm_mem_pool_t *block2 = NULL;	
	vsm_mem_pool_t *block3 = NULL;
	VsmInit(mem_pool, 800);

	printf(YELLOW"\n\nA L L O C   T E S T\n\n"WHITE);

	block = VsmAlloc((vsm_mem_pool_t*)mem_pool, 14l);
	block2 = VsmAlloc((vsm_mem_pool_t*)mem_pool, 30);
	block3 = VsmAlloc((vsm_mem_pool_t*)mem_pool, 550);
	if(block)
	SUCCESSORFAIL;

	printf(BLUE"\n\nCombine test with print pool to see result\n\n"WHITE);
	
    VsmFree(block2);
	VsmFree(block3);
	block3 = VsmAlloc((vsm_mem_pool_t*)mem_pool, 38);
	free(mem_pool);

	return test_result;
}

int VsmFree_test()
{
	int test_result = 0;
	void *mem_pool = malloc(800);
	vsm_mem_pool_t *block = NULL;

	VsmInit(mem_pool, 800);

	printf(YELLOW"\n\nF R E E  T E S T\n\n"WHITE);

	block = VsmAlloc((vsm_mem_pool_t*)mem_pool, 14l);

	VsmFree(block);

	printf(BLUE"\n\nCombine test with print pool to see result\n\n"WHITE);

	/*PrintPool(mem_pool);*/
	free(mem_pool);

	return test_result;
}
