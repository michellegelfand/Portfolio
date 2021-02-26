/**********************************************************************;
* Project           : Data Structures
*
* Program name      : singly_list_test.c
*
* Author            : Michelle Gelfand
*
* Date created      : 17.06.19
*
* Purpose           : This program provides the user with a singly 
*					  linked list data structure, and operations to store, 
*					  edit and access data in it.
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 19/06/2019       	  Michelle Gelfand           Olga K. *														  
**********************************************************************/


#include <stdio.h>/*printf*/
#include <stdlib.h>/*free*/

#include "singly_list.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"


sl_node_t *SListCreateNode_test(void *data, sl_node_t *next);
void SListFree_test(sl_node_t *head); 
void SListInsertAfter_test(sl_node_t *whereto_node, sl_node_t *new_node);
void SListInsertBefore_test(sl_node_t *whereto_node, sl_node_t *new_node);
void SListRemove_test(sl_node_t *node);
void SListRemoveAfter_test(sl_node_t *node);
int MockMatch(const void *data, void *param);
void SListFind_test(sl_node_t *head, is_match_t IsMatch, void *param );
void SListFind_fail_test(sl_node_t *head, is_match_t IsMatch, void *param );
int MockAction(void *data, void *param);
void SListForEach_test(sl_node_t *head, action_t Action, void *param);
void SListForEach_fail_test(sl_node_t *head, action_t Action, void *param);
int MockAction_Fail(void *data, void *param);
void SListFlip_test(sl_node_t *head);
void PrintSList(sl_node_t *head);
void SListIntersection_test(sl_node_t *head1, sl_node_t *head2, sl_node_t* target_node);
void SListIntersection_fail_test(sl_node_t *head1, sl_node_t *head2);
void SListCount_test(const sl_node_t *head);
void SListHasLoop_no_loop_test(const sl_node_t *head);
void SListHasLoop_yes_loop_test(const sl_node_t *head);

int main()
{
	/*init nodes*/
	int data[] = {1, 2, 3, 4, 5, 6, 7, 88}; 
	int param[] = {1,2};

	sl_node_t* new_node = NULL; 
	sl_node_t* new_node2 = SListCreateNode(&data[1], NULL);
	sl_node_t* new_node3 = SListCreateNode(&data[2], NULL);
	sl_node_t* new_node4 = SListCreateNode(&data[3], NULL);
	sl_node_t* new_node5 = SListCreateNode(&data[4], NULL);
	sl_node_t* new_node6 = SListCreateNode(&data[5], NULL);

	sl_node_t* foreach_node = SListCreateNode(&data[0], NULL);
	sl_node_t* foreach_node2 = SListCreateNode(&data[1], NULL);
	sl_node_t* foreach_node3 = SListCreateNode(&data[2], NULL);
	
	
	foreach_node -> next = foreach_node2;
	foreach_node2 -> next = foreach_node3;
	
	/*test calls*/
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nCREATE node test:\n\n"WHITE);
	printf(BLUE"\n\nstandard create test: expected result success\n\n"WHITE);
	new_node = SListCreateNode_test(data, NULL);

	/*create*/
	printf(BLUE"\nINSERT 2 AFTER 1 \n"WHITE);
	printf(BLUE"\nexpected: 1 address 2 null\n"WHITE);
	SListInsertAfter_test(new_node, new_node2);
	
	/*insert after*/
	printf(BLUE"\nINSERT 3 AFTER 1\n"WHITE);
	printf(BLUE"\nexpected: 1 address 3 address 2 null\n"WHITE);
	SListInsertAfter_test(new_node, new_node3);

	printf(BLUE"\nINSERT  4 AFTER 1\n"WHITE);
	printf(BLUE"\nexpected: 1 address 4 address 3 address 2 null\n"WHITE);
	SListInsertAfter_test(new_node, new_node4);
	
	/*insert before*/
	printf(BLUE"\nINSERT 5 BEFORE 1\n"WHITE);
	printf(BLUE"\nexpected 5 1 4 3 2 \n"WHITE);
	SListInsertBefore_test(new_node, new_node5);
	printf(BLUE"\nINSERT 6 BEFORE 4\n"WHITE);
	printf(BLUE"\nexpected 5 1 6 4  3 2 \n"WHITE);
	SListInsertBefore_test(new_node4, new_node6);

	/*remove*/
	printf(BLUE"\n\nremove 6\n\n"WHITE);
	printf(BLUE"\nexpected 5 1 4 3 2 \n"WHITE);
	SListRemove_test(new_node6);

	/*remove after*/
	printf(BLUE"\n\nremove 3\n\n"WHITE);
	printf(BLUE"\nexpected 5 6 3 2 \n"WHITE);
	SListRemoveAfter_test(new_node4);

	/*find*/
	printf(BLUE"\n\nsuccesfuly FIND 2\n\n"WHITE);
	SListFind_test(new_node, MockMatch, new_node2->data);

	printf(BLUE"\n\nFail to find 88\n\n"WHITE);
	SListFind_fail_test(new_node, MockMatch, &data[7]);

	/*foreach*/	
	printf("\n\nNew Linked List:\n");
	PrintSList(foreach_node);

	SListForEach_test(foreach_node, MockAction, param);

	printf(BLUE"\n\nFail at 3:\n"WHITE);
	SListForEach_fail_test(foreach_node, MockAction_Fail, param);

	/*intersection*/
	SListIntersection_fail_test(foreach_node, new_node);
	
	foreach_node3 -> next = new_node4;

	printf("\n\nfirst list:\n");
	PrintSList(foreach_node);
	printf("\n\nsecond list:\n");
	PrintSList(new_node);

	SListIntersection_test(foreach_node, new_node, new_node4);

	/*count*/
	SListCount_test(new_node);

	/*flip*/
	PrintSList(foreach_node);
	SListFlip_test(foreach_node);

	/*has loop*/
	SListHasLoop_no_loop_test( new_node);

	/*(insert loop)*/
	new_node4 -> next = new_node;
    SListHasLoop_yes_loop_test( new_node);

	
	

	/*cleanup*/
	free(new_node);
	free(new_node2);
	free(new_node3);
	free(new_node4);
	free(new_node5); 
	free(new_node6);

	free(foreach_node); 
	free(foreach_node2); 
	free(foreach_node3);

	return 0;
}

sl_node_t *SListCreateNode_test(void *data, sl_node_t *next)
{
	sl_node_t* new_node = SListCreateNode(data, next);
	
	if ( NULL != new_node )
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

	printf(YELLOW"\n\nCombine this test with valgrind\n\n"WHITE);
 
	return new_node;

}

void SListInsertAfter_test(sl_node_t *whereto_node, sl_node_t *new_node)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nInsert after test:\n\n"WHITE);

	SListInsertAfter(whereto_node, new_node);

	if ( NULL != new_node )
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
}

void SListInsertBefore_test(sl_node_t *whereto_node, sl_node_t *new_node)
{
	printf(YELLOW"\n\nINSERT BEFORE test:\n\n"WHITE);

	SListInsertBefore(whereto_node, new_node);

	/*if returns address in next*/
	if (whereto_node -> next == new_node )
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
}

void SListFree_test(sl_node_t *head)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nFree node test:\n\n"WHITE);

	SListFree(head);

	printf(YELLOW"\n\nCombine this test with valgrind\n\n"WHITE);

}	

void SListRemove_test(sl_node_t *node)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nREMOVE node test:\n\n"WHITE);
	
	if (node -> next == SListRemove(node))
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

}

void SListRemoveAfter_test(sl_node_t *node)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nREMOVE After test:\n\n"WHITE);
	
	if (node -> next == SListRemoveAfter(node))
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}


}

int MockMatch(const void *data, void *param)
{
	int result = 0;

	if ( *(int*)param == *(int*)data)
	{
		result = 1;
	}
	return result;	

}

void SListFind_test(sl_node_t *head, is_match_t IsMatch, void *param )
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nFind test:\n\n"WHITE);
	
	SListFind(head, IsMatch, param) ? printf(GREEN"\nSUCCESS\n"WHITE) : \
	printf(RED"\n!! FAILED !!\n"WHITE);




}
void SListFind_fail_test(sl_node_t *head, is_match_t IsMatch, void *param )
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nfail to Find test:\n\n"WHITE);
	
	SListFind(head, IsMatch, param) ? 
	printf(RED"\n!! FAILED !!\n"WHITE) : printf(GREEN"\nSUCCESS\n"WHITE);

}

int MockAction(void *data, void *param)
{
	*(int*)data = *(int*)data + *(int*)param; 

	/*Success*/
	return 0;
}

int MockAction_Fail(void *data, void *param)
{
	int result = 0;
	
	if ( 3 == *(int*)data )
	{
		result = -1;
	}
	else
	{
		*(int*)data = *(int*)data + *(int*)param; 
	}

	/*Success*/
	return result;
}

void SListForEach_test(sl_node_t *head, action_t Action, void *param)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nSuccesful Action test:\n\n"WHITE);

	if ( 0 == SListForEach(head, Action, param))
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
}
void SListForEach_fail_test(sl_node_t *head, action_t Action, void *param)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nFailed Action test:\n\n"WHITE);

	if ( 0 != SListForEach(head, Action, param))
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
}
void SListFlip_test(sl_node_t *head)
{
	sl_node_t* cmp_vals = 0;

	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nFlip Test:\n\n"WHITE);

	cmp_vals = SListFlip(head);
	cmp_vals = cmp_vals -> next;

	if ( 6 == *(int*)cmp_vals -> data)
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
}

void SListIntersection_fail_test(sl_node_t *head1, sl_node_t *head2)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nINTERSECTION (no intersection) test:\n\n"WHITE);

	if ( NULL == (SListIntersection(head1, head2)) )
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
}

void SListIntersection_test(sl_node_t *head1, sl_node_t *head2, sl_node_t* target_node)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nINTERSECTION (found) test:\n\n"WHITE);

	if ( target_node == (SListIntersection(head1, head2)) )
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

}
void SListCount_test(const sl_node_t *head)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nCOUNT test:\n\n"WHITE);

	if ( 4 == SListCount(head))
	{
		printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}

}
void SListHasLoop_no_loop_test( const sl_node_t *head)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nHas Loop RETURN NO LOOP test:\n\n"WHITE);

	if ( 0 == SListHasLoop(head) )
	{
	printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
	

}
void SListHasLoop_yes_loop_test(const sl_node_t *head)
{
	printf(YELLOW"\n\n**************************************\n\n"WHITE);
	printf(YELLOW"\n\nHas Loop FIND LOOP test:\n\n"WHITE);

	if ( 1 == SListHasLoop(head) )
	{
	printf(GREEN"\nSUCCESS\n"WHITE);
	}
	else
	{
		printf(RED"\n!! FAILED !!\n"WHITE);
	}
	
}
