/******************************************************************************/
/*	@File:		sort_list.h													  */
/*	@Created:	26.06.19 													  */
/*  @Version: 	1.5  														  */
/*	@Modified:	30.06.19													  */
/*																			  */
/*	@Brief:		Sorted List Functions:			SortListCreate 				  */
/*										   		SortListDestroy				  */
/*							  				 	SortListCount				  */
/*							  				 	SortListIsEmpty				  */
/*							  				 	SortListBegin				  */
/*							  				 	SortListEnd					  */
/*							  				 	SortListNext				  */
/*							  				 	SortListPrev				  */
/*							  				 	SortListGetData				  */
/*							  				 	SortListIsSameIterator		  */
/*												SortListInsert				  */
/*												SortListRemove				  */
/*										   		SortListPopFront			  */
/*										   		SortListPopBack				  */
/*												SortListForEach				  */
/*												SortListFind				  */
/*												SortListFindBySortKey		  */
/*										 		SortListMerge				  */
/******************************************************************************/

/*
Change log

v.1.1  - added sort_list_ prefix to funs action, ismatch, comp 
v.1.2  - changed type sorted_list_iter to sort_list_iter 
		 and name sorted_list_iter_t to sort_list_iter_t
		
	   - added explanation to return of function Compare
	   
	   - changed return value in failure case in SortListFind and 
	     SortListFindBySortKey functions from NULL to iterator to the end 
	     of Sorted List

v1.3   - changed argument's order in IsMatch function 
		 from (const void *data1, const void *data2, void *param);
		 to (const void *data1, void *param, const void *data2)
		
v1.4   - changed return value in failure case in SortListFind function 
		 from 'iterator to the end of Sorted List' 
		 to 'end iterator' 
		 
v1.5   - addded IsBefore function to Create signature
	   - changed findbykey signature, added Compare func there


*/

#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h> /* size_t */

typedef struct sort_list_iter
{
	void* element;
	
} sort_list_iter_t;

typedef struct sort_list sort_list_t;


/* performs an action on existing list using param */
typedef int (*sort_list_action_t)(void *data, void *param);

/* search for data in existing list using param */
typedef int (*sort_list_ismatch_t)(const void *data1, void *param,
															const void *data2);

/* search for data in existing list using param */
typedef int(*sort_list_comp_t)(const void *list_data, const void *user_data);
															
/*  used to insert data to the list while keeping it sorted  */
typedef int(*sort_list_isbefore_t)(const void *list_data, const void *user_data);

/*
	NOTE: in every function begin is included in the operations,
		  while end is excluded from operations - 
	      operations end at the element before.
*/

/*------------------------------------------------------------------------------

SortListCreate - Creates a new Sorted List. 
                                             
ARGS: 
IsBefore - Function that determines the sort order of the list
		   this function returns: 
							 1 if user_data is sorted before the queue data
							 0 if user_data is sorted after the queue data	
		
RETURNS: 	Success: pointer to a Sorted List 
			Failure: NULL   		  

*/
sort_list_t *SortListCreate(sort_list_isbefore_t IsBefore);
 
 
/*------------------------------------------------------------------------------

SortListDestroy - Frees all allocated memory to Sorted List. 
                                        
ARGS: 
sort_list - pointer to a Sorted List			   
 
RETURNS: void                                                                

*/ 
void SortListDestroy(sort_list_t *sort_list);

/*------------------------------------------------------------------------------

SortListCount - Counts the number of elements in Sorted List. 
                                        
ARGS: 
sort_list - pointer to a Sorted List			   
 
RETURNS: number of elements                       	                          
*/
 
size_t SortListCount(const sort_list_t *sort_list);

/*------------------------------------------------------------------------------

SortListIsEmpty - checks whether the Sorted List is empty.
                                        
ARGS: 
sort_list  - pointer to a Sorted List			   
 
RETURNS: 	 1 if empty
			 0 if not empty                       	                          
*/
 
int SortListIsEmpty(const sort_list_t *sort_list);

/*------------------------------------------------------------------------------

SortListBegin - returns the first legal element in the Sorted List.
			If the list is empty, returns iterator to the end of the list.
                                        
ARGS: 
sort_list -  pointer to a Sorted List	
 
RETURNS: 	 iterator to the first legal element or           		    
			 iterator to the end if empty                 
*/
 
sort_list_iter_t SortListBegin(const sort_list_t *sort_list);

/*------------------------------------------------------------------------------

SortListEnd - returns the end of the Sorted List.
                                        
ARGS: 
sort_list -  pointer to a Sorted List	   
 
RETURNS: 	iterator to the list's end
*/
 
sort_list_iter_t SortListEnd(const sort_list_t *sort_list);

/*------------------------------------------------------------------------------

SortListNext - returns the next iterator in the Sorted List. 
            (calling on end element will cause undefined behaviour)                 
ARGS: 
iterator -  struct with pointer to Sorted List		   
 
RETURNS: 	next iterator on the list        		                  	  
			
*/
 
sort_list_iter_t SortListNext(sort_list_iter_t iterator);

/*------------------------------------------------------------------------------

SortListPrev - returns the previous iterator in the Sorted List. 
			(calling on the first element will cause undefined behaviour)
                                        
ARGS: 
iterator - iterator of Sorted List		   
 
RETURNS: 	previous iterator on the list         		                  	  
			        	                  	  
*/
sort_list_iter_t SortListPrev(sort_list_iter_t iterator);

/*------------------------------------------------------------------------------

SortListGetData - gets the data from an iterator
                                        
ARGS: 
iterator - iterator of Sorted List		   
 
RETURNS:	pointer to data of current iterator
			
*/
 
void *SortListGetData(sort_list_iter_t iterator);

/*------------------------------------------------------------------------------

SortListIsSameIterator - checks if both iterators are the same 
                                        
ARGS: 
iterator1 - iterator of Sorted List	
iterator2 - iterator of Sorted List	   
 
RETURNS: 	1 if it is the same iterator
			0 otherwise					        	                  	      
*/
 
int SortListIsSameIterator(sort_list_iter_t iterator1, 
												  sort_list_iter_t iterator2);

/*------------------------------------------------------------------------------

SortListInsert - Inserts an element to a Sorted List in an appropriate place. 
                                          
ARGS:
sort_list - pointer to Sort List
data 	  - pointer to data to be added to the list 
			   
RETURNS:	Success: iterator to the new element
			Failure: iterator to the end of list
*/          

sort_list_iter_t SortListInsert(sort_list_t *sort_list, void *data);

/*------------------------------------------------------------------------------

SortListRemove - Removes from the Sorted List and destroys the given iterator.
				(calling on end element will cause undefined behaviour)
                                          
ARGS: 
iterator - iterator of the Sorted List to be removed
			   
RETURNS:   the next iterator

		   if the last element before the end of the list was removed:  
		   iterator to the end of list will be returned
*/          

sort_list_iter_t SortListRemove(sort_list_iter_t iterator);

/*------------------------------------------------------------------------------

SortListPopFront - Detaches an element from the beginning of the Sorted List 
				   and destroys it. 
                                          
ARGS: 
sort_list - pointer to a Sorted List.
			   
RETURNS: void pointer to removed data
		 NULL if the list is empty				  											  
*/          

void *SortListPopFront(sort_list_t *sort_list);

/*------------------------------------------------------------------------------

SortListPopBack - Detaches an element from the end of the Sorted List 
			   and destroys it.  
                                          
ARGS: 
sort_list - pointer to a Sorted List
			   
RETURNS: void pointer to removed data 		
		 NULL if the list is empty									  
*/          

void *SortListPopBack(sort_list_t *sort_list);

/*------------------------------------------------------------------------------

SortListForEach - performs the same action on every member in the List. 
			   (Stops in case of an action failure).
                                            
ARGS: 
begin  - iterator to the first element on which the action should
         be performed.
end    - iterator to the last element
Action - Action function that performs an action on the data
	  	 (returns 0 on action success, other on failure)
param  - the second arg for the Action function
		   
RETURNS:	Status of the last action performed.
			      
*/
                                                             
int SortListForEach(sort_list_iter_t begin, sort_list_iter_t end,
									    sort_list_action_t Action, void *param);
/*------------------------------------------------------------------------------

SortListFind - Finds a specific element in the Sorted List. 
                                            
ARGS: 
begin	 - iterator to the beginning of existing Sorted List
end  	 - iterator to the end of existing Sorted List
IsMatch  - IsMatch function checks for data match (returns 1/0)
param    - the second arg for the IsMatch function
data2    - criteria data for search

RETURNS:	Success: iterator to the found element
			Failure: end iterator 
*/
 
sort_list_iter_t SortListFind(sort_list_iter_t begin, sort_list_iter_t end,
				   sort_list_ismatch_t IsMatch, void *param, const void *data2);

/*------------------------------------------------------------------------------

SortListFindBySortKey - Finds a specific element in the Sorted List,
					
                                            
ARGS: 
sort_list - pointer to the sorted list.
data- criteria data for search

RETURNS:	Success: iterator to the found element
			Failure: iterator to the end of Sorted List
*/
 
sort_list_iter_t SortListFindBySortKey(sort_list_t *sort_list,
									 sort_list_comp_t Compare, const void *data);

/*------------------------------------------------------------------------------

SortListMerge - Merge two Sorted Lists to one Sorted List. 
			    src and dest lists has to have identical sort criteria.
				src is destroyed after the merge.							
                  	                       
ARGS: 
src  - pointer to sorted list, that is to be merged with dest.
dest - pointer to sorted list, that has src merged into.
	
*/          

void SortListMerge(sort_list_t *src, sort_list_t *dest);

/*----------------------------------------------------------------------------*/

#endif /* __SORTED_LIST_H__ */
