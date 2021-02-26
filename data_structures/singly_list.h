/**********************************************************************;
* Project           : Data Structures
*
* Program name      : singly_list.h
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


#ifndef __SINGLY_LIST_H__
#define __SINGLY_LIST_H__

#include <stddef.h> /* size_t */

typedef struct sl_node sl_node_t;

struct sl_node
{
	void *data;
	sl_node_t *next;
};

/*check if existing data matches the user search criteria */
typedef int (*is_match_t)(const void *data, void *param);

/* performs an action on existing data using param */
typedef int (*action_t)(void *data, void *param);

/*----------------------------------------------------------------------------*/

/* Creates new Linked List. 
                                             
ARGS: 
data - pointer to the data to be inserted into the node				   
next - pointer to the next node

RETURNS: pointer to a Linked List or NULL if creation failed   */

sl_node_t *SListCreateNode(void *data, sl_node_t *next);
 
/*----------------------------------------------------------------------------*/

/* Frees all nodes from head pointer onwards. 
                                        
ARGS: 
head - pointer from which all members will be freed.			   
 
RETURNS: none.                                                                */
 
void SListFree(sl_node_t *head);

/*----------------------------------------------------------------------------*/

/* Insert an element after the given node. 
                                          
ARGS:
whereto_node - pointer to a node to insert a node after it
new_node - node to be inserted

RETURNS: pointer to the new_node  */       

sl_node_t *SListInsertAfter(sl_node_t *whereto_node, sl_node_t *new_node);

/*----------------------------------------------------------------------------*/

/* Insert an element before the given node. 
                                          
ARGS: 
whereto_node - pointer to a node to insert the new node before
new_node - node to be inserted
			   
RETURNS: pointer to the new_node      */          

sl_node_t *SListInsertBefore(sl_node_t *whereto_node, sl_node_t *new_node);

/*----------------------------------------------------------------------------*/

/* Detaches an element from the Linked List. (can't detach the last one.)
   (Data is to be freed by user).
                                           
ARGS: 
node - pointer to the node to be Detached
    
RETURN : pointer to the detached node  */
      
sl_node_t *SListRemove(sl_node_t *node);

/*----------------------------------------------------------------------------*/

/* Detaches an element from the Linked List. 
                                          
ARGS: 
node - pointer to the node before the one to be detached 

RETURN : pointer to the detached node */
          
sl_node_t *SListRemoveAfter(sl_node_t *node);

/*----------------------------------------------------------------------------*/

/* Counts all members of this Linked List. 
                                            
ARGS: 
head - pointer to existing Linked List				   
 
RETURNS: the number of the elements in the Linked List. */
 
size_t SListCount(const sl_node_t *head);

/*----------------------------------------------------------------------------*/

/* Find specific element from the Linked List. 
                                            
ARGS: 
head - pointer to existing Linked List
data - void pointer to the value to be found.			   
func - IsMatch checks for data match (returns 1/0)
param - the second arg for the IsMatch function
RETURNS: pointer to the found element or NULL if nothing found. */
 
sl_node_t *SListFind(sl_node_t *head, is_match_t IsMatch, void *param );

/*----------------------------------------------------------------------------*/

/* Foreach performs the same action on every member in the list. 
   Stops after first failed action.
                                            
ARGS: 
head - pointer to existing Linked List
func - Action performs action on the data
	   (returns 0 on action success, -1 if not)
		   
RETURNS: 0 on all actions success, else -1   */
                                                             
int SListForEach(sl_node_t *head, action_t Action, void *param);

/*----------------------------------------------------------------------------*/

/* Flips all the members of the Linked List. 
                                            
ARGS: 
head - pointer to existing Linked List	

RETURNS: pointer to the new head of the Linked List.	 */	 	   
 
sl_node_t *SListFlip(sl_node_t *head);

/*----------------------------------------------------------------------------*/

/* Finds a node at which the intersection of two Singly Linked Lists occures 
                                            
ARGS: 
head1 - pointer to existing Linked List	
head2 - pointer to the additional Linked List	

RETURNS: pointer to the node at which the intersection occures,
		 or NULL if none */	   
 
sl_node_t *SListIntersection(sl_node_t *head1, sl_node_t *head2);

/*----------------------------------------------------------------------------*/

/* Finds a node at which the loop in a Singly Linked Lists occures
                                            
ARGS: 
head - pointer to existing Linked List	

RETURNS: 1 if there is a loop, 0 if not	 */	 	   
 
int SListHasLoop(const sl_node_t *head);

/*----------------------------------------------------------------------------*/

#endif /* __SINGLY_LIST_H__ */

