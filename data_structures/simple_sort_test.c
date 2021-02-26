/**********************************************************************;
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
*******************************************************************/


#include <stdio.h>/*printf*/
#include <stdlib.h>/*rand*/
#include <time.h>/*time*/

#include "simple_sort.h"

#define ARR_SIZE 20


void PrintSort(int *array,int size);
void PassOrFail(int *array,int size);
void BubbleSort_test();
void SelectionSort_test();
void InsertionSort_test();
void CountingSort_test();
void RadixSort_test();
void QuickSort_Test();

int Compare (void *data1, void *data2, void *param);

int main()
{
	/* BubbleSort_test();
	SelectionSort_test();
	InsertionSort_test();
	CountingSort_test();	
	RadixSort_test();
 */

	QuickSort_Test();
	return 0;
}

void QuickSort_Test()
{
	int arr[] = {-3, 5, 12, 8, -9, 21, -3, 22, -3, 19, 15, 13, 14, -5000, 5000};
	int i =0;
	int array_size = sizeof(arr)/sizeof(*arr);

	QuickSort(arr, array_size, sizeof(int), Compare, NULL);

	for(i=0; i<array_size; ++i)
	{
		printf("%d,  ", arr[i]);
	}


}

int Compare (void *data1, void *data2, void *param)
{
	(void)param;

	if(*(int*)data1 >*(int*)data2)
	{
		return 1;
	}
	else if(*(int*)data1<*(int*)data2)
	{
		return -1;
	}

	return 0;
}
void PassOrFail(int *array, int size)
{
	int i=0;
	int pass = 1;

	if( -12 != array[0])
	{
		pass=0;
	}

	for(i=0; i<size-1; ++i)
	{
		if( i+1 != array[i])	
		{
			pass=0;
		} 
	}

	if(0 == pass)
	{
		printf("FAIL");
	}
}
void PrintSort(int *array, int size)
{
	int i=0;

	printf("\n\n");
	for(i =0; i<size; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n\n");
}

void BubbleSort_test()
{
	int array[] = {3, 7, 1, 2, 4, 6, 8, 5, 9, -12};
	
	BubbleSort(array, 10);
	PrintSort(array, 10);

}
void SelectionSort_test()
{
	int array[] = {3, 7, 1, 2, 4, 6, 8, 5, 9, -12};

	SelectionSort(array, 10);
	PrintSort(array, 10);

}
void InsertionSort_test()
{
	int array[] = {3, 7, 1, 2, 4, 6, 8, 5, 9, -12};

	InsertionSort(array, 10);
	PrintSort(array, 10);

}
void CountingSort_test()
{
	int array1[] = {3, 7, 1, 2, 4, 6, 8, 5, 9, -12};
	int i =0;
	int array2 [ARR_SIZE] = {0};
	srand(time(NULL));

	CountingSort(array1, 10);
	PrintSort(array1, 10);

	for(i = 0; i<ARR_SIZE; ++i)
	{
		array2[i] = ( (rand()%100) + 1 );
	}
	for(i = 0; i<ARR_SIZE; ++i)
	{
		printf(" %d ", array2[i]);
	}

	CountingSort(array2, ARR_SIZE);

	printf("\n\n");

	for(i = 0; i<ARR_SIZE; ++i)
	{
		printf(" %d ", array2[i]);
	}

	printf("\n\n");
}
void RadixSort_test()
{
	int array1[] = {3, 7, 1, 2, 4, 6, 8, 5, 9, -12};
	int i =0;
	int array2 [ARR_SIZE] = {0};
	int array3[ARR_SIZE] = {0};
	srand(time(NULL));

	RadixSort(array1, 10);
	PrintSort(array1, 10);

	for(i = 0; i<ARR_SIZE; ++i)
	{
		array2[i] = ( (rand()%100) + 1 );
	}
	for(i = 0; i<ARR_SIZE; ++i)
	{
		printf(" %d ", array2[i]);
	}

	RadixSort(array2, ARR_SIZE);

	printf("\n\n");

	for(i = 0; i<ARR_SIZE; ++i)
	{
		printf(" %d ", array2[i]);
	}

	for(i=0; i<ARR_SIZE; ++i)
	{
		array3[i] = ( (rand()%9000000) + 1000001 );
	}
	
	RadixSort(array3, ARR_SIZE);

	printf("\n\n\n");

	for(i = 0; i<ARR_SIZE; ++i)
	{
		printf(" %d ", array3[i]);
	}

	printf("\n\n");
}

