/**********************************************************************;
* Project           : Data Structures
*
* Program name      : queue.c
*
* Author            : Michelle Gelfand
*
* Date created      : 19.06.19
*
* Purpose           : This program provides the user with a
*					  queue structure, and operations to store, 
*					  edit and access data in it.
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 22/06/2019       	  Michelle Gelfand           Amitay Nadav 														  
*******************************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "queue.h"
#include "singly_list.h"

struct queue
{
	sl_node_t *front;
	sl_node_t *rear;
};

/*****************************************************************************/
queue_t *QCreate()
{
	queue_t *new_queue = (queue_t*)malloc(sizeof(queue_t));

	if ( NULL != new_queue )
	{
		sl_node_t *dummy_rear  = SListCreateNode((void*)0xDEADBEEF, NULL);
		sl_node_t *dummy_front = SListCreateNode((void*)0xDEADBEEF, dummy_rear);

		if ( (NULL != dummy_rear) && (NULL != dummy_front) )
		{
			new_queue->rear  = dummy_rear;
			new_queue->front = dummy_front;
		}
		else
		{
			SListFree(dummy_rear);
			dummy_rear = NULL;

			SListFree(dummy_front);
			dummy_front = NULL;

			free(new_queue);
			new_queue = NULL;
		}
	}

	return new_queue;
}
/*****************************************************************************/
void QDestroy(queue_t *queue)
{
	assert(queue);	
	
	SListFree(queue->front);

	queue->rear = NULL;
	queue->front = NULL;

	free(queue);
	queue = NULL;
}
/*****************************************************************************/
q_status_t QEnqueue(queue_t *queue, void *data)
{
	q_status_t status = Q_ALLOCATION_FAIL;
	sl_node_t *new_node = NULL;

	assert(queue);

	/*create new node*/
	new_node = SListCreateNode(data, NULL);

	if ( NULL != new_node )
	{
		/*insert node before  rear*/ 
		SListInsertBefore(queue->rear, new_node);

		/*rear now sitting on new_node, move forward back to dummy*/
		queue->rear = (queue->rear)->next;
		
		status = Q_SUCCESS;
	}

	return status;
}
/*****************************************************************************/
void QDequeue(queue_t *queue)
{
	assert(queue);

	if (!QIsEmpty(queue))
	{
		SListFree( SListRemoveAfter(queue->front) );
	}
}
/*****************************************************************************/
void *QPeek(const queue_t *queue)
{
	void *peeked_data = NULL; 

	assert(queue);

	if (!QIsEmpty(queue))
	{
		peeked_data = ((queue->front)->next)->data;
	}

	return peeked_data;
}
/*****************************************************************************/
int QIsEmpty(const queue_t *queue)
{
	assert(queue);

	return ( (queue->front)->next == queue->rear );
}
/******************************************************************************/
size_t QSize(const queue_t *queue)
{
	assert(queue);

	/*minus 2 dummies*/
	return ( SListCount(queue->front) - 2 );
}
/*****************************************************************************/
void QAppend (queue_t *src, queue_t *dest)
{
	sl_node_t *src_second_element = src->front->next->next;

	/*insert first src element before dest rear dummy*/
	/*func swaps dummy node with first element in src*/
	SListInsertBefore(dest->rear, src->front->next);

	/*dest is first element, dest next is dummy*/
	dest->rear->next = src_second_element;

	dest->rear = src->rear;

	src->rear = src->front->next;

	QDestroy(src);

}

