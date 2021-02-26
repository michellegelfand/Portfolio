/******************************************************************************/
/*    @File:       simple_sort.h                                              */
/*    @Created:    16.07.19                                                   */
/*    @Version:    1.2	                                                      */
/*    @Author:                                                                */
/*                                                                            */
/*    @Brief:        Sort Functions    :              BubbleSort     	 	  */
/*                                                    SelectionSort		   	  */
/*                                                    InsertionSort   		  */
/*													  CountingSort	    	  */
/*													  RadixSort	
													  QuickSort			      */
/******************************************************************************/
/*changelog

1.2 - Quicksort returns status_t */

#ifndef __SIMPLE_SORT_H__
#define __SIMPLE_SORT_H__

#include <stddef.h> /* size_t */

typedef enum status
{
	SORT_SUCCESS,
	SORT_ALLOCATION_FAIL
} status_t;


/*
	quick_cmp_t returns:

							negative - data1 smaller than data2
							0 		 - data1 is equal to data2
							positive - data1 is bigger than data2
 */

typedef int (*quick_cmp_t) (void *data1, void *data2, void *param);

/******************************************************************************/
/*BubbleSort - sort array of integers from small to large values

ARGS:            array of integers
				 size of array

*/
void BubbleSort(int *array, size_t size);

/******************************************************************************/
/*SelectionSort - sort array of integers from small to large values

ARGS:            array of integers
				 size of array

*/
void SelectionSort(int *array, size_t size);

/******************************************************************************/
/*InsertionSort - sort array of integers from small to large values

ARGS:            array of integers
				 size of array

*/
void InsertionSort(int *array, size_t size);

/******************************************************************************/
/*CountingSort - sort array of integers from small to large values

ARGS:            array of integers
				 size of array

return:			SORT_SUCCESS
				SORT_ALLOCATOIN_FAIL
*/
status_t CountingSort(int *array, size_t size);

/******************************************************************************/
/*RadixSort - sort array of integers from small to large values

ARGS:           array of integers
				size of array

return:			SORT_SUCCESS
				SORT_ALLOCATOIN_FAIL

*/
status_t RadixSort(int *array, size_t size);

/******************************************************************************/
/*	QuickSort - 

ARGS:			array of data,
				size of darray,
				size of each element,
				quick_cmp_t function,
				param (optional)
returns:
				SORT_SUCCESS
				SORT_ALLOCATOIN_FAIL
 */

status_t QuickSort ( void *base, size_t size, size_t element_size, quick_cmp_t Compare, void *param);

#endif /* __SIMPLE_SORT_H__*/