/**********************************************************************;
* Project           : Data Structures
*
* Program name      : singly_list.c
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

#include <stdlib.h>/*malloc*/

#include "singly_list.h"

#ifndef NDEBUG

	#include <stdio.h>

	void PrintSList(sl_node_t *head)
	{
		sl_node_t* original_head = head;

		printf("\nData:          nextptr:          this address: \n");	

		while ( NULL != original_head->next )
		{
			printf("\n%-10d     %-14p     %-14p \n", 
			*(int* )(original_head->data), 
			(void*)original_head->next,
			(void*)original_head);

			original_head = original_head->next;
		}

		printf("\n%-10d     %-14p     %-14p\n", *(int*)(original_head->data),
		(void*)original_head->next, (void*)original_head);
	}
#else

	#define PrintSList(head)

#endif /*NDEBUG*/

sl_node_t *SListCreateNode(void *data, sl_node_t *next)
{
	sl_node_t *new_node = (sl_node_t*)malloc(sizeof(sl_node_t));
	
	if (NULL != new_node)
	{
		new_node -> data = data;
		new_node -> next = next;
	}

	return new_node;
}
/*----------------------------------------------------------------------------*/

void SListFree(sl_node_t *head)
{
	sl_node_t* next_head = head -> next;

	/*we are assuming here the user knows not to enter a looped list
	it is their responsibility*/
	while (NULL != head -> next)
	{
		next_head = head ->next;
		free(head);		
		head = next_head;	
	}

	/*for last node for which next = null*/
	free(head);	
	head = NULL;
}

sl_node_t *SListInsertAfter(sl_node_t *whereto_node, sl_node_t *new_node)
{
	/*save whereto_nodes' next*/
	sl_node_t* original_next = whereto_node->next;
	
	whereto_node->next = new_node; 
	
	new_node->next = original_next;

	/*PrintSList(whereto_node);*/
	
	return new_node;
	
}

/*----------------------------------------------------------------------------*/
sl_node_t *SListInsertBefore(sl_node_t *whereto_node, sl_node_t *new_node)
{
	/*save old nodes' original data and ptr*/
	void* whereto_data = whereto_node->data; 
	
	/*swap data vals*/
	whereto_node->data = new_node->data; 
 	new_node -> data = whereto_data;
	
	/*swap nexts*/
	new_node->next = whereto_node->next;
	whereto_node->next = new_node ;  
	
	/*PrintSList(whereto_node);*/

	return whereto_node;	
}

/*----------------------------------------------------------------------------*/
sl_node_t *SListRemove(sl_node_t *node)
{
	/*save detached node to return*/
	sl_node_t* detached_node = node->next;

	/*save node data*/
	void* detached_data = node->data;

	/*take next node's data*/
	node->data = node->next->data;
	node->next = node->next->next;

	detached_node->next = NULL;	

	/*paste data*/
	detached_node->data = detached_data;

	/*PrintSList(node);*/

	return detached_node;
}
/*----------------------------------------------------------------------------*/
          
sl_node_t *SListRemoveAfter(sl_node_t *node)
{
	/*save detached node to return*/
	sl_node_t* detached_node = node->next;

	node -> next = detached_node->next;

	detached_node->next = NULL;	

	/*PrintSList(node);*/

	return detached_node;
}

/*----------------------------------------------------------------------------*/
size_t SListCount(const sl_node_t *head)
{
	size_t count = 0;

	while( NULL != head )
	{
		++count;
		head = head->next;
	}
	
	return count;
}
/*----------------------------------------------------------------*/
sl_node_t *SListFind(sl_node_t *head, is_match_t IsMatch, void *param )
{
	sl_node_t* result = NULL;

	while ( NULL != head->next)
	{
		if ( IsMatch(head->data, param) )
		{
			result = head;
			break;
		}
		head = head ->next;
	}

	/*'while' above checks until second to last to avoid seg fault*/
	/*if no result yet check one more time*/
	if (NULL == result)
	{
		if ( IsMatch(head->data, param) )
		{
			result = head;
		}
	}
	return result;
}

/*----------------------------------------------------------------------------*/                                                            
int SListForEach(sl_node_t *head, action_t Action, void *param)
{
	int result = 0;
	sl_node_t* move_head = head;
	while ( NULL != move_head)
	{
		if ( -1 == Action(move_head->data, param) )
		{
			result = -1;
			break;
		}
		move_head = move_head->next;
	}
	
	/*PrintSList(head);*/

	return result;
}

/*----------------------------------------------------------------------------*/
sl_node_t *SListFlip(sl_node_t *head)
{
	sl_node_t *previous_node = NULL;
	sl_node_t *next_node = head->next;

	while (NULL != head->next)
	{	
		head->next = previous_node;
		
		previous_node = head;
		head = next_node;
		next_node = head->next;
	}

	/*point final (head node)*/
	head -> next = previous_node;

	/*PrintSList(head);*/
	return head;
}

/*----------------------------------------------------------------------------*/
sl_node_t *SListIntersection(sl_node_t *head1, sl_node_t *head2)
{
	/*count length of linked lists*/
	size_t count1 = SListCount(head1);
	size_t count2 = SListCount(head2);
	
	/*difference is length between lists*/
	size_t len_diff = 0;

	/*find longer list and advance to same starting point*/
	if ( count2 > count1 )
	{
		len_diff = count2 - count1;
		
		while (len_diff)
		{
			head2 = head2->next;
			--len_diff;
		}
		
	}
	else
	{
		len_diff = count1 - count2;
		
		while (len_diff)
		{
			head1 = head1->next;
			--len_diff;
		}
		
	}
	/*here they are same length*/
	while ( ( head2 != head1 )  && head2 )
	{
		head2 = head2 -> next;
		head1 = head1 -> next;
	}

	return head2;
}

/*----------------------------------------------------------------------------*/	   
 
int SListHasLoop(const sl_node_t *head)
{
	int is_loop = 0;

	/*can change pointer, not pointers' content*/
	const sl_node_t *tortoise = head;
	const sl_node_t *hare = head->next;
	
	/*hare will arrive faster to null*/
	while ( hare )
	{
		/*big hop*/
		hare = hare->next;

		if (hare)
		{
			hare = hare->next;
		}

		/*small hop*/
		tortoise = tortoise->next;
		
		if( tortoise == hare)
		{
			is_loop = 1;
			break;
		}
	}
	return is_loop;
}
