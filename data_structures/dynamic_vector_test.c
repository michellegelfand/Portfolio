/**********************************************************************;
* Project           : Data Structures
*
* Program name      : bit_array.c
*
* Author            : Michelle Gelfand
*
* Date created      : 04.06.19
*
* Purpose           : This program provides the user with a dynamic array
					  and operators to store and access data within it				  
*
* Review Status		: Approved
*
* Date Approved        Author			          Reviewer 
* 08.06.19		       Michelle Gelfand           Doron Weitzman   *														  
**********************************************************************/
#include "dynamic_vector.h"
#include <stdio.h> /*printf*/

dynamic_vector_t* _CreateVector_Test(size_t type_size, size_t init_capacity);
void _DynamicVectorDestroy_Test(dynamic_vector_t* vector);
void _DynamicVectorPushBack_Test(dynamic_vector_t* vector, void* value);
void _DynamicVectorPopBack_Test(dynamic_vector_t *vector);
void* _DynamicVectorGetElementAddress_Test(dynamic_vector_t* vector, int index);
void _DynamicVectorIsEmpty_Test(dynamic_vector_t *vector);
void _DynamicVectorCount_Test(dynamic_vector_t *vector);

int main()
{
	int value[] = {4, 5, 9};
	dynamic_vector_t* vector = _CreateVector_Test(4, 3);
	dynamic_vector_t* vector1 = _CreateVector_Test(4, 3);


	 _DynamicVectorPushBack_Test(vector, &value[1]);
	 _DynamicVectorPushBack_Test(vector, &value[2]);
	 _DynamicVectorPushBack_Test(vector, &value[2]);
	 _DynamicVectorPushBack_Test(vector, &value[1]);
	 _DynamicVectorPushBack_Test(vector, &value[2]);
	 _DynamicVectorPushBack_Test(vector, &value[2]);
	 _DynamicVectorPushBack_Test(vector, &value[2]);
	 _DynamicVectorPushBack_Test(vector, &value[2]);
	 _DynamicVectorPushBack_Test(vector, &value[2]);

	_DynamicVectorGetElementAddress_Test(vector, 4);
	_DynamicVectorGetElementAddress_Test(vector, 40);
	
	
	_DynamicVectorIsEmpty_Test(vector);
	_DynamicVectorIsEmpty_Test(vector1);
	_DynamicVectorCount_Test(vector);
	_DynamicVectorCount_Test(vector1);

	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	_DynamicVectorPopBack_Test(vector);
	


	_DynamicVectorDestroy_Test(vector);
	_DynamicVectorDestroy_Test(vector1);

	 return 0;
}


dynamic_vector_t* _CreateVector_Test(size_t type_size, size_t init_capacity)
{
	size_t * to_print;
	void* test = 0;
	printf("\n****************************************************\n");
	
	printf(" \n\nCreate Dynamic Vector Test:\n\n");
	test=DynamicVectorCreate(type_size, init_capacity);
	
	printf("\n\ntype size: %lu\n", *((size_t*)(test)));
	to_print = test ;
	++to_print;

	printf("capacity: %lu\n", *((size_t*)to_print));

	++to_print;

	printf("element count: %lu\n", *((size_t*)to_print));
	printf("data: %d\n", *((int*)to_print));
	printf("\nCombine this test with valgrind\n");
	return test;
}
void _DynamicVectorDestroy_Test(dynamic_vector_t* vector)
{
	
	 
	
	printf("\n****************************************************\n");
	printf("\n\nDestroy Dynamic Vector Test:\n\n");

	

	DynamicVectorDestroy(vector);
	printf("\nCombine this test with valgrind\n");


}
void _DynamicVectorPushBack_Test(dynamic_vector_t* vector, void* value)
{
	int* val =(int*)value; 
	status_t result = 0;
	printf("\n****************************************************\n");
	
	printf("\n\nPush Back test:\n\n");

	printf("\n\nAfter push\n");
	(1 ==  result ) ? printf("(ALLOCATION_FAIL)\n") : printf("(SUCCESS)\n");
	result = DynamicVectorPushBack(vector, val);
	
	

}


void _DynamicVectorPopBack_Test(dynamic_vector_t* vector)
{
	printf("\n****************************************************\n");
	printf("\nVector Pop Test:\n");	
		
	(SUCCESS == DynamicVectorPopBack(vector)) ?
	printf("\nSuccess\n") :  printf("\nSuccess\n");


}
void* _DynamicVectorGetElementAddress_Test(dynamic_vector_t* vector, int index)
{
	void* element = DynamicVectorGetElementAddress(vector, index);
	printf("\n****************************************************\n");
	printf("\n\nElement Address Test:\n\n");
	if (NULL != element)
	{
		printf("\n\nelement drawn is element %d: %d\n" ,index, *(int*)element); 
	}
	else
	{
		printf("\nelement is out of bounds!\n"); 
	}
	return element;
}
void _DynamicVectorIsEmpty_Test(dynamic_vector_t *vector)
{
	printf("\n****************************************************\n");
	printf("\nvector IsEmpty test:\n");
	(1 == DynamicVectorIsEmpty(vector)) ? 
		  printf("\nEmpty!\n"): printf("\nNot Empty!\n");

}
void _DynamicVectorCount_Test(dynamic_vector_t *vector)
{
	printf("\n****************************************************\n");
	printf("\nVector Count test:\n");
	printf("\n%lu\n",DynamicVectorCount(vector));
	
}
	
