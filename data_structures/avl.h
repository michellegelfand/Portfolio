/******************************************************************************/
/*    @File:       AVL.h                                                      */
/*    @Created:    18.07.19                                                   */
/*    @Version:    1.1	                                                      */
/*    @Author:     Grisha Tsukerman                                           */
/*	  NOTE: Our binary tree supports only unique keys (no duplicates)*/
/******************************************************************************/


#ifndef __AVL_H__
#define __AVL_H__

#include <sys/types.h> /*size_t, ssize_t */

typedef enum avl_status
{
    AVL_SUCCESS,
    AVL_FAIL
}avl_status_t;

typedef struct avl avl_t;


typedef int (*avl_compare_t)(const void *data1, const void *data2, 
                                                        void *param );

/* visitor return: on error: non zero
                   on success: 0 */
typedef int (*avl_visitor_t)(void *data, void *param);



/******************************************************************************/

/* RETURN - pointer to new tree  */

avl_t *AvlCreate(avl_compare_t compare, void *param);

/******************************************************************************/

/* RETURN: none. */

void AvlDestroy(avl_t *tree);

/******************************************************************************/

/* RETURN: number of nodes in a tree.  */

size_t AvlCount(const avl_t *tree);

/******************************************************************************/
/* RETURN:      AVL_SUCCESS  
                AVL_FAIL
                
*/
avl_status_t AvlInsert(avl_t *tree, void *data);
    
/******************************************************************************/

/*AVLRemove -  func to remove a node            

RETURN:         none.

*/
void AvlRemove(avl_t *tree, void *data);

/******************************************************************************/
/*
RETURN:   the status of the visitor func
            NOTE: stops in case visitor function fails
*/
int AvlForEach(avl_t *tree, avl_visitor_t visitor, void *param);

/******************************************************************************/
/*RETURN:  data found by key
         NULL - if not found.
*/
void *AvlFind(const avl_t *tree, void *key);

/*****************************************************************************/
int AvlIsEmpty(const avl_t *tree);

/*****************************************************************************/
/* RETURN:  Height of root (number of edges on the longest path)
        (-1 for empty tree)
*/

ssize_t AvlHeight(const avl_t *tree);

#endif /* __AVL_H__*/
17001
