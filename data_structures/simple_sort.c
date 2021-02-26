/******************************************************************************;
* Project           : Data Structures
*
* Program name      : simple_sort.c
*
* Author            : Michelle Gelfand
*
* Date created      : 16.07.19
*
* Purpose           : This program provides the user
					  with 5 sorting algorithms
*
* Version           : 1.3
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer
* 17/07/2019       	  Michelle Gelfand           Assaf B. *
*******************************************************************************/

#include <stdlib.h>/*calloc, size_t, rand*/
#include <assert.h>/*assert*/
#include <math.h> /*abs*/
#include <string.h>/*memcpy */
#include <time.h>/*time */

#include "simple_sort.h"

#define DIGIT_LUT_MIN -9
#define DIGIT_LUT_RANGE 19
/*************************************************************************** */
static void Swap(int *num1, int *num2);
static size_t GetRange (int *array, size_t size);
static int GetMin(int *array, size_t size);
static int GetBiggestAbsValue(int *array, size_t size);

static void QuickSortRec ( void *base, size_t size, size_t element_size,
quick_cmp_t Compare, void *param, void *buffer);
void UpdatePivot(size_t *pivot_idx, size_t left_idx, size_t right_idx);

static size_t Partition(void *base, size_t left_idx, size_t right_idx,
quick_cmp_t Compare, void *param, size_t element_size, void *buffer);
static void QuickSortSwap(void *element1, void *element2, size_t element_size, void *buffer);
/******************************************************************************/
status_t QuickSort ( void *base, size_t size, size_t element_size,
quick_cmp_t Compare, void *param)
{
	void *buffer = NULL;

    assert(base);
    assert(element_size);
    assert(Compare);
    assert(size);

	buffer = (void*)malloc(sizeof(element_size));

	if(!buffer)
	{
		return SORT_ALLOCATION_FAIL;
	}
	 
	QuickSortRec (base, size, element_size, Compare, param, buffer);

	free(buffer);
	buffer = NULL;

	return SORT_SUCCESS;
}

static void QuickSortRec ( void *base, size_t size, size_t element_size,
quick_cmp_t Compare, void *param, void *buffer)
{

	size_t right_idx = size - 1;
	size_t pivot_idx = 0;
	void *pivot_elem = NULL;

	if(size > 1)
    {
 	    pivot_idx = Partition(base, 0, right_idx, Compare, param, element_size,
							  buffer);

		pivot_elem = (void*)((char*)base + (char)element_size * (pivot_idx + 1));

        QuickSortRec(base, pivot_idx, element_size, Compare, param, buffer);
			/*TODO maby more vars? not so easy to read*/
        QuickSortRec(pivot_elem, right_idx-pivot_idx, element_size, Compare, param, buffer);
    }
}

static size_t Partition(void *base, size_t left_idx, size_t right_idx,
quick_cmp_t Compare, void *param, size_t element_size, void *buffer)
{
    size_t pivot_idx = 0;
	void *left_element = NULL;
	void *right_element = NULL;
	void *pivot = NULL;

    srand(time(NULL));

    pivot_idx = (size_t)(rand()%right_idx- left_idx) + left_idx;

	while(left_idx != right_idx)

	{
		pivot = (void*)((char*)base+(char)element_size*pivot_idx);

		for(; left_idx < pivot_idx; ++left_idx)
		{
			left_element = (void*)((char*)base + (char)element_size * left_idx);

			/*if element > pivot */
			if( 0 < Compare(left_element, pivot, param))
			{
				break;
			}
		}

		for(; pivot_idx < right_idx; --right_idx)
		{
			right_element = (void*)((char*)base + (char)element_size * right_idx);

			/*if element < pivot */
			if(0 > Compare(right_element, pivot, param))
			{
				break;
			}
		}

		left_element = (void*)((char*)base + (char)element_size * left_idx);
		right_element = (void*)((char*)base + (char)element_size * right_idx);

		QuickSortSwap(left_element, right_element, element_size, buffer);

		UpdatePivot(&pivot_idx, left_idx, right_idx);
	}

	return pivot_idx;
}
/*if one of the swapped elements is pivot, update pivot index*/
void UpdatePivot(size_t *pivot_idx, size_t left_idx, size_t right_idx)
{
	if(left_idx == *pivot_idx)
	{
		*pivot_idx = right_idx;
	}
	else if(right_idx == *pivot_idx)
	{
		*pivot_idx = left_idx;
	}
}

static void QuickSortSwap(void *element1, void *element2, size_t element_size,
						  void *buffer)
{
	if(element1 != element2)
	{
		memcpy(buffer, element1, element_size);
		memcpy(element1, element2, element_size);
		memcpy(element2, buffer, element_size);
	}
}

/**************************static funcs***************************************/
static void Swap(int *num1, int *num2)
{
	int hold_val = 0;

	assert(num1);
	assert(num2);

	hold_val = *num1;
	*num1 = *num2;
	*num2 = hold_val;
}

/*range between smallest and biggest num in array, to use for lut*/
static size_t GetRange (int *array, size_t size)
{
	size_t arr_idx =0;
	int min = *array;
	int max = *array;

	for(arr_idx =0; arr_idx < size; ++arr_idx)
	{
		if( max < array[arr_idx])
		{
			max = array[arr_idx];
		}

		if( min > array[arr_idx])
		{
			min = array[arr_idx];
		}
	}

	return (size_t)(max - min + 1);
}

static int GetMin(int *array, size_t size)
{
	size_t arr_idx =0;
	int min = *array;

	for(arr_idx = 0; arr_idx < size; ++arr_idx)
	{
		if( min > array[arr_idx])
		{
			min = array[arr_idx];
		}
	}

	return min;
}

static int GetBiggestAbsValue(int *array, size_t size)
{
	size_t arr_idx =0;
	int max_abs_value = abs(*array);

	for(arr_idx = 0; arr_idx < size; ++arr_idx)
	{
		if( max_abs_value < abs(array[arr_idx]))
		{
			max_abs_value = abs(array[arr_idx]);
		}
	}

	return max_abs_value;
}

size_t GetDigitCount(int num)
{
	int digit_count = 0;

	/*do once in case num is zero*/
	do
    {
        num /= 10;
        ++digit_count;
    }
	while(num);

	return digit_count;
}

static int GetDigit(int num, int current_digit)
{
	int devider = 1;
	int digits = GetDigitCount(num);
	int index = 0;

	/*in case less digits than current_digit*/
	for(index = 0; (index < digits) && (index < current_digit); ++index)
	{
		devider *= 10;
	}

	return ((num / devider) % 10);
}

/*This is an appended version of CountingSort to be used for RadixSort.
  Compares digits rather than whole number*/

/*current_digit 0 for ones, current_digits 1 for dozens, etc.*/
static status_t DigitCountingSort(int *array, size_t size, size_t current_digit)
{
	status_t op_status = SORT_SUCCESS;
	size_t lut_idx = 0;
	size_t arr_idx = 0;
	int min = 0;
	int *lut = NULL;
	int *sorted = NULL;

	assert(array);
	assert(size);

	min = DIGIT_LUT_MIN;

	lut = calloc( sizeof(int),DIGIT_LUT_RANGE);

	if(!lut)
	{
		lut = NULL;
		return SORT_ALLOCATION_FAIL;
	}

	sorted = calloc(sizeof(int) , size);

	if(!sorted)
	{
		free(lut);
		lut = NULL;
		return SORT_ALLOCATION_FAIL;
	}

	/*count appearances of each val in array*/
	for(arr_idx = 0; arr_idx < size; ++arr_idx)
	{
		++lut[GetDigit(array[arr_idx], current_digit) - min];
	}

	/*accumulate counts*/
	for(lut_idx = 1; lut_idx < DIGIT_LUT_RANGE; ++lut_idx)
	{
		lut[lut_idx] += lut[lut_idx - 1];
	}

	/*fill sorted array*/
	for(arr_idx = size - 1; (int)arr_idx >= 0; --arr_idx)
	{
		int correct_place =
			(lut[ (GetDigit(array[arr_idx], current_digit)) - min ]) - 1;

		sorted[ correct_place ] = 	array[arr_idx];

		--lut[ (GetDigit(array[arr_idx], current_digit) - min) ];
	}

	/*transfer sorted array to original array*/
	for(arr_idx = 0; arr_idx < size; ++arr_idx)
	{
		array[arr_idx] = sorted[arr_idx];
	}

	free(sorted);
	free(lut);

	return op_status;
}

/*****************************API funcs***************************************/
void BubbleSort(int* array, size_t size)
{
	int arr_idx = 0;
	int needs_sort = 1;

	assert(array);

	while(needs_sort)
	{
		needs_sort = 0;

		while( size > (size_t)(arr_idx+1) )
		{
			if( array[arr_idx] > array[arr_idx+1])
			{
				needs_sort = 1;
				Swap( &array[arr_idx], &array[arr_idx+1]);
			}

			++arr_idx;
		}

		arr_idx = 0;
	}
}

void SelectionSort(int* array, size_t size)
{
	int arr_idx = 0;
	int scan_arr = 0;
	int smallest = 0;

	assert(array);

	while( size > (size_t)arr_idx)
	{
		for(scan_arr=arr_idx; (size_t)scan_arr < size; ++scan_arr)
		{
			if(array[smallest]>array[scan_arr])
			{
				smallest = scan_arr;
			}
		}

		Swap(&array[smallest], &array[arr_idx]);

		++arr_idx;
		smallest = arr_idx;
	}
}

/*algorithm finds smallest number, moves all numbers behind it a step forward,
  then pastes that number before the unsorted numbers*/
void  InsertionSort(int* array, size_t size)
{
	int arr_idx = 0;
	int scan_arr = 0;
	int smallest = 0;
	int insert_at_start = 0;

	assert(array);

	while( size > (size_t)arr_idx)
	{
		for(scan_arr=arr_idx; (size_t)scan_arr < size; ++scan_arr)
		{
			if(array[smallest]>array[scan_arr])
			{
				smallest = scan_arr;
			}
		}

		insert_at_start = array[smallest];

		for(scan_arr = smallest; scan_arr > arr_idx; --scan_arr)
		{
			array[scan_arr] = array[scan_arr-1];
		}

		array[arr_idx] = insert_at_start;

		++arr_idx;
		smallest = arr_idx;
	}
}

status_t CountingSort(int *array, size_t size)
{
	status_t op_status = SORT_SUCCESS;
	size_t lut_idx = 0;
	size_t arr_idx = 0;
	size_t range = 0;
	int min = 0;
	int *lut = NULL;
	int *sorted = NULL;

	assert(array);
	assert(size);

	range = GetRange(array, size);
	min =  GetMin(array, size);

	lut = calloc(sizeof(int) , range);

	if(!lut)
	{
		lut = NULL;
		return SORT_ALLOCATION_FAIL;
	}

	sorted = calloc(sizeof(int) , size);

	if(!sorted)
	{
		free(lut);
		lut = NULL;
		return SORT_ALLOCATION_FAIL;
	}

	/*count appearances of each val in array*/
	for(arr_idx = 0; arr_idx < size; ++arr_idx)
	{
		lut[(array[arr_idx] - min)] +=1;
	}

	/*accumulate counts*/
	for(lut_idx = 1; lut_idx< range; ++lut_idx)
	{
		lut[lut_idx]+= lut[lut_idx-1];
	}

	/*fill sorted array*/
	for(arr_idx = 0; arr_idx < size; ++arr_idx)
	{
		sorted[ (lut[ (array[arr_idx])- min ]) - 1] = array[arr_idx];
		--lut[ (array[arr_idx] - min) ];
	}

	/*transfer sorted array to original array*/
	for(arr_idx = 0; arr_idx<size; ++arr_idx)
	{
		array[arr_idx] = sorted[arr_idx];
	}

	free(sorted);
	free(lut);

	return op_status;
}

status_t RadixSort(int *array, size_t size)
{
	status_t op_status = SORT_SUCCESS;
	int max_digits_member = 0;
	int digit_count =0;
	int current_digit = 0;

	assert(array);
	assert(size);

	max_digits_member = GetBiggestAbsValue(array, size);
	digit_count = GetDigitCount(max_digits_member);

	while(digit_count  > current_digit)
	{
		op_status |= DigitCountingSort(array, size, current_digit);

		++current_digit;
	}

	return op_status;
}
