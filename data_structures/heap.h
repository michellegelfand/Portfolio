#ifndef __HEAP_H__
#define __HEAP_H__
/*******************************************************************************
 *									::HEADER::
 *
 *						Project Name:   Data Stractures
 *						Product Name:   Heap
 *						version:		1.3
 *
 ******************************************************************************/

/* Change log */
/* 1.1 - added param to remove func */
/* 1.2 - HeapRemove return void*  */
/* 1.3 - added param to compare func and Create*/

#include <stddef.h> /* size_t */

/*
	struct heap
	{
		heap_compare func;
		dynamic_vector_t *vector;
		void *param;
	};
*/

typedef struct heap heap_t;

/**
 * returns
 * 			positive - heap_data bigger - swap
 * 			0        - equals
 * 		   negative  - heap_data smaller
 */
typedef int (*heap_compare_t)(const void *heap_data, const void *user_data,
							  void *param );

typedef int (*heap_ismatch_t)(const void *data1, void *param,
							  const void *data2);
typedef enum heap_status
{
	HEAP_SUCCESS,
	HEAP_FAIL
} heap_status_t;

/**
 *	Allocates Heap
 *	args:
 *		compare_func - pointer to ordering function
 *
 * 	returns
 * 		on fail - NULL
 * 		otherwise pointer to heap
 */
heap_t *HeapCreate(heap_compare_t compare_func, void *param);

/**
 *	Deallocates Heap
 *		args:
 *			heap - pointer to heap
 */
void HeapDestroy(heap_t *heap);

/**
 *	Insert element according to Heap ordering
 *		args:
 *			heap - pointer to heap
 *			data - pointer to user data
 */
heap_status_t HeapPush(heap_t *heap, void *data);

/**
 *	Removes Top element from the heap
 *		args:
 *			heap - pointer to heap
 */
void HeapPop(heap_t *heap);

/**
 *	Get data of the top element of the heap
 *		args:
 *			heap - pointer to heap
 *	returns:
 *		fail  	- NULL,
 * 		success - pointer to data
 */
void *HeapPeek(const heap_t *heap);

/**
 *	Remove data from heap
 *		args:
 *			heap - pointer to heap
 *          data - data to remove
 *          is_match - funtcion to check if data match to heap data
 */
void *HeapRemove(heap_t *heap, void *data, heap_ismatch_t is_match, void *param);

/**
*      args:
*			heap - pointer to heap
*  returns:
*		    1 - empty
			0 - not empty
 */
int HeapIsEmpty(const heap_t *heap);

/**
 * Get heap size
*      args:
*			heap - pointer to heap
*  returns:
*		heap size
 */
size_t HeapSize(const heap_t *heap);

#endif /* __HEAP_H__ */
