/**********************************************************************;
* Project           : Data Structures
*
* Program name      : mergesort.c
*
* Author            : Michelle Gelfand
*
* Date created      : 01.08.19
*
* Purpose           : Merge sort algorithm
*
* Version           : 1.0
*														  
**********************************************************************/

#include <stdio.h>/*printf* */
#include <stdlib.h> /*malloc*/

static int _MergeHalves(int *left, int *right, size_t lengthL, size_t lengthR)
{
	int *merged = (int*)malloc(sizeof(int)*(lengthL+lengthR));

	size_t idx = 0;
	size_t r_idx = 0;
	size_t l_idx = 0;


	if(merged)
	{
		while (( lengthL > l_idx) && (lengthR > r_idx))
		{
			if(left[l_idx] > right[r_idx])
			{
				merged[idx] = right[r_idx];
				++r_idx;
				++idx;
			}
			else
			{
				merged[idx] = left[l_idx];
				++l_idx;
				++idx;
			}

		}

		/*if only one half finished fill remaining merged array */
		while( lengthL > l_idx)
		{
			merged[idx] = left[l_idx];
			++idx;
			++l_idx;
		}
		while( lengthR > r_idx)
		{
			merged[idx] = right[r_idx];
			++idx;
			++r_idx;
		}

		/*merged array filled correctly, now copy to original array (which starts at pointer left) */
		for(idx = 0; idx < (lengthL+lengthR); ++idx)
		{
			left[idx] = merged[idx];
		}

		free(merged); 
		return 0;
	}
	else
	{
		return 1;
	}
}

int *_Split(int *arr, size_t length, int *status)
{
    int *left = NULL;
    int *right = NULL;

    if ( 1 < length)
    {
        right = _Split(arr+((length/2)), (length - (length/2)), status); 
        left = _Split(arr, (length)/2, status);

       *status |= _MergeHalves(left, right, (length/2), (length - length/2));
    }

    return arr;
}

int MergeSort(int *arr, size_t length)
{
	int status = 0;

	_Split(arr, length, &status);
	return status;
}

int main()
{
	int array[] = {19, 31, 16, -4, 12, 87, 24, 7, 2, 7, 89, 1, -7};
	int i = 0;
	int status = MergeSort(array, 13);

	printf("\n\nstatus = %d\n\n", status);
	for (i=0; i<13; ++i)
	{
		printf("%d ", array[i]);
	}

	return 0;
}



