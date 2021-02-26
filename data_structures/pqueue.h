/******************************************************************************/
/*	@File:		pqueue.h													  */
/*	@Created:	26.06.19 													  */
/*  @Version: 	1.4  														  */
/*	@Modified:	30.06.19													  */
/*	@Author:																  */
/*																			  */
/*	@Brief:		Pqueue Functions	:			PQueueCreate 				  */
/*										   		PQueueDestroy				  */
/*							  				 	PQueueEnqueue				  */
/*							  				 	PQueueDequeue				  */
/*							  				 	PQueuePeek					  */
/*							  				 	PQueueSize					  */
/*							  				 	PQueueIsEmpty				  */
/*							  				 	PQueueClear					  */
/*							  				 	PQueueRemove				  */
/*                                                                            */
/******************************************************************************/

/* 
				v 1.4   - creat function signature is now : "IsBefore" and
						  "not Compare"
						  
						- note : if element is of higher priority, 
						  he will be inserted closer to the head of the queue!
		

				v.1.3
						- fixed arg names to pqueue from queue
						- PQSize returns size_t and not size_t*
						- struct name element changed from p_queue to queue

*/



#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h>


typedef enum status
{
	PQ_SUCCESS ,
	PQ_ALLOCATION_FAIL

}pq_status_t;

typedef struct p_queue p_queue_t;

/*

struct p_queue
{
	sort_list_t *queue;
	
};

*/

/* search for data in priority queue using param */
typedef int (*pq_ismatch_t)(const void *data1, void *param,
														     const void *data2);
									
/* used to insert data to the correct place in the queue */
typedef int (*pq_is_before_t)(const void *queue_data, const void *user_data);

/*------------------------------------------------------------------------------

PQueueCreate - Creates a new priority queue. 
                                             
ARGS: 
IsBefore - Function that determines the sort order of the priority queue
		   this function returns: 
		   				 1 if user_data is sorted before the queue data
						 0 if user_data is sorted after the queue data					
						
note : if element is of higher priority, he will be inserted closer to the head
		of the queue!
		
		
RETURNS: 	Success: pointer to priority queue 
			Failure: NULL   		  

*/

p_queue_t *PQCreate(pq_is_before_t IsBefore);
 
 
/*------------------------------------------------------------------------------

PQDestroy - Frees all allocated memory to queue. 
                                        
ARGS: 
pqueue - pointer to a priority queue			   
 
RETURNS: void                                                                

*/ 

void PQDestroy(p_queue_t *pqueue);

/*------------------------------------------------------------------------------

PQEnqueue - adds element to the rear of the queue

ARGS:
	pqueue- pointer to priority queue
	data - pointer to data to enqueue
 
RETURN: SUCCESS or FAILED_ALLOCATION

*/

pq_status_t PQEnqueue(p_queue_t *queue, void *data);


/*------------------------------------------------------------------------------

PQDequeue: removes the front element from the  queue.

AGS: 
	pqueue - pointer to priority queue

*/

void PQDequeue(p_queue_t *pqueue); 

/*------------------------------------------------------------------------------

PQPeek: peeks on the first element of the queue.

AGS: 
	pqueue - pointer to priority queue

RETURNS : pointer to peeked data
		  NULL if empty

*/

void *PQPeek(p_queue_t *pqueue); 

/*------------------------------------------------------------------------------

PQSize: returns the size of the queue.

AGS: 
	pqueue - pointer to priority  queue

RETURNS : the number of elements currently enqueued

*/

size_t PQSize(p_queue_t *pqueue); 

/*------------------------------------------------------------------------------

PQIsEmpty: checks if the queue is empty.

AGS: 
	queue - pointer to priority queue

RETURNS : 1 if the queue is empty
		  0 if not

*/

int PQIsEmpty (p_queue_t *pqueue); 

/*------------------------------------------------------------------------------

PQClear: removes all the elements from the turn.

AGS: 
	queue - pointer to priority queue
	

*/

void PQClear(p_queue_t *pqueue); 

/*------------------------------------------------------------------------------

PQRemove: removes a single element from the queue.

AGS: 
	pqueue   - pointer to priority queue
	ISMatch - function used to compare and search the queue
	param   - data comparison condition  
	data -  data comparison parameter

RETURNS : pointer to removed data
		  NULL if fail

*/

void *PQRemove(p_queue_t *pqueue, pq_ismatch_t IsMatch, void *param, void* data); 

/*----------------------------------------------------------------------------*/

#endif /* __PQUEUE_H__ */


