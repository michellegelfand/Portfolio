/******************************************************************************/
/*    @File:       bst.h                                                      */
/*    @Created:    18.07.19                                                   */
/*    @Version:    1.1	                                                      */
/*    @Author:     Alex Raihel                                                */
/******************************************************************************/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst_node bst_node_t;
typedef struct bst bst_t;
typedef struct bst_node *bst_iterator;

/*

struct bst_node
{
	void *data;
    bst_node_t *parent;
	bst_node_t *children[2];   
};

struct bst
{
	bst_node_t root;
    bst_compare_t compare;
    void *param;
};

 */


/* return:
             1  -  if data1> data2
             0  -  if data1 == data2
            -1  -  if data1 < data2
                   *existed data is data1
                   *new data is data2

             */
typedef int (*bst_compare_t)(const void *data1, const void *data2, 
                                                        void *param );

/* visitor return: on error: -1
                   on success: 0 */
typedef int (*bst_visitor_t)(void *data, void *param);


/*NOTE: Our binary tree soppurts only unique keys (no duplicates) */
/******************************************************************************/

/* RETURN - pointer to new tree  */

bst_t *BstCreate(bst_compare_t compare, void *param);

/******************************************************************************/

/* RETURN: none. */

void BstDestroy(bst_t *tree);

/******************************************************************************/

/* RETURN: number of nodes in a tree.  */

size_t BstCount(const bst_t *tree);

/******************************************************************************/  
          
/* RETURN: iterator to the smallest element.
            End if the tree is empty  */

bst_iterator BstBegin(const bst_t *tree);
/******************************************************************************/  
          
/* RETURN: returns an invalid iterator/the one after the last valid element*/

bst_iterator BstEnd(const bst_t *tree);


/******************************************************************************/

/* RETURN: the parent iterator.
        when prev on Begin is an undefined behaviour */

bst_iterator BstPrev(bst_iterator iterator);

/******************************************************************************/

/* RETURN: iterator to the next element
            next on End is an undefined behaviour */

bst_iterator BstNext(bst_iterator iterator);
    

/******************************************************************************/

/* RETURN:  pointer to node's data. */

void *BstGetData(bst_iterator iterator);

/******************************************************************************/

/*BstInsert -  and compare func to insert new_node
              in the correct place

RETURN:         SUCCESS insreted iterator 
                FAIL    invalid iterator

*/
bst_iterator BstInsert(bst_t *tree, void *data);
    
/******************************************************************************/

/*BstRemove -  and compare func to remove a node            

RETURN:         none.

*/
void BstRemove(bst_t *tree, bst_iterator to_remove);


/******************************************************************************/

/*BstForEach -  and action func to preform on all the nodes 

RETURN:        the status of the visitor func

*/
int BstForEach(bst_iterator from, bst_iterator to, bst_visitor_t visitor, 
                                                                void *param);

/******************************************************************************/

/*BstFind - Gets pointer to tree and compare func to find a specific node 

RETURN:        iterator to the found node /
               NULL if not found

*/
bst_iterator BstFind(bst_t *tree, void *data);

/*****************************************************************************/

/*BstIsSameIterator - 

RETURN:     1 for matching iterators
            0 for not matching iterators */



int BstIsSameIterator(const bst_iterator first, const  bst_iterator second);
/*****************************************************************************/

/* 
RETURN:     1 if the tree is empty
            0 otherwise*/

int BstIsEmpty(const bst_t *tree);
#endif /* __BST_H__*/
