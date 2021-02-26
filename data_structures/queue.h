/******************************************************************************/
/*	@File:		queue.h												  		  */
/*	@Author: 	Michelle Gelfand									          */
/*	@Created:	19.06.19 													  */
/*  @Version: 	1.0  														  */
/*	@Modified:	-															  */
/*	@Reviewer:	Amitay Nadav										          */
/*																			  */
/*	@Brief:		Queue Functions:			QCreate							  */
/*											QDestroy						  */
/*											QPeek							  */
/*											QEnqueue						  */
/*											QDequeue						  */
/*											QSize							  */
/*											QIsEmpty						  */
/*											QAppend							  */
/******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

#include "singly_list.h"

typedef enum status
{
	Q_SUCCESS ,
	Q_ALLOCATION_FAIL

}q_status_t;

/**************************************************/
typedef struct queue queue_t;

/*****************************************************
 *	Create Queue - creates a queue data structure
 	args:
 		NONE
 
 *	return:
 		SUCCESS - pointer to the newly created queue
 		FAIL 	- NULL
 */
queue_t *QCreate();

/****************************************************
 *	Destroy Queue: frees all allocated memory for this queue 
 * 	args:
 *		queue - pointer to existing queue
 */	

void QDestroy(queue_t *queue);

/***************************************************
 *  Queue Peek: 
 * 	args: 
 *		queue - pointer to the existing queue
 *	return: 
 *			SUCCESS 	 : pointer to data at the front of queue.
 *			EMPTY QUEUE  : NULL;
 *
 */

void *QPeek(const queue_t *queue);

/***************************************************
 *	Queue Enqueue: adds element to the rear of the queue
 * 	args:
 *		queue- pointer to existing queue
 *		data - pointer to data to enqueue
 
 *	return: 
 *		SUCCESS 
 		FAILED_ALLOCATION
 */

 q_status_t QEnqueue(queue_t *queue, void *data);

/**************************************************
 *	QDequeue: removes the front element from the queue.
 * 	args: 
 *		queue - pointer to existing queue
 *	
 *	
 */ 

void QDequeue(queue_t *queue); 

/*******************************************************
 *	QSize: current number of elements in the queue
 * 	args: 
 *		queue - pointer to existing queue
 *	return: 
 *			 Element count in queue
 */			

size_t QSize(const queue_t *queue);

/****************************************************
 * QIsEmpty : checks whether queue is empty.
 * args:
 *		queue - pointer to existing queue.
 * return:
 *			1 if empty
 * 			0 if not empty
 */ 

int QIsEmpty(const queue_t *queue);

/*************************************************
*
* QAppend : Appends src to the rear of dest 
* args:
*		src - The queue to transfer
*		dest -The target queue
*
*/
void QAppend(queue_t *src, queue_t *dest);


#endif /* __QUEUE_H__ */
