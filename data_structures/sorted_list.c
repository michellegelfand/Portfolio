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



#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/

#include "doubly_list.h"
#include "sorted_list.h"

struct sort_list
{
	dl_list_t *dl_list;
	sort_list_isbefore_t IsBefore;
};

/****************************************************************************/
sort_list_t *SortListCreate(sort_list_isbefore_t IsBefore)
{
	sort_list_t *new_list = NULL;
	
	assert(IsBefore);

	new_list = (sort_list_t*)malloc(sizeof(sort_list_t));

	if(new_list)
	{
		new_list->dl_list = DListCreate();
	
		if(new_list->dl_list)
		{
			new_list->IsBefore = IsBefore;	
		}
		else
		{
			new_list->IsBefore = NULL;

			free(new_list);

			new_list = NULL;
		}
	}

	return new_list;
}
/*---------------------------------------------------------------------------*/
void SortListDestroy(sort_list_t *sort_list)
{
	assert(sort_list);

	DListDestroy(sort_list->dl_list);

	sort_list->IsBefore = NULL;

	free(sort_list);

	sort_list = NULL;
}
/*----------------------------------------------------------------------------*/
size_t SortListCount(const sort_list_t *sort_list)
{
	sort_list_iter_t counter = {0};
	sort_list_iter_t end = {0};
	size_t count = 0;	
	
	assert(sort_list);

	counter = SortListBegin(sort_list);
	end = SortListEnd(sort_list);
	
	while(end.element != counter.element)
	{
		++count;
		counter = SortListNext(counter);	
	}

	return count;
}
/*----------------------------------------------------------------------------*/ 
int SortListIsEmpty(const sort_list_t *sort_list)
{
	assert(sort_list);
	
	return ( !!( SortListBegin(sort_list).element == 
				 SortListEnd(sort_list).element ) );
}

/*----------------------------------------------------------------------------*/
sort_list_iter_t SortListBegin(const sort_list_t *sort_list)
{
	sort_list_iter_t list_begin = {0};

	assert(sort_list);

	list_begin.element = (void*)DListBegin(sort_list->dl_list);

	return list_begin;
}
/*---------------------------------------------------------------------------*/
sort_list_iter_t SortListEnd(const sort_list_t *sort_list)
{
	sort_list_iter_t list_end = {0};

	assert(sort_list);

	list_end.element = (void*)DListEnd(sort_list->dl_list);

	return list_end;
}
/*----------------------------------------------------------------------------*/
sort_list_iter_t SortListNext(sort_list_iter_t iterator)
{
	sort_list_iter_t next_element = {0};

	assert(iterator.element);
	
	next_element.element = (void*)DListNext(iterator.element); 

	return next_element;
}
/*----------------------------------------------------------------------------*/
sort_list_iter_t SortListPrev(sort_list_iter_t iterator)
{
	sort_list_iter_t prev_element = {0};

	assert(iterator.element);
	
	prev_element.element = (void*)DListPrev(iterator.element); 

	return prev_element;
}
/*---------------------------------------------------------------------------*/
void *SortListGetData(sort_list_iter_t iterator)
{
	assert(iterator.element);

	return (DListGetData((iterator_t)(iterator.element)));
}
/*----------------------------------------------------------------------------*/
int SortListIsSameIterator(sort_list_iter_t iterator1, 
												  sort_list_iter_t iterator2)
{
	assert(iterator1.element);
	assert(iterator2.element);

	return ( !!(iterator1.element == iterator2.element));
}
/*--------------------------------------------------------------------------*/
sort_list_iter_t SortListInsert(sort_list_t *sort_list, void *data)
{
	sort_list_iter_t find_where_insert = {0};
	sort_list_iter_t end = {0};

	sort_list_iter_t new_element = {0};	
	
	assert(sort_list);

	find_where_insert = SortListBegin(sort_list);
	end = SortListEnd(sort_list); 	

	/*advance find_where_insert until IsBefore returns >= 0 */
	while( (end.element != find_where_insert.element) && 
	(0 >= sort_list->IsBefore(SortListGetData(find_where_insert), data) ) )
	{
		find_where_insert = SortListNext(find_where_insert);
	} 

	new_element.element = (void*)DListInsert(sort_list->dl_list, 
						  (iterator_t)find_where_insert.element, data);	

	return new_element; 
}
/*--------------------------------------------------------------------------*/

sort_list_iter_t SortListRemove(sort_list_iter_t iterator)
{
	sort_list_iter_t next_element =  {0};

	assert(iterator.element);

	next_element.element = (void*)DListRemove(iterator.element);

	return next_element;
}
/*---------------------------------------------------------------------------*/
void *SortListPopFront(sort_list_t *sort_list)
{
	void* removed_data = NULL;

	assert(sort_list);

	
	if (!SortListIsEmpty(sort_list))
	{	
		removed_data = SortListGetData(SortListBegin(sort_list));
		
		SortListRemove(SortListBegin(sort_list));
	}

	return removed_data;
}
/*---------------------------------------------------------------------------*/

void *SortListPopBack(sort_list_t *sort_list)
{
	void* removed_data = NULL;

	assert(sort_list);

	if (!SortListIsEmpty(sort_list))
	{	
		removed_data = SortListGetData(SortListPrev(SortListEnd(sort_list)));
		
		SortListRemove(SortListPrev(SortListEnd(sort_list)));
	}

	return removed_data;
}
/*------------------------------------------------------------------*/                                                  
int SortListForEach(sort_list_iter_t begin, sort_list_iter_t end,
									    sort_list_action_t Action, void *param)
{
	sort_list_iter_t current_node = {0};
	int action_result = 0;

	assert(begin.element);
	assert(end.element);
	assert(Action);
	
	current_node = begin;

	while((end.element != current_node.element) && ( 0 == action_result))
	{
		action_result = Action(SortListGetData(current_node), param);

		current_node = SortListNext(current_node);
	}

	return action_result;
}
/*---------------------------------------------------------------------------*/
sort_list_iter_t SortListFind(sort_list_iter_t begin, sort_list_iter_t end,
				 sort_list_ismatch_t IsMatch, void *param, const void *data2)
{
	int found = 0;
	sort_list_iter_t finder = {0};

	assert(begin.element);
	assert(end.element);
	assert(IsMatch);
	assert(data2);

	finder = begin;

	while((finder.element != end.element) && ( !found ) )
	{
		found = IsMatch(SortListGetData(finder), param, data2);
		
		finder = SortListNext(finder);
	}

	if(found)
	{
		finder = SortListPrev(finder);
	}

	return finder;
}
/*---------------------------------------------------------------------------*/
sort_list_iter_t SortListFindBySortKey(sort_list_t *sort_list,
						sort_list_comp_t IsBefore, const void *data)
{
	int found = -1;
	sort_list_iter_t finder = {0};
	sort_list_iter_t end = {0};

	assert(sort_list);
	assert(data);

	finder = SortListBegin(sort_list);
	end = SortListEnd(sort_list);

	while((finder.element != end.element) && ( 0 > found ) )
	{
		found = IsBefore(SortListGetData(finder), data);
		
		finder = SortListNext(finder);
	}

	if( 0 == found )
	{
		finder = SortListPrev(finder);
	}
	else
	{
		finder = end;
	}

	return finder;
}
/*----------------------------------------------------------------------------*/

void SortListMerge(sort_list_t *src, sort_list_t *dest)
{
	int do_splice = 0;

	sort_list_iter_t src_elem = {0};
	sort_list_iter_t dest_elem = {0};
	sort_list_iter_t chunk_begin = {0};
	sort_list_iter_t chunk_end = {0};

	assert(src);
	assert(dest);

	src_elem = SortListBegin(src);
	dest_elem = SortListBegin(dest);
	chunk_begin = src_elem;

	/* if dest is empty copy all src into dest */
	if( SortListIsEmpty(dest) )
	{
		DListSpliceBefore( dest_elem.element,
		 				   chunk_begin.element,
		                   SortListEnd(src).element );
	}
	while( !SortListIsEmpty(src) && dest_elem.element != 
			SortListEnd(dest).element )
	{
		/*src_elem < dest_elem (sort little to big) & src end not reached */
		/*this condition advances src_elem until it becomes chunk end*/
		if( (src_elem.element != SortListEnd(src).element) &&
		    ( 0 > dest->IsBefore(SortListGetData(src_elem),
			SortListGetData(dest_elem)) ) )
		{
			do_splice += 1;
			src_elem = SortListNext(src_elem);
		}
		else
		{
			chunk_end = src_elem;
			
			if(do_splice)
			{
			  DListSpliceBefore( dest_elem.element,
			  chunk_begin.element,
			  chunk_end.element);

			  chunk_begin = chunk_end;
			  do_splice = 0;
			}
			dest_elem = SortListNext(dest_elem);
		}		
	}
	/*if src > dest*/
	if((!SortListIsEmpty(src)) && 
	  ((dest_elem.element) == SortListEnd(dest).element))
	{
		chunk_end = SortListEnd(src);

	    DListSpliceBefore(dest_elem.element, chunk_begin.element,
	                          				  chunk_end.element);
	}

	SortListDestroy(src);
}



