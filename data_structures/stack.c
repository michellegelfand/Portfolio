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

#include <stdlib.h>/*malloc*/
#include <string.h>/*memcpy*/
#include <assert.h>/*assert*/

#include "stack.h"

struct stack                         
{	
	void *tail; 
    size_t element_size; 
    size_t capacity;
	char head[1]; 
};

stack_t *StackCreate(size_t element_size, size_t capacity)
{
	size_t memory_size = 
			sizeof(stack_t) - (sizeof(size_t))
						+ (element_size * capacity);

    stack_t *new_stack = (stack_t*) calloc(memory_size, 1);

    if( new_stack )
    {
        new_stack->element_size = element_size;
        new_stack->capacity = capacity;
		new_stack->tail = NULL;
    }

    return new_stack;

}

void StackDestroy(stack_t *stack)
{
	stack->tail = NULL;
	free(stack);
	stack = NULL;
}

void* StackPeek(const stack_t *stack)
{
	return stack->tail;
}


status_t StackPush(stack_t *stack, void *value)
{
	size_t stack_size = 0;
	status_t status = SUCCESS; 
	int is_first_push = 0;

	assert(stack);

	/*if not first push*/
	if ( NULL != stack->tail)
	{
		stack_size = (((char*)stack->tail - (char*)stack-> head)
								   /(stack->element_size))+1;	
	}
	else
	{
	    /*point tail to head*/
		stack->tail = (void*)(stack->head);
		is_first_push = 1;
	}
	/*if there is place and this is not the first push*/

	if (((stack-> capacity) > stack_size) && !(is_first_push))
	{	
		stack->tail = (void*)((char*)stack->tail+stack->element_size);
	
	}

	if (stack-> capacity > stack_size)
	{
		*((char**)&stack->tail) += stack->element_size;
		stack->tail = memcpy(stack->tail, (char*)value, stack->element_size);

	}
	else
	{
		status = STACK_FULL;
	}
	return status;
}

void StackPop(stack_t *stack)
{
	
	if (NULL != stack->tail)
	{

		if (stack->head != stack->tail)
		{
			stack->tail = (void*)((char*)stack->tail - stack->element_size );
		}
		else
		{
			stack->tail = NULL;
		}

	}
 

}

size_t StackSize(const stack_t *stack)
{
	size_t stack_size = 0;

	if ( NULL != stack->tail)
	{
		stack_size = (((char*)stack->tail - (char*)stack-> head)
							   /(stack->element_size))+1;
	} 
	
	return stack_size;
}


