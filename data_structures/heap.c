/**********************************************************************;
* Project           : Data Structures
*
* Program name      : heap.c
*
* Author            : Michelle Gelfand
*
* Purpose           : provide heap data structure	
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 06/08/2019       	  Michelle Gelfand           Doron W.														  
*******************************************************************/

#include <stdlib.h> 	/* malloc */
#include <assert.h> 	/* assert */
#include <string.h> 	/* memcpy */
#include <sys/types.h>  /* ssize_t */

#include "heap.h"
#include "dynamic_vector.h"

#define INITIAL_HEAP_SIZE 40
#define LEFT_CHILD  (2*idx + 1)
#define RIGHT_CHILD (2*idx + 2)

static void SiftUp(heap_t *heap, size_t idx);
static void SiftDown(heap_t *heap, size_t idx);
static void SwapElements(void** element1, void** element2);
static ssize_t FindIdxToRemove(heap_t *heap, void* data, 
heap_ismatch_t is_match, void *param);

struct heap
{
	heap_compare_t func;
	dynamic_vector_t *vector;
    void *param;
};

/**********P R I N T **********************************************************/

#ifndef DNDEBUG

#include <stdio.h> 		/* printf */
static void PrintHeap(heap_t *heap)
{
    size_t i = 0;
    size_t size = HeapSize(heap);

    printf("\nVector : ");

    for ( i = 0; i < size ; ++i )
    {
        printf("%d ", (**(int**)DynamicVectorGetElementAddress(heap->vector, i)));
    }
    printf("\n");
}

#endif /*DNDEBUG

/******************************************************************************/

heap_t *HeapCreate(heap_compare_t compare_func, void *param)
{
    heap_t *heap = NULL;
    assert(compare_func);

    heap = (heap_t*)malloc(sizeof(heap_t));

    if(heap)
    {
        heap->vector = DynamicVectorCreate(sizeof(void*), INITIAL_HEAP_SIZE);

        if(heap->vector)
        {
            heap->func = compare_func;
            heap->param = param;
        }
        else
        {
            free(heap);
			heap = NULL;
        } 
    }

    return heap;
}

/******************************************************************************/

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    DynamicVectorDestroy(heap->vector);

    memset(heap, 0, sizeof(heap));

    free(heap);
    heap = NULL;
}
/******************************************************************************/

heap_status_t HeapPush(heap_t *heap, void *data)
{   
    heap_status_t status = HEAP_SUCCESS;

    assert(heap);

    if( SUCCESS == DynamicVectorPushBack(heap->vector, &data))
    {
        SiftUp(heap, DynamicVectorCount(heap->vector) -1);
    }
    else
    {
        status = HEAP_FAIL;
    }

    return status;
}
/******************************************************************************/

static void SwapElements(void** element1, void** element2)
{
    void *buffer = NULL;

    buffer = *element1;
    *element1 = *element2;
    *element2 = buffer;
}

static void **GetElementAddress(heap_t *heap, size_t idx)
{
    return (void**)DynamicVectorGetElementAddress(heap->vector, idx);
}

static void SiftDown(heap_t *heap, size_t idx)
{
    void **element = NULL;
    void **left_child = NULL;
    void **right_child = NULL;
    size_t vector_size = 0;

    assert(heap);

    vector_size = DynamicVectorCount(heap->vector);
    
    while(LEFT_CHILD < vector_size) 
    {
        element =  DynamicVectorGetElementAddress(heap->vector, idx);
        left_child = DynamicVectorGetElementAddress(heap->vector, LEFT_CHILD);
        right_child = DynamicVectorGetElementAddress(heap->vector, RIGHT_CHILD);
                     
        if( right_child &&
            ( 0 > heap->func(*left_child, *right_child, heap->param)) )
        {
            if(  0 > heap->func(*element, *right_child, heap->param))
            {
                SwapElements(right_child, element);
                idx = RIGHT_CHILD;
            }
            else
            {
                break;
            }  
        }
        else
        {
            if(0 > heap->func(*element, *left_child, heap->param))
            {
                SwapElements(left_child, element);
                idx = LEFT_CHILD;
            }
            else
            {
                break;
            } 
        }
	}	
}

static void SiftUp(heap_t *heap, size_t idx)
{
    void **element = NULL;
    void **parent = NULL;

    assert(heap);

    /*while has parent */
    while( 0 < idx)
    {
        element = DynamicVectorGetElementAddress(heap->vector, idx);
        parent = DynamicVectorGetElementAddress(heap->vector, (idx-1)/2);

        if(parent && element && 0 > heap->func(*parent, *element, heap->param))
        {
            /*if parent 'smaller' */
         	SwapElements(parent, element);
            idx = (idx-1)/2;
        }
        else
        {
            /*destination reached */
            break;
        }
    }
}

/******************************************************************************/

void *HeapPeek(const heap_t *heap)
{
    assert(heap);

    if(HeapIsEmpty(heap))
    {
        return NULL;
    }

    return *(void**)DynamicVectorGetElementAddress(heap->vector, 0);
}
/******************************************************************************/

void HeapPop(heap_t *heap)
{
    size_t last_idx = 0;
    void **last_element = NULL;
    void **heap_front = NULL;

    assert(heap);

	if(!HeapIsEmpty(heap))
	{		
		heap_front = GetElementAddress(heap, 0);

    	last_idx = HeapSize(heap) - 1;
        
    	last_element = GetElementAddress(heap, last_idx);

    	SwapElements(heap_front, last_element);

    	DynamicVectorPopBack(heap->vector);

	    SiftDown(heap, 0);
	}
}

/******************************************************************************/

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return DynamicVectorIsEmpty(heap->vector);
}
/******************************************************************************/

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return DynamicVectorCount(heap->vector);
}
/******************************************************************************/

void *HeapRemove(heap_t *heap, void *data, heap_ismatch_t is_match, void *param)
{
    ssize_t idx_to_remove= 0;
    void **removed_data = NULL;
    void *removed = NULL;
    assert(heap);
    assert(is_match);

    idx_to_remove = FindIdxToRemove(heap, data, is_match, param);

    if(-1 == idx_to_remove)
    {
        return NULL;
    }

    /*swap last element with to_remove */
    SwapElements(GetElementAddress(heap, idx_to_remove), 
                 GetElementAddress(heap, HeapSize(heap) - 1 ));

    removed_data = GetElementAddress(heap, HeapSize(heap)-1);
    
	removed = *removed_data;

    DynamicVectorPopBack(heap->vector);

	if(!HeapIsEmpty(heap))
	{
    	SiftUp(heap, idx_to_remove);
    	SiftDown(heap, idx_to_remove);
	}

    return removed;
}


static ssize_t FindIdxToRemove(heap_t *heap, void* data,
                                heap_ismatch_t is_match, void* param)
{
    size_t vector_size = 0;
    size_t idx = 0;
    assert(heap);

    vector_size = HeapSize(heap);

    if(vector_size)
    {
        for(idx = 0; idx < vector_size; ++idx)
        {
            if(is_match( *(void**)DynamicVectorGetElementAddress
						  (heap->vector, idx), param, data))
            {
                return idx;
            }
        }
	}
   
    return -1;
}

