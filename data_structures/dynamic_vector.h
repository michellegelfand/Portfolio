/**********************************************************************;
* Project           : Data Structures
*
* Program name      : bit_array.c
*
* Author            : Michelle Gelfand
*
* Date created      : 04.06.19
*
* Version           : 1.0      
*
* Purpose           : This program provides the user with a dynamic array
					  and operators to store and access data within it				  
*
* Review Status		: Approved
*
* Date Approved        Author			          Reviewer 
* 08.06.19 		       Michelle Gelfand           Doron Weitzman   *														  
**********************************************************************/

#ifndef __DYNAMIC_VECTOR_H__
#define __DYNAMIC_VECTOR_H__

#include <stddef.h> /* size_t */



/*
 *	version: 1.1
 */


typedef struct dynamic_vector dynamic_vector_t;

typedef enum status
{	
	SUCCESS,
	ALLOCATION_FAIL,
	EMPTY_VECTOR
} status_t;


/*
 *	Create Dynamic Vector: 
 * 	args: 
 *		type_size - size of one element in the vector
 *		init_capacity - max allowed elements in the vector
 *	return: 
 *		pointer to vector or NULL if creation failed
 */
dynamic_vector_t *DynamicVectorCreate(size_t type_size, size_t init_capacity);


/*
 *	Destroy Dynamic Vector: frees all allocated memory for this vector 
 * 	args:
 *		*vector - pointer to existed vector
 *	return: none
 */	
void DynamicVectorDestroy(dynamic_vector_t *vector);


/*
 *	Dynamic Vector Get Element Address: 
 * 	args: 
 *		vector - pointer to existing vector
 *		element_index - a place where element is stored in vector
 *	return: 
 *		pointer to an element by index or NULL if index out of range
 */
void* DynamicVectorGetElementAddress(dynamic_vector_t *vector, size_t element_index);


/*
 *	Dynamic Vector Push Back: adds element to the end of a vector 
 * 	args:
 *		vector - pointer to existing vector
 		value - pointer to value to store in a vector element
 *	return: 
 *		SUCCESS or
 *		ALLOCATION_FAIL
 */
 status_t DynamicVectorPushBack(dynamic_vector_t *vector, void *value);


/*
 *	Dynamic Vector Pop Back: removes last element 
 * 	args: 
 *		vector - pointer to existing vector
 *	return:
 *		SUCCESS,
 *		ALLOCATION_FAIL or
 *		EMPTY_VECTOR
 */
status_t DynamicVectorPopBack(dynamic_vector_t *vector);


/*
 *	Dynamic Vector Is Empty: checks there are NO elements in a vector 
 * 	args: 
 *		vector - pointer to existed vector
 *	return: 
 *		1 if empty, otherwise return 0
 */
int DynamicVectorIsEmpty(dynamic_vector_t *vector);


/*
 *	Dynamic Vector Count:  
 * 	args: 
 *		vector - pointer to existed vector
 *	return: 
 *		 current number of elements in the vector
 */
size_t DynamicVectorCount(dynamic_vector_t *vector);


#endif /* __DYNAMIC_VECTOR_H__ */
