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
* Version           : 1.0
*
* Date Approved       Author	 	             Reviewer 
* 12/06/2019       	  Michelle Gelfand           Waed Bader *														  
**********************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

/*
 *	version: 1.0
 *	date: 10/06/2019 time: 12:00 
 */

typedef enum status
{
    SUCCESS,
    STACK_FULL
        
} status_t;

/*
 
struct stack
{	
	void *stack_tail;
	void *stack_head; 
    size_t element_size; 
    size_t capacity;
};
 
*/
typedef struct stack stack_t;

/*
 *	Create Stack: 
 * 	args: 
 *		element_size - size of one element in the stack
 *		capacity - max allowed elements in the stack
 					   (capacity must be greater than 0)
 *	return: 
 *		pointer to stack or NULL if creation failed
 */
stack_t *StackCreate(size_t element_size, size_t capacity);

/*
 *	Destroy Stack: frees all allocated memory for this stack 
 * 	args:
 *		*stack - pointer to existed stack
 *	return: none
 */	
void StackDestroy(stack_t *stack);

/*
 *	Stack Peek: 
 * 	args: 
 *		stack - pointer to the existed stack
 *	return: 
 *		pointer to the top value in the stack or NULL if empty
 */
void* StackPeek(const stack_t *stack);

/*
 *	Stack Push: adds element to the top of the stack 
 * 	args:
 *		stack - pointer to existing stack
 		value - pointer to value to push into the top of the stack
 *	return: 
 *		SUCCESS or
 *		STACK_FULL
 */
 status_t StackPush(stack_t *stack, void *value);

/*
 *	Stack Pop: removes the top element from the stack, if exists.
 * 	args: 
 *		stack - pointer to existing stack
 */
void StackPop(stack_t *stack); 

/*
 *	Stack Size: current number of elements in the stack
 * 	args: 
 *		stack - pointer to existed stack
 *	return: 
 *		 current number of elements in the stack
 */
size_t StackSize(const stack_t *stack);

#endif /* __STACK_H__ */
