#include <stdio.h> /*printf */

#include "test_tools.h"
#include "searches.h"

int Compare (void const *data1, void const *data2, void *param);

void BinaryItr();
void BinaryRec();
void Jump();

int main()
{
  /*   BinaryItr(); */
    /* BinaryRec(); */
    Jump();
    return 0;
}


void Jump()
{
    int arr[] = {5,8,9, 12, 34, 43, 54, 65, 89};
    int not_in_arr = 999;
    int *found =  JumpSearch(arr, sizeof(arr)/sizeof(*arr),
                    sizeof(*arr),  Compare, NULL, &not_in_arr );
         
    if( NULL != found)
    {
        printf(RED"result not as expected");
    }
 
    found =  JumpSearch(arr, sizeof(arr)/sizeof(*arr),
                    sizeof(*arr),  Compare, NULL, &arr[5] );

    printf("%d", *found);

    if( 43 != *found)
    {
        printf(RED"result not as expected");
    }
  
}

void BinaryItr()
{
    int arr[] = {5,8,9, 12, 34, 43, 54, 65, 89};
    int not_in_arr = 999;
    int *found =  BinarySearch(arr, sizeof(arr)/sizeof(*arr),
                    sizeof(*arr),  Compare, NULL, &not_in_arr );
         
    if( NULL != found)
    {
        printf(RED"result not as expected");
    }
 
    found =  BinarySearch(arr, sizeof(arr)/sizeof(*arr),
                    sizeof(*arr),  Compare, NULL, &arr[1] );

    if( 8 != *found)
    {
        printf(RED"result not as expected");
    }
  
}


void BinaryRec()
{
    int arr[] = {5,8,9, 12, 34, 43, 54, 65, 89};
    int not_in_arr = 999;
    int *found =  BinarySearchRecursively(arr, sizeof(arr)/sizeof(*arr),
                    sizeof(*arr),  Compare, NULL, &not_in_arr );
         
    if( NULL != found)
    {
        printf(RED"result not as expected");
    }
 
    found =  BinarySearchRecursively(arr, sizeof(arr)/sizeof(*arr),
                    sizeof(*arr),  Compare, NULL, &arr[6] );

    if( 54 != *found)
    {
        printf(RED"result not as expected");
    }
 

    
}

int Compare (void const *data1, void const *data2, void *param)
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