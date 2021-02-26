/**********************************************************************;
* Project           : Data Structures
*
* Program name      : queue.c
*
* Author            : Michelle Gelfand
*
* Date created      : 25.06.19
*
* Purpose           : This program provides the user with a
*					  self sorting list structure, and operations to store, 
*					  edit and access data in it.
*
* Version           : 1.4
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 27/06/2019       	  Michelle Gelfand           Waed S. 														  
*******************************************************************/


#include <stdio.h>/*printf*/
#include <assert.h>/*assert*/

#include "sorted_list.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

int SortListCreate_test();
int SortListDestroy_test();
int SortListCount_test();
int SortListIsEmpty_test();
int SortListBegin_test();
int SortListEnd_test();
int SortListNext_test();
int SortListPrev_test();
int SortListGetData_test();
int SortListIsSameIterator_test();
int SortListInsert_test();
int SortListFind_test();
int SortListFindBySortKey_test();
int SortListRemove_test();
int SortListPopBack_test();
int SortListPopFront_test();
int SortListMerge_test();
int SortListForEach_test();

int Compare_test(const void *data1, const void *data2);
int IsMatch(const void *data1, void *param, const void *data2);
int main()
{
	int test_result = 0;

	test_result |= SortListCreate_test();
	test_result |= SortListDestroy_test();
	test_result |= SortListCount_test();
	test_result |= SortListIsEmpty_test();
	test_result |= SortListBegin_test();
	test_result |= SortListNext_test();
	test_result |= SortListPrev_test();
	test_result |= SortListGetData_test();
	test_result |= SortListIsSameIterator_test();
	test_result |= SortListInsert_test();
	test_result |= SortListFind_test();
	test_result |= SortListFindBySortKey_test();
	test_result |= SortListRemove_test();
	test_result |= SortListPopBack_test();
	test_result |= SortListPopFront_test();
	test_result |= SortListMerge_test();
	test_result |= SortListForEach_test();

	(0 == test_result)? printf(KCYN"\n\nALL TESTS PASSED\n\n"WHITE) :
						printf(RED"\n\nFailed on some tests\n\n"WHITE);

	return 0;
}
/*************************User Func Simulators*********************************/
/*returns bigger >0 smaller <0 or equal 0 */
int Compare_test(const void *data1, const void *data2)
{
	assert(data1);
	assert(data2);

	return (*(int*)data1 - *(int*)data2);
}
/*returns 1 for match, 0 for no match*/
int IsMatch(const void *data1, void *param, const void *data2)
{
	assert(data1);
	assert(data2);

	(void)param;

	return ( !!(*(int*)data1 ==*(int*)data2) );
}
int Action(void *data, void *param)
{
	int result = 0;

	assert(data);

	if (900 != *(int*)data)
	{
		*(int*)data += *(int*)param;
	}
	else
	{
		result = 1;
	}
	
	return result;
}
/******************************************************************************/
int SortListCreate_test()
{
	int test_result = 0;
	sort_list_t *new_list = SortListCreate(Compare_test);

	printf(KCYN"\n\nCreate Sorted List Test:\n"WHITE);

	if (new_list)
	{
		printf(GREEN"\nSuccesfully created sorted list\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to create sorted list\n"WHITE);

		test_result+=1;
	}

	printf(YELLOW"\nCombine this test with valgrind to assure"\
				 " no memory leaks\n");	
	
	SortListDestroy(new_list);

	return test_result;
}
/******************************************************************************/
int SortListDestroy_test()
{
	int test_result = 0;
	sort_list_t *new_list = SortListCreate(Compare_test);

	printf(KCYN"\n\nDestroy Sorted List Test:\n"WHITE);

	SortListDestroy(new_list);

	if ( NULL != new_list)
	{
		printf(GREEN"\nSuccesfully destroyed sorted list\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to destroy sorted list\n"WHITE);

		test_result+=1;
	}

	printf(YELLOW"\nCombine this test with valgrind to assure"\
				 " no memory leaks\n");	
	
	

	return test_result;
}

int SortListCount_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);

	printf(KCYN"\n\nCount Test:\n"WHITE);

	if ( 0 == SortListCount(new_list))
	{
		printf(GREEN"\nSuccesfully counted zero for empty list\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to count zero for empty list\n"WHITE);

		test_result+=1;
	}

	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data+3);

	if ( 4 == SortListCount(new_list))
	{
		printf(GREEN"\nSuccesfully counted four elements\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to count four elements\n"WHITE);

		test_result+=1;
	}
	
	SortListDestroy(new_list);

	return test_result;
}
int SortListIsEmpty_test()
{
	int test_result = 0;
	int data = 1;
	sort_list_t *new_list = SortListCreate(Compare_test);

	printf(KCYN"\n\nIs Empty Test:\n"WHITE);

	if ( SortListIsEmpty(new_list) )
	{
		printf(GREEN"\nSuccesfully returned list is empty\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return list is empty\n"WHITE);

		test_result+=1;
	}

	SortListInsert(new_list, &data);

	if ( !SortListIsEmpty(new_list) )
	{
		printf(GREEN"\nSuccesfully returned list not empty\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return list not empty\n"WHITE);

		test_result+=1;
	}
	
	SortListDestroy(new_list);

	return test_result;

}
int SortListBegin_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);

	printf(KCYN"\n\nBegin Test:\n"WHITE);

	if ( (int*)SortListGetData(SortListEnd(new_list)) == 
		 (int*)SortListGetData(SortListBegin(new_list) ) )
	{
		printf(GREEN"\nSuccesfully returned end for empty list\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return end for empty list\n"WHITE);

		test_result+=1;
	}

	SortListInsert(new_list, data);

	if ( 1 == *(int*)SortListGetData(SortListBegin(new_list)) )
	{
		printf(GREEN"\nSuccesfully returned first element\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return first element\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListEnd_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);
	SortListInsert(new_list, data);
	printf(KCYN"\n\nEnd Test:\n"WHITE);

	if ( (int*)0xDEADBEEF ==  (int*)SortListGetData(SortListEnd(new_list)) )
	{
		printf(GREEN"\nSuccesfully returned end\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return end\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;	
}
int SortListNext_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);

	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data+3);

	printf(KCYN"\n\nNext Test:\n"WHITE);

	if(2 == *(int*)SortListGetData(SortListNext(SortListBegin(new_list))))
	{
		printf(GREEN"\nSuccesfully returned next element\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return next element\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListPrev_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);

	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data+3);

	printf(KCYN"\n\nPrev Test:\n"WHITE);

	if(4 == *(int*)SortListGetData(SortListPrev(SortListEnd(new_list))))
	{
		printf(GREEN"\nSuccesfully returned previous element\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return previous element\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListGetData_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);

	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data+3);

	printf(KCYN"\n\nGet Data Test:\n"WHITE);

	if(4 == *(int*)SortListGetData(SortListPrev(SortListEnd(new_list))))
	{
		printf(GREEN"\nSuccesfully returned data\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return data\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListIsSameIterator_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);

	sort_list_iter_t a = SortListInsert(new_list, data);
	sort_list_iter_t b = SortListInsert(new_list, data+1);

	printf(KCYN"\n\nIs Same Iterator Test:\n"WHITE);

	if(!SortListIsSameIterator(a, b))
	{
		printf(GREEN"\nSuccesfully returned iterators are not same\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return iterators are not same\n"WHITE);

		test_result+=1;
	}
	if(SortListIsSameIterator(a, a))
	{
		printf(GREEN"\nSuccesfully returned iterators are same\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return iterators are same\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListInsert_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4};
	sort_list_t *new_list = SortListCreate(Compare_test);

	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data);
	SortListInsert(new_list, data+3);
	SortListInsert(new_list, data+1);

	printf(KCYN"\n\nInsert Test:\n"WHITE);

	if(( 1 == *(int*)SortListGetData(SortListBegin(new_list)))&&
	  ( 2 == *(int*)SortListGetData(SortListNext(SortListBegin(new_list))))&&
	  ( 3 == *(int*)SortListGetData(SortListNext(SortListNext(SortListBegin(new_list))))))
	{
		printf(GREEN"\nSuccesfully Insert and Sorting\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to Insert and Sort\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}

int SortListFind_test()
{	
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 8};
	sort_list_t *new_list = SortListCreate(Compare_test);

	sort_list_iter_t to_find = SortListInsert(new_list, data+2);
	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	
	SortListInsert(new_list, data+3);


	printf(KCYN"\n\nFind Test:\n"WHITE);

	if( SortListEnd(new_list).element == SortListFind(SortListBegin(new_list), SortListEnd(new_list), IsMatch, NULL, (data+4)).element )
	{
		printf(GREEN"\nSuccesfully returned end for no match\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return end for no match\n"WHITE);

		test_result+=1;
	}

	if( to_find.element == (SortListFind
	  (SortListBegin(new_list), SortListEnd(new_list), IsMatch, NULL, data+2)).element)
	{
		printf(GREEN"\nSuccesfully found element\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to find element\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;


}
int SortListFindBySortKey_test()
{	
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 8};
	sort_list_t *new_list = SortListCreate(Compare_test);

	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	SortListInsert(new_list, data+3);


	printf(KCYN"\n\nFind By Sort Key Test:\n"WHITE);

	if( SortListEnd(new_list).element == ((SortListFindBySortKey(new_list, Compare_test, data+4)).element))
	{
		printf(GREEN"\nSuccesfully returned end for no match\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to return end for no match\n"WHITE);

		test_result+=1;
	}

	if( SortListBegin(new_list).element == (SortListFindBySortKey(new_list,Compare_test, data)).element)
	{
		printf(GREEN"\nSuccesfully found element\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to find element\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListRemove_test()
{
	sort_list_iter_t remove_node = {0};
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 8};
	sort_list_t *new_list = SortListCreate(Compare_test);

	remove_node = SortListInsert(new_list, data+2);

	SortListRemove(remove_node);

	printf(KCYN"\n\nRemove Test:\n"WHITE);

	if ( SortListIsEmpty(new_list) )
	{
		printf(GREEN"\nSuccesfully removed element\n"WHITE);
	}
	else
	{
		printf(RED"\nFailed to remove element\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListPopBack_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 8};
	sort_list_t *new_list = SortListCreate(Compare_test);
	
	
	printf(KCYN"\n\nPop Back Test:\n"WHITE);

	if(NULL == SortListPopBack(new_list))
	{	
		printf(GREEN"\nback pop empty list return null\n"WHITE);
	}
	else
	{
		printf(RED"\nback pop empty list fail\n"WHITE);

		test_result+=1;
	}
	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	SortListInsert(new_list, data+3);

	SortListPopBack(new_list);

	if ( 3 == *(int*)SortListGetData(SortListPrev(SortListEnd(new_list))))
	{
		printf(GREEN"\nback pop successful\n"WHITE);
	}
	else
	{
		printf(RED"\nback pop failed\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}

int SortListPopFront_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 8};
	sort_list_t *new_list = SortListCreate(Compare_test);
	
	printf(KCYN"\n\nPop Front Test:\n"WHITE);

	if(NULL == SortListPopFront(new_list))
	{	
		printf(GREEN"\nfront pop empty list return null\n"WHITE);
	}
	else
	{
		printf(RED"\nfront pop empty list fail\n"WHITE);

		test_result+=1;
	}

	SortListInsert(new_list, data+2);
	SortListInsert(new_list, data);
	SortListInsert(new_list, data+1);
	SortListInsert(new_list, data+3);

	SortListPopFront(new_list);

	if ( 2 == *(int*)SortListGetData(SortListBegin(new_list)))
	{
		printf(GREEN"\nfront pop successful\n"WHITE);
	}
	else
	{
		printf(RED"\nfront pop failed\n"WHITE);

		test_result+=1;
	}

	SortListDestroy(new_list);
	return test_result;
}
int SortListMerge_test()
{
	int test_result = 0;
	int data_src[] = {2, 4, 5, 6};
	int data_dest[] = {1, 3, 7, 8, 9, 10};
	sort_list_t *src = SortListCreate(Compare_test);
	sort_list_t *dest = SortListCreate(Compare_test);
	sort_list_iter_t printer = {0};
	int i =0;

	printf(KCYN"\n\nMerge Test:\n"WHITE);

	SortListInsert(src, data_src);
	SortListInsert(src, data_src+1);
	SortListInsert(src, data_src+2);
	SortListInsert(src, data_src+3);


	SortListInsert(dest, data_dest);
	SortListInsert(dest, data_dest+1);
	SortListInsert(dest, data_dest+2);
	SortListInsert(dest, data_dest+3);
	SortListInsert(dest, data_dest+4);
	SortListInsert(dest, data_dest+5);

	SortListMerge(src, dest);

	printer = SortListBegin(dest);
	printf("\nnumbers are sorted in src\n");

	for(i=0; i<10; ++i)
	{
		printf(" %d ", *(int*)SortListGetData(printer));

		if ( (int)(i+1) == *(int*)(SortListGetData(printer)))
		{
			printf(GREEN"\nsuccessful merge insert\n"WHITE);
		}
		else
		{
			printf(RED"\nmerge failed failed\n"WHITE);

			test_result+=1;
		}
		printer= SortListNext(printer);
	}
	
	SortListDestroy(dest);
	return test_result;
}


int SortListForEach_test()
{
	int i =0;
	int param = 1;
	int test_result = 0;
	int data_src[] = {1, 2, 3, 4, 5};
	int data_dest[] = {1, 2, 900, 4, 5};
	sort_list_t *src = SortListCreate(Compare_test);
	sort_list_t *dest = SortListCreate(Compare_test);
	sort_list_iter_t printer = {0};
	sort_list_iter_t fail = {0};
	
	printf(KCYN"\n\nFor Each Test:\n"WHITE);

	SortListInsert(src, data_src);
	SortListInsert(src, data_src+1);
	SortListInsert(src, data_src+2);
	SortListInsert(src, data_src+3);
	SortListInsert(src, data_src+4);

	SortListInsert(dest, data_dest);
	SortListInsert(dest, data_dest+1);
	fail = SortListInsert(dest, data_dest+2);
	SortListInsert(dest, data_dest+3);
	SortListInsert(dest, data_dest+4);

	printer = SortListBegin(src);
	printf("\naction on all numbers\n");

	SortListForEach(SortListBegin(src), SortListEnd(src), Action, &param);

	SortListForEach(SortListBegin(dest), SortListEnd(dest), Action, &param);

	for(i=0; i<5; ++i)
	{
		printf(" %d ", *(int*)SortListGetData(printer));

		if ( (int)(i+2) == *(int*)(SortListGetData(printer)))
		{
			printf(GREEN"\naction successful\n"WHITE);
		}
		else
		{
			printf(RED"\naction failed\n"WHITE);

			test_result+=1;
		}
		printer= SortListNext(printer);
	}
	printf("\naction fails\n");

	printer = SortListBegin(dest);
	for(i=0; i<2; ++i)
	{
		printf(" %d ", *(int*)SortListGetData(printer));

		if ( (int)(i+2) == *(int*)(SortListGetData(printer)))
		{
			printf(GREEN"\naction successful\n"WHITE);
		}
		else
		{
			printf(RED"\naction failed\n"WHITE );

			test_result+=1;
		}
		printer= SortListNext(printer);
	}

	if ( 900 == *(int*)SortListGetData(SortListPrev(SortListEnd(dest))))
	{
		printf(GREEN"\nfailed action properly\n"WHITE);
	}
	else
	{
		printf(RED"\nfailed to fail action properly\n"WHITE);

		test_result+=1;
	}
	(void)fail;
	SortListDestroy(dest);
	SortListDestroy(src);

	return test_result;
}



