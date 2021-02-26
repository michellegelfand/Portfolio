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
* Version           : 1.3
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 27/06/2019       	  Michelle Gelfand           Waed S. 														  
*******************************************************************/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc, free*/

#include "sorted_list.h"
#include "pqueue.h" 

struct p_queue
{
	sort_list_t *p_queue;
	
};
/****************************************************************************/
p_queue_t *PQCreate(pq_is_before_t is_before)
{
	p_queue_t *new_pq = NULL;

	assert(is_before);

	new_pq = (p_queue_t*)malloc(sizeof(p_queue_t));
	
	if(new_pq)
	{
		new_pq->p_queue = SortListCreate(is_before);
		
		if( NULL == new_pq->p_queue)
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

	SortListDestroy(pqueue->p_queue);

	free(pqueue);
	
	pqueue = NULL;
}
/*---------------------------------------------------------------------------*/
pq_status_t PQEnqueue(p_queue_t *queue, void *data)
{
	pq_status_t status  = PQ_SUCCESS;
	
	sort_list_iter_t inserted_node = {0};

	assert(queue);

	inserted_node = SortListInsert(queue->p_queue, data);

	if( SortListIsSameIterator(SortListEnd(queue->p_queue), inserted_node ))
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
	SortListPopFront(pqueue->p_queue);
}

/*-------------------------------------------------------------------------*/

void *PQPeek(p_queue_t *pqueue)
{
	void *peek_data = NULL;

	assert(pqueue); 

	if(!PQIsEmpty(pqueue))
	{
		peek_data = SortListGetData(SortListBegin(pqueue->p_queue));
	}

	return peek_data;
}

/*---------------------------------------------------------------------------*/

size_t PQSize(p_queue_t *pqueue)
{
	assert(pqueue);

	return SortListCount(pqueue->p_queue);	
}

/*---------------------------------------------------------------------------*/
int PQIsEmpty (p_queue_t *pqueue)
{
	assert(pqueue);

	return SortListIsEmpty(pqueue->p_queue);
}

/*---------------------------------------------------------------------------*/
void PQClear(p_queue_t *pqueue)
{
	assert(pqueue);

	/*keep popping front til empty*/
	while ( !PQIsEmpty(pqueue) )
	{
		PQDequeue(pqueue);
	}
}

/*--------------------------------------------------------------------------*/
void *PQRemove(p_queue_t *pqueue, pq_ismatch_t IsMatch, void *param, void* data)
{
	void *data_to_remove = NULL;
	sort_list_iter_t node_to_remove = {0};

	assert(pqueue);
	assert(IsMatch);

	node_to_remove = SortListFind(SortListBegin(pqueue->p_queue),
	SortListEnd(pqueue->p_queue),IsMatch, param, data);

	if( !SortListIsSameIterator(node_to_remove, SortListEnd(pqueue->p_queue)) )
	{
		data_to_remove = SortListGetData(node_to_remove);
		SortListRemove(node_to_remove);
	}

	return data_to_remove;
}


