/**********************************************************************;
* Project           : Data Structures
*
* Program name      : bst.c
*
* Author            : Michelle Gelfand
*
* Date created      : 19.07.19
*
* Purpose           : This program provides the user
					  with a binary search tree
*
* Version           : 1.3
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 22/07/2019       	  Michelle Gelfand           Saar Y. *														  
*******************************************************************/

#include <stdio.h>

#include "bst.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"

void InsertRemoveTest();
void ForEachCountTest();
void FindEndNextPrevTest();
void BeginEndSameEmpty();

int Compare(const void *data1, const void *data2, void *param)
{
	int result = 0;
	(void)param;

	if(*(int*)data1 > *(int*)data2)
	{
		result = 1;
	}	 
	else if (*(int*)data1 < *(int*)data2)
	{
		result = -1;
	}

	return result;
}

int main()
{
	InsertRemoveTest();
	ForEachCountTest();
	FindEndNextPrevTest();
	BeginEndSameEmpty();

	return 0;
}

void InsertRemoveTest()
{
	bst_t *tree = BstCreate(Compare, NULL);

	bst_iterator ee =NULL;
	bst_iterator ff =NULL;

	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int f = 13;
	int g = 17;
	int h = 11;

	if(tree)
	{
		printf(GREEN"\n\ncreated tree\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! CREATE TREE HAS FAILED !!!\n\n"WHITE);
	}

	BstInsert(tree, &d);

	if( 4 == *(int*)BstGetData(BstBegin(tree)))
	{
		printf(GREEN"\n\nfirst insertion\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! INSERTION 1 HAS FAILED !!!\n\n"WHITE);
	}

	BstInsert(tree, &b);
	if( 2 == *(int*)BstGetData(BstBegin(tree)))
	{
		printf(GREEN"\n\nsecond insertion\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! INSERTION 2 HAS FAILED !!!\n\n"WHITE);
	}

	BstInsert(tree, &c);

	if( 3 == *(int*)BstGetData(BstNext(BstBegin(tree))))
	{
		printf(GREEN"\n\nthird insertion\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! INSERTION 3 HAS FAILED !!!\n\n"WHITE);
	}

	ee=BstInsert(tree, &e);
	ff=BstInsert(tree, &f);
	BstInsert(tree, &g);
	BstInsert(tree, &h);

	BstRemove(tree, ff);

	if(  11 == *(int*)BstGetData(BstNext(ee)))  	
	{
		printf(GREEN"\n\ntwo child removal\n\n"WHITE);
		printf(GREEN"\n\nend works\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! 2 child removal HAS FAILED !!!\n\n"WHITE);
		printf(GREEN"\n\npossible problem in end\n\n"WHITE);
	}
	
	BstDestroy(tree);

	printf(BLUE"\n\n combine destroy test with valgrind\n\n"WHITE);

}

void ForEachCountTest()
{
	bst_t *tree = BstCreate(Compare, NULL);

	int a = 1;
	int e = 5;
	int f = 13;
	

	if( 0 == BstCount(tree))
	{
		printf(GREEN"\n\ncount empty\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! count empty HAS FAILED !!!\n\n"WHITE);
	}

	BstInsert(tree, &e);
	BstInsert(tree, &f);
	BstInsert(tree, &a);

	if( 3 == BstCount(tree))
	{
		printf(GREEN"\n\ncount full\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! count full HAS FAILED !!!\n\n"WHITE);
	}
	if( 3 == BstCount(tree))
	{
		printf(GREEN"\n\nforeach succesful\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n oh noes !!! foreach HAS FAILED !!!\n\n"WHITE);
	}

	BstDestroy(tree);
}
void FindEndNextPrevTest()
{
	bst_t *tree = BstCreate(Compare, NULL);

	int a = 1;
	int e = 5;
	int f = 13;

	BstInsert(tree, &e);
	BstInsert(tree, &a);
	BstInsert(tree, &f);

	if( 1 == *(int*)BstGetData(BstFind(tree, &a)))
	{
		printf(GREEN"\n\n Get data successful \n find succesful\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n Get data failed \n find find\n\n"WHITE);
	}

	if(5==*(int*)BstGetData(BstNext(BstFind(tree, &a))))
	{
		printf(GREEN"\n\n next succesful\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n next failed\n\n"WHITE);
	}

	if(1==*(int*)BstGetData(BstPrev(BstNext(BstFind(tree, &a)))))
	{
		printf(GREEN"\n\n prev succesful\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n prev failed\n\n"WHITE);
	}

	BstDestroy(tree);
}	
void BeginEndSameEmpty()
{
	bst_iterator aa = NULL;
	bst_iterator bb = NULL;

	int a = 1;
	int e = 5;
	int f = 13;

	bst_t *tree = BstCreate(Compare, NULL);

	

	if(BstIsEmpty(tree))
	{
		printf(GREEN"\n\n return empty\n\n"WHITE);
	}
	else 
	{
		printf(RED"\n\nempty failed\n\n"WHITE);
	}

	aa= BstInsert(tree, &e);
	bb = BstInsert(tree, &a);
	BstInsert(tree, &f);

	if(!BstIsEmpty(tree))
	{
		printf(GREEN"\n\n empty success\n\n"WHITE);
	}
	else 
	{
		printf(RED"\n\nempty failed\n\n"WHITE);
	}
	
	if(!BstIsSameIterator(aa,bb))
	{
		printf(GREEN"\n\n is same success\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n is same failure\n\n"WHITE);
	}

	if( 1 == *(int*)BstGetData(BstBegin(tree)))
	{
		printf(GREEN"\n\n begin success\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\n begin fail\n\n"WHITE);
	}

	BstDestroy(tree);
}

