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

#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "doubly_list.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

typedef struct dl_node dl_node_t;

struct dl_node
{
	void *data;
	dl_node_t *next;
	dl_node_t *prev;
};

struct dl_list
{
	dl_node_t head;
	dl_node_t tail;
};

/******************************************************************************/
static dl_node_t* _CreateNode(void* data)
{
	dl_node_t *new_node = (dl_node_t*)malloc(sizeof(dl_node_t));

	new_node->data = data;

	return new_node;
}
/*----------------------------------------------------------------------------*/
dl_list_t *DListCreate(void)
{
	dl_list_t *new_list = (dl_list_t*)malloc(sizeof(dl_list_t)); 
	
	if(new_list)
	{
		new_list->head.data = (void*)0xDEADBEEF;
		new_list->tail.data = (void*)0xDEADBEEF;
		
		/*point head and tail to eachother*/
		new_list->head.next = &new_list->tail;
		new_list->tail.prev = &new_list->head;		

		/*point tail to self for convenience in future funcs*/
		new_list->head.prev = NULL;
		new_list->tail.next = &new_list->tail;
	}

	return new_list;
}
/*----------------------------------------------------------------------------*/
void DListDestroy(dl_list_t *dl_list)
{
	iterator_t node_to_remove = NULL;
	iterator_t list_end = NULL;

	assert(dl_list);

	node_to_remove = DListBegin(dl_list);

	list_end = DListEnd(dl_list);

	/*while destroyer is not on tail*/ 
	while( !(DListIsSameIterator( node_to_remove , list_end) ) ) 
	{
		/*func remove returns iterator to next element*/
		node_to_remove = DListRemove(node_to_remove);
	}

	free(dl_list);

	node_to_remove = NULL;
	dl_list = NULL;
}
/*----------------------------------------------------------------------------*/
int CountAction(void *data, void *param)
{
	(void)data;
	++*(size_t*)param;

	return 0;
}

size_t DListCount(const dl_list_t *dl_list)
{
	size_t count = 0;

	assert(dl_list);
	
	DListForEach(DListBegin(dl_list), DListEnd(dl_list), CountAction, &count);
		
	return count;															
}

/*----------------------------------------------------------------------------*/ 
int DListIsEmpty(const dl_list_t *dl_list)
{
	assert(dl_list);

	return !!(dl_list->head.next == &dl_list->tail);	
}
/******************************************************************************/ 
iterator_t DListBegin(const dl_list_t *dl_list)
{
	assert(dl_list);

	return dl_list->head.next;
}
/*----------------------------------------------------------------------------*/
iterator_t DListEnd(const dl_list_t *dl_list)
{
	assert(dl_list);

	return (iterator_t)&dl_list->tail;
}
/*---------------------------------------------------------------------------*/
iterator_t DListNext(const iterator_t iterator)
{
	assert(iterator);

	return iterator->next;
}

/*----------------------------------------------------------------------------*/
iterator_t DListPrev(const iterator_t iterator)
{
	assert(iterator);

	return iterator->prev;
}

/*----------------------------------------------------------------------------*/

void *DListGetData(const iterator_t iterator)
{
	assert(iterator);

	return iterator->data;
}
/*--------------------------------------------------------------------------*/

int DListIsSameIterator(const iterator_t iterator1, const iterator_t iterator2)
{
	assert(iterator1);
	assert(iterator2);

	return !!(iterator1 == iterator2);
}

/*----------------------------------------------------------------------------*/   
iterator_t DListInsert(dl_list_t *dl_list, iterator_t iterator, void *data)
{
	iterator_t return_itr = &dl_list->tail;
	dl_node_t *insert_node = NULL; 
	iterator_t prev_node = NULL;
	
	assert(dl_list);
	assert(iterator);

	insert_node = _CreateNode(data);
	
	if(insert_node)
	{
		prev_node = iterator->prev;	
		prev_node->next = insert_node;

		insert_node->prev = prev_node;
		insert_node->next = iterator;

		iterator->prev = insert_node;

		return_itr = insert_node;
	}

	return return_itr;
}
/*----------------------------------------------------------------------------*/
iterator_t DListInsertAfter(dl_list_t *dl_list, iterator_t iterator, void *data)
{
	assert(dl_list);
	assert(iterator);
	
	return DListInsert(dl_list ,DListNext(iterator), data );
}
/*----------------------------------------------------------------------------*/
iterator_t DListRemove(iterator_t iterator)
{
	iterator_t return_next = NULL;

	assert(iterator);

	return_next = iterator->next;

	iterator->prev->next = iterator->next;
	iterator->next->prev = iterator->prev;

	iterator->next = NULL;
	iterator->prev = NULL;
	iterator->data = NULL;

	free(iterator);

	return return_next;
}
/*----------------------------------------------------------------------------*/
iterator_t DListPushFront(dl_list_t *dl_list, void *data)
{
	assert(dl_list);
	
	return ( DListInsert(dl_list, DListBegin(dl_list), data) );
}
/*----------------------------------------------------------------------------*/
iterator_t DListPushBack(dl_list_t *dl_list, void *data)
{
	assert(dl_list);
	
	return ( DListInsert(dl_list, DListEnd(dl_list), data) );
}

/*---------------------------------------------------------------------------*/
void *DListPopFront(dl_list_t *dl_list)
{
	iterator_t to_pop = NULL;

	/*if list is empty will return this null*/
	void *to_pop_data = NULL;

	assert(dl_list);

	to_pop = DListBegin(dl_list);
	
	/*if list not empty*/
	if( !( DListIsEmpty(dl_list) ) )
	{
		to_pop_data = DListGetData(to_pop);
		DListRemove(to_pop);
	}
	
	return to_pop_data;
}

/*----------------------------------------------------------------------------*/
void *DListPopBack(dl_list_t *dl_list)
{
	iterator_t to_pop = NULL;

	/*if list is empty will return this null*/
	void *to_pop_data = NULL;

	assert(dl_list);

	/*if list not empty*/
	if( !( DListIsEmpty(dl_list) ) )
	{
		/*to_pop = element before end*/
		to_pop = DListPrev( DListEnd( dl_list ) );

		to_pop_data = DListGetData(to_pop);
		DListRemove(to_pop);
	}
	return to_pop_data;
}

/*--------------------------------------------------------------------------*/                                         
int DListForEach(iterator_t begin, iterator_t end, action_t Action, 
																void *param)
{
	int status = 0;	
	
	/*just for readability*/
	iterator_t current = begin;

	assert(begin);
	assert(end);

	/*else will return success without entering while*/
	assert(Action);

	while( ( 0 == status )&&( end != current )  )
	{
		status = Action(DListGetData(current), param);
		
		current = DListNext(current);
	}

	return status;
}

/*------------------------------------------------------------------------*/
iterator_t DListFind(iterator_t begin, iterator_t end,
					 ismatch_t IsMatch, void *param, const void *data2)
{
	int is_found = 0;

	/*just for readability*/
	iterator_t current = begin;

	iterator_t found_element = NULL;

	assert(begin);
	assert(end);
	assert(IsMatch);

	while(  ( !is_found ) && ( !( DListIsSameIterator(current, end) ) ) )
	{
		is_found = IsMatch(DListGetData(current), param, data2);
		
		current = DListNext(current);	
	}

	if(is_found)
	{
		found_element = DListPrev(current);
	}

	return found_element;
}
/*---------------------------------------------------------------------------*/
void DListSpliceBefore( iterator_t where_to, 
							  iterator_t begin, 
							  iterator_t end )
{	
	/*i used 2 extra vars, for readaility*/
	iterator_t before_where_to = NULL;
	iterator_t before_end = NULL;
	iterator_t before_begin = NULL;

	assert(where_to);
	assert(begin);
	assert(end);

	if (begin != end)
	{
		/*saving iterators to assign new pointers*/
		before_where_to = DListPrev(where_to);
		before_end = DListPrev(end);
		before_begin = DListPrev(begin);

		/*connect before_where_to before begin*/
		before_where_to->next = begin;
		begin->prev = before_where_to;
		
		/*connect before_end before where_to*/
		before_end->next = where_to;
		where_to->prev = before_end;

		/*reconnect spliced chain without removed nodes*/
		before_begin->next = end;
		end->prev = before_begin;	
	}
}

/*----------------------------------------------------------------------------*/
 
 
