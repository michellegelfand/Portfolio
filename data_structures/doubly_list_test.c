/**********************************************************************;
* Project           : Data Structures
*
* Program name      : doubly_list.c
*
* Author            : Michelle Gelfand
*
* Date created      : 19.06.19
*
* Purpose           : This program provides the user with a
*					  Double linked list structure, and operations to store, 
*					  edit and access data in it.
*
* Version           : 1.5
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 24/06/2019       	  Michelle Gelfand           Evgeni S. 														  
*******************************************************************/


#include <stdio.h>/*printf*/
#include <stdlib.h>/*free*/

#include "doubly_list.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

int DListCreate_test();
int DListDestroy_test();
int DListCount_test();
int DListIsEmpty_test(); 
int DListBegin_test();
int DListEnd_test();
int DListNext_test();
int DListPrev_test();
int DListGetData_test();
int DListIsSameIterator_test();
int DListInsert_test();
int DListInsertAfter_test();        
int DListRemove_test();
int DListPushFront_test();
int DListPushBack_test();
int DListPopFront_test();
int DListPopBack_test();                                                            
int DListForEach_test();
int DListFind_test();
int DListSpliceBefore_test();

int IsMatch(const void *data1, void *param, const void *data2);
int Action(void *data, void *param);
/****************************************************************************/
int main()
{
	int test_result = 0;

	test_result |= DListCreate_test();
	test_result |= DListDestroy_test();
	test_result |= DListInsert_test();
	test_result |= DListIsEmpty_test();
	test_result |= DListBegin_test();
	test_result |= DListEnd_test();
	test_result |= DListNext_test();
	test_result |= DListPrev_test();
	test_result |= DListGetData_test();
	test_result |= DListIsSameIterator_test();
	test_result |= DListInsertAfter_test();
	test_result |= DListRemove_test();
	test_result |= DListPushFront_test();
	test_result |= DListPushBack_test();
	test_result |= DListPopFront_test();
	test_result |= DListPopBack_test();   
	test_result |= DListCount_test();
	test_result |= DListFind_test();
	test_result |= DListForEach_test();
	test_result |= DListSpliceBefore_test();
	
	(0 == test_result) ? printf(KCYN"\n\nAll Tests Passed\n"WHITE) :
					printf(KCYN"\n\nTests Not Passed\n"WHITE);
	return 0;
}
/******************************************************************************/
int DListCreate_test()
{
	int test_result = 0;
	dl_list_t *new_list = DListCreate();
	
	printf(KCYN"\n\nCreate list test:\n"WHITE);

	if ( NULL != new_list )
	{
		printf(GREEN"\nSuccessfuly create new double linked list\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to create new double linked list\n"WHITE);
		test_result=1;
	}

	printf(YELLOW"\nCombine this test with valgrind to assure"\
				 " no memory leaks\n");	

	DListDestroy(new_list);

	return test_result;
}
/******************************************************************************/
int DListDestroy_test()
{
	int test_result = 0;
	dl_list_t *new_list = DListCreate();
	
	printf(KCYN"\n\nDestroy list test:\n"WHITE);

	if ( NULL != new_list )
	{
		printf(GREEN"\nSuccessfuly destroyed double linked list\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to destroy double linked list\n"WHITE);
		test_result=1;
	}

	printf(YELLOW"\nCombine this test with valgrind to assure"\
				 " no memory leaks\n");	

	DListDestroy(new_list);

	return test_result;
}
/******************************************************************************/
int DListInsert_test()
{
	int test_result = 0;
	int data = 1;
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nInsert list test:\n"WHITE);

	DListInsert(new_list, DListEnd(new_list), &data);

	if ( data == *(int*)DListGetData(DListBegin(new_list) ) )
	{
		printf(GREEN"\nSuccessfuly inserted \n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to insert\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/****************************************************************************/
int DListIsEmpty_test()
{
	int test_result = 0;
	int data = 1;
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nInsert list test:\n"WHITE);
	
	if ( DListIsEmpty(new_list) )
	{
		printf(GREEN"\nSuccessfuly returned list is empty \n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return list is empty\n"WHITE);
		test_result=1;
	}

	DListInsert(new_list, DListEnd(new_list), &data);

	if ( !DListIsEmpty(new_list) )
	{
		printf(GREEN"\nSuccessfuly returned list is not empty \n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return list is not empty\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListBegin_test()
{
	int test_result = 0;
	int data = 1;
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nBegin test\n"WHITE);
	
	if ( DListEnd(new_list) == DListBegin(new_list) )
	{
		printf(GREEN"\nSuccessfuly returned end for empty list\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return end for empty list\n"WHITE);
		test_result=1;
	}

	DListInsert(new_list, DListEnd(new_list), &data);

	if ( DListEnd(new_list) != DListBegin(new_list) )
	{
		printf(GREEN"\nSuccessfuly returned first element\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return first element\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListEnd_test()
{
	int test_result = 0;
	int data = 1;
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nEnd test\n"WHITE);

	DListInsert(new_list, DListEnd(new_list), &data);

	if ( 1 == *(int*)DListGetData(DListPrev(DListEnd(new_list) ) ) )
	{
		printf(GREEN"\nSuccessfuly returned End\n\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return End\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListNext_test()
{
	int test_result = 0;
	int data[] = {1, 2};
	dl_list_t *new_list = DListCreate();
	iterator_t test_itr = NULL;

	printf(KCYN"\n\nNext test\n"WHITE);

	test_itr = DListInsert(new_list, DListEnd(new_list), &data);

	if ( DListEnd(new_list) == DListNext(test_itr) )
	{
		printf(GREEN"\nSuccessfuly returned End as next\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return End as next\n"WHITE);
		test_result=1;
	}

	test_itr = DListInsert(new_list, DListEnd(new_list), data+1);

	if ( DListEnd(new_list) == DListNext(DListNext(test_itr) ) )
	{
		printf(GREEN"\nSuccessfuly returned Next element\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return next element\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListPrev_test()
{
	int test_result = 0;
	int data[] = {1, 2};
	dl_list_t *new_list = DListCreate();
	iterator_t test_itr = NULL;

	printf(KCYN"\n\nPrev test\n"WHITE);

	test_itr = DListInsert(new_list, DListEnd(new_list), &data);

	DListInsert(new_list, DListEnd(new_list), &data);

	if ( DListPrev(DListEnd(new_list)) == DListNext(test_itr) )
	{
		printf(GREEN"\nSuccessfuly returned previous element\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return previous element\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListGetData_test()
{
	int test_result = 0;
	int data = 1;
	dl_list_t *new_list = DListCreate();
	iterator_t test_itr = NULL;

	printf(KCYN"\n\nGet Data test\n"WHITE);

	test_itr = DListInsert(new_list, DListEnd(new_list), &data);

	if ( 1 == *(int*)DListGetData(test_itr) )
	{
		printf(GREEN"\nSuccessfuly returned data\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return data\n"WHITE);
		test_result=1;
	}
	
	DListDestroy(new_list);	

	return test_result;

}
/****************************************************************************/
int DListIsSameIterator_test()
{
	int test_result = 0;
	int data[] = {1, 2};
	dl_list_t *new_list = DListCreate();

	iterator_t test_itr1 = NULL;
	iterator_t test_itr2 = NULL;

	printf(KCYN"\n\nIs Same Iterator test\n"WHITE);

	test_itr1 = DListInsert(new_list, DListEnd(new_list), data);
	test_itr2 = DListInsert(new_list, DListEnd(new_list), data+1);

	if ( DListIsSameIterator(test_itr1, test_itr1) )
	{
		printf(GREEN"\nSuccessfuly returned Is same iterator\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return Is same iterator\n"WHITE);
		test_result=1;
	}
	
	if ( !(DListIsSameIterator(test_itr1, test_itr2)) )
	{
		printf(GREEN"\nSuccessfuly returned Is Not same iterator\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return Is Not same iterator\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListInsertAfter_test()
{
	int test_result = 0;
	int data[] = {1, 2};
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nInsert After test\n"WHITE);

	DListInsert(new_list, DListEnd(new_list), data);
	DListInsertAfter(new_list, DListBegin(new_list), data+1);

	if ( 2 == *(int*)DListGetData(DListNext(DListBegin(new_list))) )
	{
		printf(GREEN"\nSuccessfuly inserted data after\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to insert data after\n"WHITE);
		test_result=1;
	}


	DListDestroy(new_list);	

	return test_result;

}
/*****************************************************************************/
int DListRemove_test()
{
	int test_result = 0;
	int data[] = {1, 2};
	dl_list_t *new_list = DListCreate();
	iterator_t test_itr = NULL;

	printf(KCYN"\n\nRemove test\n"WHITE);

	test_itr = DListInsert(new_list, DListEnd(new_list), &data);

	DListInsert(new_list, DListEnd(new_list), data+1);

	DListRemove(test_itr);

	if ( 2 == *(int*)DListGetData(DListBegin(new_list)) )
	{
		printf(GREEN"\nSuccessfuly removed iterator\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to remove iterator\n"WHITE);
		test_result=1;
	}


	DListDestroy(new_list);	

	return test_result;

}
/*****************************************************************************/
int DListPushFront_test()
{
	int test_result = 0;
	int data[] = {1, 2};
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nPush Front test\n"WHITE);

	DListPushFront(new_list, &data);


	if ( 1 == *(int*)DListGetData(DListBegin(new_list)) )
	{
		printf(GREEN"\nSuccessfuly pushed front (first push)\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to push front (first push)\n"WHITE);
		test_result=1;
	}

	DListPushFront(new_list, &data[1]);

	if ( 2 == *(int*)DListGetData(DListBegin(new_list)) )
	{
		printf(GREEN"\nSuccessfuly pushed front (second push)\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to push front (second push)\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListPushBack_test()
{
	int test_result = 0;
	int data[] = {1, 2};
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nPush Front test\n"WHITE);

	DListPushBack(new_list, &data);


	if ( 1 == *(int*)DListGetData(DListPrev(DListEnd(new_list))) )
	{
		printf(GREEN"\nSuccessfuly pushed back (second push)\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to push back (second push)\n"WHITE);
		test_result=1;
	}

	DListPushBack(new_list, &data[1]);

	if ( 2 == *(int*)DListGetData(DListPrev(DListEnd(new_list))) )
	{
		printf(GREEN"\nSuccessfuly pushed back (second push)\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to push back (second push)\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}
/*****************************************************************************/
int DListPopFront_test()
{
	int test_result = 0;
	int data = 1;
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nPop Front test\n"WHITE);

	DListPushBack(new_list, &data);

	if( 1 == *(int*)DListPopFront(new_list) )
	{
		printf(GREEN"\nSuccessfuly popped front\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to pop front\n"WHITE);
		test_result=1;
	}

	if( NULL == DListPopFront(new_list) )
	{
		printf(GREEN"\nSuccessfuly popped front empty list\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to pop front empty list\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);

	return test_result;
}
/*****************************************************************************/
int DListPopBack_test()
{
	int test_result = 0;
	int data = 1;
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nPop Back test\n"WHITE);

	DListPushBack(new_list, &data);


	if ( 1 == *(int*)DListPopBack(new_list) )
	{
		printf(GREEN"\nSuccessfuly popped back\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to pop back\n"WHITE);
		test_result=1;
	}

	if ( NULL == DListPopBack(new_list) )
	{
		printf(GREEN"\nSuccessfuly popped back empty list\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to pop back empty list\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);

	return test_result;
}
/*****************************************************************************/
int DListFind_test()
{
	dl_list_t *new_list = DListCreate();
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 5};;

	DListPushBack(new_list, data);
	DListPushBack(new_list, (data+1));
	DListPushBack(new_list, (data+2));
	DListPushBack(new_list, (data+3));

	printf(KCYN"\n\nFind test\n"WHITE);

	if( 3 == *(int*)DListGetData(DListFind(DListBegin(new_list), DListEnd(new_list),
					 IsMatch, NULL, &data[2]) ) )
	{
		printf(GREEN"\nSuccessfuly found element\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to find element\n"WHITE);
		test_result=1;
	}

	if( NULL == (int*)(DListFind(DListBegin(new_list), DListEnd(new_list),
					 IsMatch, NULL, &data[4]) ))
	{
		printf(GREEN"\nSuccess: returned null when there is no match\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return null when there is not match\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);	

	return test_result;
}

int IsMatch(const void *data1, void *param, const void *data2)
{
	int is_match = 0;

	(void)param;

	if(*(int*)data1 == *(int*)data2)
	{
		is_match = 1;
	}

	return is_match;
}
/*****************************************************************************/
int DListCount_test()
{
	dl_list_t *new_list = DListCreate();
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 5};;

	printf(KCYN"\n\nCount test\n"WHITE);

	if( 0 == DListCount(new_list))
	{
		printf(GREEN"\nSuccess: 0 list is empty\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return 0: list is empty\n"WHITE);
		test_result=1;
	}

	DListPushBack(new_list, data);
	DListPushBack(new_list, (data+1));
	DListPushBack(new_list, (data+2));
	DListPushBack(new_list, (data+3));

	if( 4 == DListCount(new_list))
	{
		printf(GREEN"\nSuccess: returned list size is 4\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to return list size of 4\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);

	return test_result;
}
/****************************************************************************/
int Action(void *data, void *param)
{
	int result = 0;

	if( 8 != *(int*)data)
	{
		*(size_t*)data += *(size_t*)param;
	}
	else
	{
		result=1;
	}

	return result;
}

int DListForEach_test()
{
	int test_result = 0;
	int data[] = {1, 2, 3, 4, 8};
	int param = 1;
	dl_list_t *new_list = DListCreate();

	printf(KCYN"\n\nForEach test\n"WHITE);

	DListPushBack(new_list, data);
	DListPushBack(new_list, (data+1));
	DListPushBack(new_list, (data+2));
	DListPushBack(new_list, (data+3));
	

	if (( 0 == DListForEach(DListBegin(new_list), DListEnd(new_list), Action, 
																&param))&&
		( 2 ==*(int*)DListGetData(DListBegin(new_list)))&&
		( 3 ==*(int*)DListGetData(DListNext(DListBegin(new_list)))))
	{
		printf(GREEN"\nSuccess: All actions succesful\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed on an action\n"WHITE);
		test_result=1;
	}

	DListPushBack(new_list, (data+4));

	if (( 1 == DListForEach(DListBegin(new_list), DListEnd(new_list), Action, 
																&param))&&
		( 3 ==*(int*)DListGetData(DListBegin(new_list)))&&
		( 4 ==*(int*)DListGetData(DListNext(DListBegin(new_list))))&&
		( 8 ==*(int*)DListGetData(DListPrev(DListEnd(new_list)))))
	{
		printf(GREEN"\nSuccess: all actions done until fail\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed on 'all actions done until fail'\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);

	return test_result;															
}
/****************************************************************************/
int DListSpliceBefore_test()
{
	dl_list_t *new_list = DListCreate();
	dl_list_t *new_list2 = DListCreate();
	int test_result = 0;
	int data1[] = {1, 2, 3, 4, 5};
	int data2[] = {6, 7, 8};
	iterator_t begin = NULL;
	iterator_t where_to = NULL;

	printf(KCYN"\n\nSplice Before test\n"WHITE);

	DListPushBack(new_list, data1);
	DListPushBack(new_list, (data1+1));
	DListPushBack(new_list, (data1+2));
	DListPushBack(new_list, (data1+3));
	
	/*whereto = 5*/
	where_to = DListPushBack(new_list, (data1+4)); 

	/*begin= 2*/
	begin = DListPushBack(new_list2, (data2));
	DListPushBack(new_list2, (data2+1));
	DListPushBack(new_list2, (data2+2));

	/*we want 1  2 3 4 (6 7 8 ) 5*/
	DListSpliceBefore(where_to, begin, DListEnd(new_list2));

	if (( 8 == *(int*)DListGetData(DListPrev(DListPrev(DListEnd(new_list))))))
	{
		printf(GREEN"\nSuccessfuly spliced!\n"WHITE);

	}
	else
	{
		printf(RED"\nFailed to properly splice\n"WHITE);
		test_result=1;
	}

	DListDestroy(new_list);
	DListDestroy(new_list2);

	return test_result;
}



