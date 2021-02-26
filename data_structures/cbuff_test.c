/**********************************************************************;
* Project           : Data Structures
*
* Program name      : cbuff.c
*
* Author            : Michelle Gelfand
*
* Date created      : 13.06.19
*
* Purpose           : This program provides the user with a circular
*					  buffer to write and read from, as well as 
*					  additional operations		 				  
*
* Review Status		: Approved
*
* Date Approved        Author			          Reviewer 
* 15.06.19		       Michelle Gelfand           Inbar Duek   *														  
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "cbuff.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"

cbuff_t *CBuffCreate_test(size_t n_bytes);
void CBDestroy_test();
void CBRead_test(cbuff_t *c_buff, void *dest, void *src);
void CBWrite_test(cbuff_t *c_buff, const void *src);
void CBCapacity_test();
void CBIsEmpty_test();
void CBFreeSpace_test();

typedef struct test
{
	char string[4];
	int num;
}test;

int main()
{
	/*struct size = 16*/
	cbuff_t *c_buff = 0;
	test src[6] = { {"woof", 0x04030201},
				    {"ding",  0x08070605}, 
				    {"meow", 0x12111009}, 
					{"rbek", 0x16151413}, 
					{"hiss", 0x20191817},
					{"erno", 0x24232221} };

	test dest[6] = {0};

	c_buff = CBuffCreate_test(sizeof(test) * 5);

	CBDestroy_test();
	
	c_buff = CBuffCreate( sizeof(test) * 2);

	CBWrite_test(c_buff, src);
	
	free(c_buff);

	c_buff = CBuffCreate( sizeof(test) * 2);
	
	CBRead_test(c_buff, dest, src);

	free(c_buff);
		
	CBFreeSpace_test();

	CBCapacity_test();

	CBIsEmpty_test();

	return 0;
}
cbuff_t *CBuffCreate_test(size_t n_bytes)
{
	cbuff_t *c_buff = CBuffCreate(n_bytes);

	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nCREATE circular buffer test:\n\n"WHITE);
	printf(BLUE"\n\nstandard create test:\n\n"WHITE);
	printf(BLUE"\nexpected result: Success\n\n"WHITE);

	if ( NULL != c_buff )
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

	free(c_buff);
	c_buff = CBuffCreate(n_bytes * 999999999999);

	printf(BLUE"\n\ndata overflow create test (too many bytes)\n \
	must fail creation:\n\n"WHITE);
	if ( NULL == c_buff )
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

	printf(YELLOW"\n\ncombine this test with valgrind\n\n"WHITE);
	free(c_buff);
	return c_buff;
}
void CBDestroy_test()
{
	cbuff_t *c_buff = CBuffCreate(7);
	CBuffDestroy(c_buff);

	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nDestroy circular buffer test:\n\n"WHITE);
	
	printf(YELLOW"\n\ncombine this test with valgrind\n\n"WHITE);

}
void CBWrite_test(cbuff_t *c_buff, const void *src)
{

	ssize_t written = CBuffWrite(c_buff, src,sizeof(test));
	
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nWRITE to circular buffer test:\n\n"WHITE);
	printf(BLUE"\nWrite to empty buffer:\n\n"WHITE);


	if ( 1*sizeof(test) == written)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

	printf(BLUE"\nOverwrite to buffer: only 8 out of 16 bytes written\n\n"WHITE);

	written = CBuffWrite(c_buff, (char*)src+sizeof(test), 2*sizeof(test));

	if (1*sizeof(test) == written)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
	printf(BLUE"\nTry writing to full buffer: must fail (return 0)\n\n"WHITE);
	written = CBuffWrite(c_buff, (char*)src+sizeof(test), 2*sizeof(test));

	if ( 0 == written)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
}
void CBRead_test(cbuff_t *c_buff, void *dest, void *src)
{
	ssize_t read = 0;
	printf(YELLOW"\n\nRead circular buffer test:\n\n"WHITE);
	printf(BLUE"\nNo bytes to read: must return 0\n\n"WHITE);

	

	read = CBuffRead(c_buff, dest ,sizeof(test));

	if ( 0 == read)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
	
	printf(BLUE"\nRead 8 bytes with a jump from end on buffer to start:\n\n"WHITE);

	(void)CBuffWrite(c_buff, src, 2*sizeof(test));
	(void)CBuffRead(c_buff, src,2*sizeof(test)-4);
	(void)CBuffWrite(c_buff, src, 8);
	read = CBuffRead(c_buff, src,2*sizeof(test)-4);
	
	if (12 == read)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

}
void CBFreeSpace_test()
{
	int src[] = {4,6,5,7,8};
	size_t free_space = 0;
	cbuff_t* c_buff = CBuffCreate(20);

	printf(YELLOW"\n\nFree Space test:\n\n"WHITE);
	printf(BLUE"\nempty cbuff: freespace is 20\n\n"WHITE);
  
	free_space = CBuffFreeSpace(c_buff);

	if (20 == free_space)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

	printf(BLUE"\nafter push: freeSpace is 10\n\n"WHITE);

	(void)CBuffWrite(c_buff, src, 10);
	free_space = CBuffFreeSpace(c_buff);

	if (10 == free_space)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
			printf(RED"\n!! FAILED !!\n"WHITE);
	}
	free(c_buff);
}
void CBCapacity_test()
{
	size_t capacity = 0;
	cbuff_t* c_buff = CBuffCreate(20);

	printf(YELLOW"\n\nCapacity test:\n\n"WHITE);

  
	capacity = CBuffCapacity(c_buff);

	if (20 == capacity)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
	free(c_buff);
	
}
void CBIsEmpty_test()
{
	int src[] = {3,5,4,3,4};
	cbuff_t* c_buff = CBuffCreate(20);

	printf(YELLOW"\n\nIs Empty test:\n\n"WHITE);
	printf(BLUE"\nWhen buffer IS empty: return 1\n\n"WHITE);	
	if (1 ==  CBuffIsEmpty(c_buff))
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
	
	(void)CBuffWrite(c_buff, src, 2);

	printf(BLUE"\nafter push: return buffer is not empty 0\n\n"WHITE);

	if (0 ==  CBuffIsEmpty(c_buff))
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
	free(c_buff);

}


