/**********************************************************************;
* Project           : Data Structures
*
* Program name      : stack_test.c
*
* Author            : Michelle Gelfand
*
* Date created      : 10.06.19
*
* Purpose           : This program provides the user with a stack 
*                     data structure, and operations to store and access 
*					  data in it.
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 12/06/2019       	  Michelle Gelfand           Waed Bader *														  
**********************************************************************/
#include <stdio.h>
#include <stdio.h>

#include "stack.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"

stack_t* StackCreate_test(size_t element_size, size_t capacity);
void StackDestroy_test(stack_t *stack);
void IntStackPeek_test( stack_t *stack);
void IntStackPush_test(stack_t *stack);
void IntStackPop_test(stack_t *stack);
void IntStackSize_test(stack_t *stack);


void FltStackPeek_test( stack_t *stack);
void FltStackPush_test(stack_t *stack);
void FltStackPop_test(stack_t *stack);
void FltStackSize_test(stack_t *stack);

void StatusTestResults(status_t status, status_t condition);

int main()
{
	/*int tests*/
	
	stack_t* stack = NULL;
	printf(YELLOW"\n\nINT STACK TESTS\n\n"WHITE);
	stack= StackCreate_test(4, 3);
	IntStackPush_test(stack);
	IntStackPop_test(stack);
	IntStackSize_test(stack);
	IntStackPeek_test(stack);
	StackDestroy_test(stack);

	/*flt tests*/
	printf(YELLOW"\n\nFLT STACK TESTS\n\n"WHITE);
	stack= StackCreate_test(8, 3);
	FltStackPush_test(stack);
	FltStackPop_test(stack);
	FltStackSize_test(stack);
	FltStackPeek_test(stack);
	StackDestroy_test(stack);

	return 0;
}

stack_t* StackCreate_test(size_t element_size, size_t capacity)
{
	stack_t* new_stack = StackCreate(element_size, capacity);
	
	printf(BLUE"\n\nStackCreate test:\n"WHITE);
	/*if alloc failed returns null ptr*/
	if(NULL != new_stack)
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed\n"WHITE);
	}
	return new_stack;

}
void StackDestroy_test(stack_t *stack)
{
	printf(BLUE"\n\nIntStack Destroy test:\n"WHITE);
	StackDestroy(stack);

	printf("\nCombine this test with valgrind to assure no memory leak\n\n");

}

void IntStackPush_test(stack_t *stack)
{
	int* peek_stack = NULL;
	int values[] = {3, 6, 9, 8, 7};
	printf(BLUE"\n\nStack Push test:\n"WHITE);
	peek_stack =StackPeek(stack); 
	printf("\npeek tail: %p\n\n", (void*)peek_stack);

	printf("\nPush into empty array:\n");
	printf("\nExpected status: SUCCESS 0 \n");
	StatusTestResults(StackPush(stack, values), SUCCESS); 
	printf("\npeek tail: %d\n", *((int*)StackPeek(stack)));
 	printf("\n*********************************\n");
	printf("\n\nPush into non full & non empty array:\n");
	printf("\nExpected status: SUCCESS 0 \n");
	StatusTestResults(StackPush(stack, values+1), SUCCESS); 
	printf("\npeek tail: %d\n", *((int*)StackPeek(stack)));
	printf("\n*********************************\n");
	StatusTestResults(StackPush(stack, values+2), SUCCESS);
	printf("\npeek tail: %d\n", *((int*)StackPeek(stack)));
	printf("\n*********************************\n");
	printf("\nPush when array is full:\n");
	printf("\nExpected status: STACK_FULL 1\n");
	StatusTestResults(StackPush(stack, values+3), STACK_FULL);
	printf("\npeek tail: %d\n", *((int*)StackPeek(stack)));
	printf("\n*********************************\n");
	StatusTestResults(StackPush(stack, values+4), STACK_FULL);
	printf("\npeek tail: %d\n", *((int*)StackPeek(stack)));
	printf("\n*********************************\n");
	

}
void IntStackPop_test(stack_t *stack)
{
	
	printf(BLUE"\n\nStack Pop test:\n"WHITE);

	
 	
	printf("\npeek tail: %d\n", *(int*)StackPeek(stack));

	
	StackPop(stack);
	printf("\npeek tail: %d\n", *(int*)StackPeek(stack));
	if (6 == *(int*)StackPeek(stack))
	{
		printf("\nExpected val: 6 : "GREEN"Success\n"WHITE );
	}
	else
	{
		printf("\nExpected val: 6  "RED"Failed\n"WHITE);
		
	}

	StackPop(stack);
	printf("\npeek tail: %d\n", *(int*)StackPeek(stack));
	if (3 == *(int*)StackPeek(stack))
	{
		printf("\nExpected val: 3  : "GREEN"Success\n"WHITE );
	}
	else
	{
		printf("\nExpected val: 3  "RED"Failed\n"WHITE);
		
	}

	StackPop(stack);
	printf("\npeek tail: %p\n", (void*)(int*)StackPeek(stack));
	printf("\nPopping empty stack:\n");
	StackPop(stack);
	printf("\npeek tail: %p\n", (void*)(int*)StackPeek(stack));
	StackPop(stack);
	printf("\npeek tail: %p\n", (void*)(int*)StackPeek(stack));


}
void StatusTestResults(status_t status, status_t condition)
{

	if (status == condition)
	{
		printf("\nReturned status: %d : "GREEN"Success\n"WHITE, condition );
	}
	else
	{
		printf("\nReturned status: %d "RED"Failed\n"WHITE, condition );
		
	}

}

void IntStackSize_test(stack_t *stack)
{
	int array[] = {7,8};
	size_t size = 0;
	printf(BLUE"\nStack size test:\n"WHITE);
	StackPush(stack, array);	
	
	size = StackSize(stack);

	
	if (1 == size)
	{
		printf("\nsize = 1 : "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\nsize = 1:  "RED"Failed\n"WHITE );
		
	}

	StackPush(stack, array+1);	
	
	size = StackSize(stack);
	

	if (2 == size)
	{
		printf("\nsize = 2 : "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\nsize = 2:  "RED"Failed\n"WHITE );
		
	}
	
	StackPop(stack);
	StackPop(stack);
	size = StackSize(stack);
	

	if (0 == size)
	{
		printf("\nsize = 0 : "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\nsize = 0:  "RED"Failed\n"WHITE );
		
	}
}
void IntStackPeek_test(stack_t *stack)
{	
	int array[] = {7,8};
	printf(BLUE"\nStack Peek test:\n"WHITE);
	printf("\nempty stack:\n");
	if (NULL == StackPeek(stack))
	{
		printf("\npeek: NULL "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\npeek: NULL "RED"Failed\n"WHITE );
		
	}
	printf("\nnon-empty stack:\n");
	StackPush(stack, array+1);
	if (8 == *(int*)StackPeek(stack))
	{
		printf("\npeek: 8 "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\npeek: 8 "RED"Failed\n"WHITE );
		
	}

}
/*******************************flt tests**********************************/
void FltStackPush_test(stack_t *stack)
{
	float* peek_stack = NULL;
	float values[] = {3.1, 6.1, 9.1, 8.1, 7.1};
	printf(BLUE"\n\nStack Push test:\n"WHITE);
	peek_stack =StackPeek(stack); 
	printf("\npeek tail: %p\n\n", (void*)peek_stack);

	printf("\nPush into empty array:\n");
	printf("\nExpected status: SUCCESS 0 \n");
	StatusTestResults(StackPush(stack, values), SUCCESS); 
	printf("\npeek tail: %f\n", *((float*)StackPeek(stack)));
 	printf("\n*********************************\n");
	printf("\n\nPush into non full & non empty array:\n");
	printf("\nExpected status: SUCCESS 0 \n");
	StatusTestResults(StackPush(stack, values+1), SUCCESS); 
	printf("\npeek tail: %f\n", *((float*)StackPeek(stack)));
	printf("\n*********************************\n");
	StatusTestResults(StackPush(stack, values+2), SUCCESS);
	printf("\npeek tail: %f\n", *((float*)StackPeek(stack)));
	printf("\n*********************************\n");
	printf("\nPush when array is full:\n");
	printf("\nExpected status: STACK_FULL 1\n");
	StatusTestResults(StackPush(stack, values+3), STACK_FULL);
	printf("\npeek tail: %f\n", *((float*)StackPeek(stack)));
	printf("\n*********************************\n");
	StatusTestResults(StackPush(stack, values+4), STACK_FULL);
	printf("\npeek tail: %f\n", *((float*)StackPeek(stack)));
	printf("\n*********************************\n");
	

}
void FltStackPop_test(stack_t *stack)
{
	float num = 6.1;	


	printf(BLUE"\n\nStack Pop test:\n"WHITE);

	
 	
	printf("\npeek tail: %f\n", *(float*)StackPeek(stack));

	StackPop(stack);
	printf("\npeek tail: %f\n", *(float*)StackPeek(stack));
	if (num == *(float*)StackPeek(stack))
	{
		printf("\nExpected val: 6.1 : "GREEN"Success\n"WHITE );
	}
	else
	{
		printf("\nExpected val: 6.1  "RED"Failed\n"WHITE);
		
	}
	printf("\n*********************************\n");
	num = 3.1;
	StackPop(stack);
	printf("\npeek tail: %f\n", *(float*)StackPeek(stack));
	if (num == *(float*)StackPeek(stack))
	{
		printf("\nExpected val: 3.1  : "GREEN"Success\n"WHITE );
	}
	else
	{
		printf("\nExpected val: 3.1  "RED"Failed\n"WHITE);
		
	}
	printf("\n*********************************\n");

	StackPop(stack);
	printf("\npeek tail: %p\n", (void*)(float*)StackPeek(stack));
	printf("\nPopping empty stack:\n");
	StackPop(stack);
	printf("\npeek tail: %p\n", (void*)(float*)StackPeek(stack));
	StackPop(stack);
	printf("\npeek tail: %p\n", (void*)(float*)StackPeek(stack));


}


void FltStackSize_test(stack_t *stack)
{
	float array[] = {7.1,8.1};
	size_t size = 0;
	printf(BLUE"\nStack size test:\n"WHITE);
	StackPush(stack, array);	
	
	size = StackSize(stack);

	
	if (1 == size)
	{
		printf("\nsize = 1 : "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\nsize = 1:  "RED"Failed\n"WHITE );
		
	}
	printf("\n*********************************\n");
	StackPush(stack, array+1);	
	
	size = StackSize(stack);
	

	if (2 == size)
	{
		printf("\nsize = 2 : "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\nsize = 2:  "RED"Failed\n"WHITE );
		
	}
	printf("\n*********************************\n");
	StackPop(stack);
	StackPop(stack);
	size = StackSize(stack);
	

	if (0 == size)
	{
		printf("\nsize = 0 : "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\nsize = 0:  "RED"Failed\n"WHITE );
		
	}
	printf("\n*********************************\n");
}
void FltStackPeek_test(stack_t *stack)
{	
	float array[] = {7.2,8.2};
	float num = 8.2;
	printf(BLUE"\nStack Peek test:\n"WHITE);
	printf("\nempty stack:\n");
	if (NULL == StackPeek(stack))
	{
		printf("\npeek: NULL "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\npeek: NULL "RED"Failed\n"WHITE );
		
	}
	printf("\n*********************************\n");
	printf("\nnon-empty stack:\n");
	StackPush(stack, array+1);
	if (num == *(float*)StackPeek(stack))
	{
		printf("\npeek: 8.2 "GREEN"Success\n"WHITE);
	}
	else
	{
		printf("\npeek: 8.2 "RED"Failed\n"WHITE );
		
	}
	printf("\n*********************************\n");



}
