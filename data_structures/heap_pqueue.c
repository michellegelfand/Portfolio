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
*					  self sorting priority queue structure, 
*					  and operations to store, 
*					  edit and access data in it.
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 06/07/2019       	  Michelle Gelfand           Doron W. 														  
*******************************************************************/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc, free*/

#include "heap.h"
#include "pqueue.h" 

struct p_queue
{
	heap_t *heap;
	
};


typedef struct wrapper
{
	pq_is_before_t func;
}wrapper_t;


int compare(const void *heap_data, const void *user_data, wrapper_t param)
{
	if(param.func(heap_data, user_data))
	{
		return -1;
	}
	else if(param.func(user_data, heap_data))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************/
p_queue_t *PQCreate(pq_is_before_t is_before)
{
	p_queue_t *new_pq = NULL;
	wrapper_t wrapper = {0};

	assert(is_before);

	wrapper.func = is_before;

	new_pq = (p_queue_t*)malloc(sizeof(p_queue_t));
	
	if(new_pq)
	{
		new_pq->heap= HeapCreate((heap_compare_t)compare, *(void**)&wrapper);
		
		if( NULL == new_pq->heap)
		{
			free(new_pq); 
			new_pq = NULL;
		}	
	}
	return new_pq;	
}
/*--------------------------------------------------------------------------*/
void PQDestroy(p_queue_t *pqueue)
{
	assert(pqueue);

	HeapDestroy(pqueue->heap);

	free(pqueue);
	
	pqueue = NULL;
}
/*---------------------------------------------------------------------------*/
pq_status_t PQEnqueue(p_queue_t *queue, void *data)
{
	pq_status_t status  = PQ_SUCCESS;

	assert(queue);

	if( HEAP_FAIL == HeapPush(queue->heap, data))
	{
		status = PQ_ALLOCATION_FAIL;
	}

	return status;
}
/*---------------------------------------------------------------------------*/


void PQDequeue(p_queue_t *pqueue)
{
	assert(pqueue);

	/*sort list pop front checks if(!PQIsEmpty(pqueue)*/
	HeapPop(pqueue->heap);
}

/*-------------------------------------------------------------------------*/

void *PQPeek(p_queue_t *pqueue)
{
	void *peek_data = NULL;

	assert(pqueue); 

	if( !PQIsEmpty(pqueue) )
	{
		peek_data = HeapPeek(pqueue->heap);
	}

	return peek_data;
}

/*---------------------------------------------------------------------------*/

size_t PQSize(p_queue_t *pqueue)
{
	assert(pqueue);

	return HeapSize(pqueue->heap);	
}

/*---------------------------------------------------------------------------*/
int PQIsEmpty (p_queue_t *pqueue)
{
	assert(pqueue);

	return HeapIsEmpty(pqueue->heap);
}

/*---------------------------------------------------------------------------*/
void PQClear(p_queue_t *pqueue)
{
	assert(pqueue);

	/*keep popping front til empty*/
	while ( !HeapIsEmpty(pqueue->heap) )
	{
		HeapPop(pqueue->heap);
	}
}

/*--------------------------------------------------------------------------*/
void *PQRemove(p_queue_t *pqueue, pq_ismatch_t IsMatch, void *param, void* data)
{
	void *remove = NULL;

	assert(pqueue);
	assert(IsMatch);

	remove = HeapRemove(pqueue->heap, data, IsMatch, param); 

	return remove;
}



