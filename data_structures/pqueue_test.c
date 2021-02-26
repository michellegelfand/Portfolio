/**********************************************************************;
* Project           : Data Structures
*
* Program name      : pqueue.c
*
* Author            : Michelle Gelfand
*
* Date created      : 27.06.19
*
* Purpose           : This program provides the user with a
*					  self sorting priority queue structure, and operations to store, 
*					  edit and access data in it.
*
* Version           : 1.3
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 27/06/2019       	  Michelle Gelfand           Waed S. 														  
*******************************************************************/
#include <stdio.h>/*printf*/

#include "pqueue.h"

int PQCreate_test();
int PQDestroy_test();
int PQEnqueue_test();
int PQDequeue_test(); 
int PQPeek_test(); 
int PQSize_test(); 
int PQIsEmpty_test(); 
int PQClear_test(); 
int PQRemove_test(); 

int Compare_test(const void *queue_data, const void *user_data);
int IsMatch(const void *data1, void *param, const void *data2);

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

int main()
{
	int test_result = 0;

	test_result |= PQCreate_test();
	test_result |= PQDestroy_test();
	test_result |= PQEnqueue_test();
	test_result |= PQDequeue_test();
	test_result |= PQIsEmpty_test();
	test_result |= PQSize_test();
	test_result |= PQPeek_test();
	test_result |= PQRemove_test(); 
	test_result |= PQClear_test(); 

	(0 == test_result)? printf(KCYN"\n\nALL TESTS PASSED\n\n"WHITE) :
						printf(RED"\n\nFailed on some tests\n\n"WHITE);
	return 0;
}
/*************************stub user funcs*************************************/
int Compare_test(const void *queue_data, const void *user_data)
{
	return !!(*(int*)queue_data == *(int*)user_data);
}
int IsMatch(const void *data1, void *param, const void *data2)
{
	(void)param;
	return !!(*(int*)data1 == *(int*)data2);
}
/*****************************************************************************/
int PQCreate_test()
{
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nCreate Priority queue Test:\n"WHITE);

	if (new_queue)
	{
		printf(GREEN"\nSuccesfully created priority queue\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to create priority queue\n"WHITE);

		test_result+=1;
	}

	printf(YELLOW"\nCombine this test with valgrind to assure"\
				 " no memory leaks\n");	
	
	PQDestroy(new_queue);

	return test_result;
}
int PQDestroy_test()
{
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);
	PQDestroy(new_queue);

	printf(KCYN"\n\nDestroy Priority queue Test:\n"WHITE);

	if (new_queue)
	{
		printf(GREEN"\nSuccesfully destroyed priority queue\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to destroy priority queue\n"WHITE);

		test_result+=1;
	}

	printf(YELLOW"\nCombine this test with valgrind to assure"\
				 " no memory leaks\n");	
	
	return test_result;
}

int PQEnqueue_test()
{
	int data[] = {1,2,3};
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nEnqueue Test:\n"WHITE);

	PQEnqueue(new_queue, data);

	if(1 == PQSize(new_queue))
	{
		printf(GREEN"\nenqueue succesful\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to enqueue\n"WHITE);

		test_result+=1;
	}
	PQEnqueue(new_queue, data);

	if(2 == PQSize(new_queue))
	{
		printf(GREEN"\nenqueue succesful\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to enqueue\n"WHITE);

		test_result+=1;
	}
	PQDestroy(new_queue);
	return test_result;
}
int PQDequeue_test()
{
	int data[] = {1,2,3};
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nDequeue Test:\n"WHITE);

	PQEnqueue(new_queue, data);
	PQEnqueue(new_queue, data);

	PQDequeue(new_queue);

	if(1 == PQSize(new_queue))
	{
		printf(GREEN"\ndequeue succesful\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to dequeue\n"WHITE);

		test_result+=1;
	}
	PQDestroy(new_queue);
	return test_result;
}
int PQIsEmpty_test()
{
	int data[] = {1,2,3};
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nIs Empty Test:\n"WHITE);

	if(1 == PQIsEmpty(new_queue))
	{
		printf(GREEN"\nsuccesfully returned is empty\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return is empty\n"WHITE);

		test_result+=1;
	}

	PQEnqueue(new_queue, data);
	PQEnqueue(new_queue, data);

	if(0 == PQIsEmpty(new_queue))
	{
		printf(GREEN"\nsuccesfully returned not empty\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return not empty\n"WHITE);

		test_result+=1;
	}
	PQDestroy(new_queue);
	return test_result;
}
int PQSize_test()
{
	int data[] = {1,2,3};
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nSize Test:\n"WHITE);

	PQEnqueue(new_queue, data);
	PQEnqueue(new_queue, data);

	if(2 == PQSize(new_queue))
	{
		printf(GREEN"\nsuccesfully returned size\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return size\n"WHITE);

		test_result+=1;
	}

	PQDestroy(new_queue);
	return test_result;	
}
int PQPeek_test()
{
	int data[] = {1,2,3};
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nPeak Test:\n"WHITE);

	PQEnqueue(new_queue, data);

	if(data == PQPeek(new_queue))
	{
		printf(GREEN"\nsuccesfully peeked\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to peek\n"WHITE);

		test_result+=1;
	}

	PQDestroy(new_queue);
	return test_result;	
}

int PQRemove_test()
{
	int data[] = {1,5,3};
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nRemove Test:\n"WHITE);

	PQEnqueue(new_queue, data);
	PQEnqueue(new_queue, data+1);


	if( 1 == *(int*)PQRemove(new_queue, IsMatch, NULL,  data)&& 
					   (1 == PQSize(new_queue)))
	{
		printf(GREEN"\nsuccesfully removed\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to remove\n"WHITE);

		test_result+=1;
	}

	PQDestroy(new_queue);
	return test_result;	
} 
int PQClear_test()
{
	int data[] = {1,5,3};
	int test_result = 0;
	p_queue_t *new_queue = PQCreate(Compare_test);

	printf(KCYN"\n\nClear Test:\n"WHITE);

	PQEnqueue(new_queue, data);
	PQEnqueue(new_queue, data+1);
	PQEnqueue(new_queue, data+2);
	/* PQEnqueue(new_queue, data+3); */

	PQClear(new_queue);

	if( PQIsEmpty(new_queue))
	{
		printf(GREEN"\nsuccesfully cleared\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to clear\n"WHITE);

		test_result+=1;
	}

	PQDestroy(new_queue);
	return test_result;	
}
