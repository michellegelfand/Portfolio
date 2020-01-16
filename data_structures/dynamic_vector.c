/**********************************************************************;
* Project           : Data Structures
*
* Program name      : dynamic_vector.c
*
* Author            : Michelle Gelfand
*
* Date created      : 04.06.19
*
* Purpose           : This program provides the user with a dynamic vector
					  and operators to store and access data within it				  
*
* Review Status		: Approved+ fixed after code review:
					  change callocs to mallocs, remove memsets, add min array size
					  to save reacurring reallocs
*
* Date Approved       Author	 	             Reviewer 
* 08/06/2019       	  Michelle Gelfand           Doron Weitzman *	
							  
**********************************************************************/

#include <stdlib.h> /*calloc, realloc*/
#include <string.h> /*memset*/
#include "dynamic_vector.h"

/* order of magnitude by which to increase array when capacity reached */
#define RESIZE_FACTOR 2
/* At what capacity percentage do we decide to shrink array */
/* Currently: 4: at a quarter of capacity */
#define SHRINK_FACTOR 4

/* if not in debug mode delete all calls to print func */
#ifdef NDEBUG
	#define PrintDataArr(vector)
#else
	#include <stdio.h> /* printf */
	void PrintDataArr(dynamic_vector_t *vector);
#endif /* NDEBUG */

status_t DynamicVectorPopBack(dynamic_vector_t *vector);
void* DynamicVectorGetElementAddress
	  (dynamic_vector_t *vector, size_t element_index);
static status_t _ResizeDynamicVector(dynamic_vector_t *vector);
int DynamicVectorIsEmpty(dynamic_vector_t *vector);
size_t DynamicVectorCount(dynamic_vector_t *vector);
static status_t _ShrinkDynamicVector(dynamic_vector_t* vector);

struct dynamic_vector
{
	size_t type_size; 
	size_t capacity;
	size_t min_capacity;
	size_t element_count;
	void * data;
};

/*****************************************************************************/
dynamic_vector_t *DynamicVectorCreate(size_t type_size, size_t init_capacity)
{
	dynamic_vector_t *vector =
	(dynamic_vector_t*) malloc(sizeof(*vector));

	if( vector )
	{
		vector->type_size = type_size;
		vector->capacity = init_capacity;
		vector->min_capacity = init_capacity;
		vector->element_count = 0;
		vector->data = (void*)calloc(init_capacity, type_size);
		if( !vector->data )
		{
			free(vector);
			vector = NULL;
		}
	}

	return vector;
}

/*****************************************************************************/
void DynamicVectorDestroy(dynamic_vector_t *vector)
{
	free(vector->data);
	vector->data = NULL;

	free(vector);
	vector = NULL;
}

/*****************************************************************************/
status_t DynamicVectorPushBack(dynamic_vector_t *vector, void *value)
{
	status_t result = SUCCESS;

	/*if max num of elements reached for this capacity*/
	if (vector->capacity == vector->element_count) 
	{
		/*send to resize func to alloc more space*/
		result = _ResizeDynamicVector(vector);
	}

	/*if theres room for push*/
	if( result != ALLOCATION_FAIL )	
	{ 
		/*copy value to back of array*/
		memcpy((char*)vector->data+ (vector->type_size)*(vector->element_count), 
			   						 value, vector->type_size);
		vector->element_count += 1ul;
	}

	return result;
}

/*****************************************************************************/
static status_t _ResizeDynamicVector(dynamic_vector_t* vector)
{
	/*allocate dynamic array to double its' size*/
	/*realloc, as well as check it did not return NULL*/
	status_t result = SUCCESS;
	size_t realloc_size = (vector->type_size * vector->capacity)* RESIZE_FACTOR;
	
	vector->data = (void*)realloc(vector->data, realloc_size);

	if (NULL ==	vector->data)
	{
		result =  ALLOCATION_FAIL;		
	}

	vector->capacity *= RESIZE_FACTOR;
	
	return result;
}

/*****************************************************************************/
status_t DynamicVectorPopBack(dynamic_vector_t *vector)
{
	status_t result = SUCCESS;
	void* allocate_here =(char*)(vector->data) + 
		  				 (vector->type_size * (vector->element_count - 1UL));
	
	if(0 == vector->element_count)
	{
		result = EMPTY_VECTOR;
	}
	
	if(result != EMPTY_VECTOR)
	{	
		memset(allocate_here,0, vector->type_size );
		vector->element_count -= 1UL;

		/*if element cunt is quarter or less of capacity*/
		if (vector && vector->capacity >= ((vector->element_count) *SHRINK_FACTOR)
			&&
		(vector->capacity > vector->min_capacity))
		{	
			/*Call shrink func + check status after return*/
			result = _ShrinkDynamicVector(vector);
		}

		if (result != ALLOCATION_FAIL)
		{
			/* PrintDataArr(vector); */
		}
	}
		
	return result;
}

/*****************************************************************************/
static status_t _ShrinkDynamicVector(dynamic_vector_t* vector)
{
	/*allocate dynamic array to half its' size*/
	/*realloc, as well as check it did not return NULL*/
	status_t result = SUCCESS;
	size_t realloc_size= vector->type_size * (vector->capacity/RESIZE_FACTOR);

	vector->data = (void*)realloc(vector->data, realloc_size);

	if (NULL ==	vector->data)
	{
		result =  ALLOCATION_FAIL;		
	}

	vector->capacity =realloc_size/vector->type_size;
	
	return result;
}

/*****************************************************************************/
void* DynamicVectorGetElementAddress
	 (dynamic_vector_t *vector, size_t element_index)
{
	void* element_address = 0;

	/*check if element # requested is out of bounds*/
	if ( vector-> element_count <= element_index)
 	{
		element_address = NULL;
	}
	/*else- if in bounds*/
	else
	{	
		element_address = ((char*)vector->data + 
						  (element_index * vector->type_size));
	}
	
	return element_address;
}

/*****************************************************************************/

/*Only in DEBUG MODE*/
#ifndef NDEBUG

/*this func is called from within functions in testing phase*/
void PrintDataArr(dynamic_vector_t *vector)
{
	size_t i = 0;

	printf("\n");

	for(i = 0; i < vector->element_count; ++i)
	{
		printf("[%.2lu] ",i);
	}

	printf("\n");

	for(i = 0; i < vector->element_count; ++i)
	{
		printf(" %.2d  ",*((char*)vector->data + (i*(vector->type_size))) );
	}
}
#endif /*NDEBUG*/

/*****************************************************************************/
int DynamicVectorIsEmpty(dynamic_vector_t *vector)
{
	return (0 == vector->element_count) ? 1 : 0; 
}

/*****************************************************************************/
size_t DynamicVectorCount(dynamic_vector_t *vector)
{
	return vector->element_count;
}

