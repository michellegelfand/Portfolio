/******************************************************************************/
/*	@File:		doubly_list.h												  */
/*	@Author: 	Michelle Gelfand									  */
/*	@Created:	20.06.19 													  */
/*  @Version: 	1.5  														  */
/*	@Modified:	24.06.19													  */
/*	@Reviewer:	Evgeni S.												  */
/*																			  */
/*	@Brief:		Doubly Linked List Functions:	DListCreate 				  */
/*										   		DListDestroy				  */
/*							  				 	DListCount					  */
/*							  				 	DListIsEmpty				  */
/*							  				 	DListBegin					  */
/*							  				 	DListEnd					  */
/*							  				 	DListNext					  */
/*							  				 	DListPrev					  */
/*							  				 	DListGetData				  */
/*							  				 	DListIsSameIterator			  */
/*												DListInsertBefore			  */
/*												DListInsertAfter			  */
/*												DListRemove					  */
/*										   		DListPushFront				  */
/*										   		DListPushBack				  */
/*										   		DListPopFront				  */
/*										   		DListPopBack				  */
/*												DListForEach				  */
/*												DListFind					  */
/*										 		DListSpliceBefore			  */
/******************************************************************************/

#ifndef __DOUBLY_LINKLIST_H__
#define __DOUBLY_LINKLIST_H__

#include <stddef.h> /* size_t */

typedef struct dl_node* iterator_t;

typedef struct dl_list dl_list_t;

/* performs an action on existing list using param */
typedef int (*action_t)(void *data, void *param);

/* search for data in existing list using param */
typedef int (*ismatch_t)(const void *data1, void *param, const void *data2);

/*
	NOTE: in every function begin is included in the operations,
		  while end is excluded from operations - 
										operations end at the element before.
*/

/*------------------------------------------------------------------------------

DListCreate - Creates a new Doubly Linked List. 
                                             
ARGS: void

RETURNS: 	Success: pointer to a Doubly Linked List 
			Failure: NULL   		  
*/

dl_list_t *DListCreate(void);
 
 
/*------------------------------------------------------------------------------

DListDestroy - Frees all allocated memory to Doubly Linked List. 
                                        
ARGS: 
dl_list - pointer to a Doubly Linked List			   
 
RETURNS: void                                                                
*/
 
void DListDestroy(dl_list_t *dl_list);


/*------------------------------------------------------------------------------

DListCount - Counts the number of elements in Doubly Linked List. 
                                        
ARGS: 
dl_list - pointer to a Doubly Linked List			   
 
RETURNS: number of elements                       	                          
*/
 
size_t DListCount(const dl_list_t *dl_list);

/*------------------------------------------------------------------------------

DListIsEmpty - checks whether the Doubly Linked List is empty.
                                        
ARGS: 
dl_list - pointer to a Doubly Linked List			   
 
RETURNS: 	1 if empty
			0 if not empty                       	                          
*/
 
int DListIsEmpty(const dl_list_t *dl_list);

/*------------------------------------------------------------------------------

DListBegin - returns the first legal element in the Doubly Linked List.
			If the list is empty, returns iterator to the end of the list.
                                        
ARGS: 
dl_list - pointer to a Doubly Linked List
 
RETURNS: 	 iterator to the first legal element or           		    
			 iterator to the end if empty                 
*/
 
iterator_t DListBegin(const dl_list_t *dl_list);

/*------------------------------------------------------------------------------

DListEnd - returns the end of the Doubly Linked List.
                                        
ARGS: 
dl_list - pointer to a Doubly Linked List	   
 
RETURNS: 	iterator to the list's end            		                  	  
*/
 
iterator_t DListEnd(const dl_list_t *dl_list);

/*------------------------------------------------------------------------------

DListNext - returns the next iterator in the Doubly Linked List. 
            (calling on end element will cause undefined behaviour)                 
ARGS: 
iterator - iterator of Doubly Linked List		   
 
RETURNS: 	next iterator on the list        		                  	  
			
*/
 
iterator_t DListNext(const iterator_t iterator);

/*------------------------------------------------------------------------------

DListPrev - returns the previous iterator in the Doubly Linked List. 
			(calling on the first element will cause undefined behaviour)
                                        
ARGS: 
iterator - iterator of Doubly Linked List		   
 
RETURNS: 	previous iterator on the list         		                  	  
			        	                  	  
*/
iterator_t DListPrev(const iterator_t iterator);

/*------------------------------------------------------------------------------

DListGetData - gets the data from an iterator
                                        
ARGS: 
iterator - iterator of Doubly Linked List		   
 
RETURNS:	pointer to data of current iterator
			
*/
 
void *DListGetData(const iterator_t iterator);

/*------------------------------------------------------------------------------

DListIsSameIterator - checks if both iterators are the same 
                                        
ARGS: 
iterator1 - iterator of Doubly Linked List	
iterator2 - another iterator of Doubly Linked List	   
 
RETURNS: 	1 if it is the same iterator
			0 if not					        	                  	      
*/
 
int DListIsSameIterator(const iterator_t iterator1, const iterator_t iterator2);

/*------------------------------------------------------------------------------

DListInsert - Inserts an element before the given iterator. 
                                          
ARGS:
dl_list - pointer to a Doubly Linked List 
iterator - iterator of the Doubly Linked List
data - pointer to data to be added to the list 
			   
RETURNS:	Success: iterator to the new element
			Failure: iterator to the end of list
*/          

iterator_t DListInsert(dl_list_t *dl_list, iterator_t iterator, void *data);

/*------------------------------------------------------------------------------

DListInsertAfter - Inserts an element after the given iterator. 
                                          
ARGS:
dl_list - pointer to a Doubly Linked List 
iterator - iterator of the Doubly Linked List
data - pointer to data to be added to the list
			   
RETURNS:	Success: iterator to the new element
			Failure: iterator to the end of list
 */          

iterator_t DListInsertAfter(dl_list_t *dl_list, iterator_t iterator, void *data);

/*------------------------------------------------------------------------------

DListRemove - Removes from the list and destroys the given iterator.
				(calling on end element will cause undefined behaviour)
                                          
ARGS: 
iterator - iterator of the Doubly Linked List to be removed
			   
RETURNS: 	the next iterator

			if the last element before the end of the list was removed:  
			iterator to the end of list will be returned
*/          

iterator_t DListRemove(iterator_t iterator);

/*------------------------------------------------------------------------------

DListPushFront - Inserts an element to the beginning of the List. 
                                          
ARGS: 
dl_list - pointer to a Doubly Linked List
data - pointer to data to be added to the list
			   
RETURNS:	Success: iterator to the new element
			Failure: iterator to the end of list								  
*/          

iterator_t DListPushFront(dl_list_t *dl_list, void *data);

/*------------------------------------------------------------------------------

DListPushBack - Inserts an element to the end of the List. 
                                          
ARGS: 
dl_list - pointer to a Doubly Linked List
data - pointer to data to be added to the list
			   
RETURNS:	Success: iterator to the new element
			Failure: iterator to the end of list 							
*/          

iterator_t DListPushBack(dl_list_t *dl_list, void *data);

/*------------------------------------------------------------------------------

DListPopFront - Detaches an element from the beginning of the List 
				and destroys it. 
                                          
ARGS: 
dl_list - pointer to a Doubly Linked List
			   
RETURNS: void pointer to removed data
		 NULL if the list is empty				  											  
*/          

void *DListPopFront(dl_list_t *dl_list);

/*------------------------------------------------------------------------------

DListPopBack - Detaches an element from the end of the List and destroys it.  
                                          
ARGS: 
dl_list - pointer to a Doubly Linked List
			   
RETURNS: void pointer to removed data 		
		 NULL if the list is empty									  
*/          

void *DListPopBack(dl_list_t *dl_list);

/*------------------------------------------------------------------------------

DListForEach - performs the same action on every member in the List. 
			   (Stops in case of an action failure).
                                            
ARGS: 
begin - iterator to the first element on which the action should
        be performed.
end -   iterator to the last element
Action - Action function that performs an action on the data
	  	(returns 0 on action success, other on failure)
param - the second arg for the Action function
		   
RETURNS:	Status of the last action performed.			      
*/
                                                             
int DListForEach(iterator_t begin, iterator_t end, action_t Action, 
																void *param);

/*------------------------------------------------------------------------------

DListFind - Finds a specific element in the Doubly Linked List. 
                                            
ARGS: 
dl_list - pointer to existing List
IsMatch - IsMatch function checks for data match (returns 1/0)
param - the second arg for the IsMatch function
data2 - criteria data for search

RETURNS:	Success: iterator to the found element
			Failure: NULL
*/
 
iterator_t DListFind(iterator_t begin, iterator_t end,
					 ismatch_t IsMatch, void *param, const void *data2);

/*------------------------------------------------------------------------------

DListSpliceBefore - Detaches a number of consecutive iterators from one List 
					and attaches them to another. 
					If this results in an empty list, it is not destroyed.
					The function may be performed on elements from the same
					list if there is no overlap between the section begin-end
					and where_to. Overlap will result in undefined behavior.
					Note: if begin and end are the same iterator, no action 
							will be performed
                  	                       
ARGS: 
begin - beginning of the section to be spliced
end - end of the section to be spliced
where_to - iterator in the destination, 
						before which the required section should be inserted
*/          

void DListSpliceBefore( iterator_t where_to, iterator_t begin, iterator_t end);

/*----------------------------------------------------------------------------*/

#endif /* __DOUBLY_LINKLIST_H__ */
