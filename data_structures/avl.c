/**********************************************************************;
* Project           : Data Structures
*
* Program name      : avl.c
*
* Author            : Michelle Gelfand
*
* Date created      : 28.07.19
*
* Purpose           : This program provides the user with a recursive
                      self sorting balance binary search tree
*
* Version           : 1.0
*														  
*******************************************************************/
#include <stdlib.h>/*malloc */
#include <assert.h>/*assert*/ 

#include "avl.h"

#define LEFT_CHILD children[0] 
#define RIGHT_CHILD children[1]
#define ROOT tree->root
#define LEFT 0
#define RIGHT 1 

#define MAX_HEIGHT(x,y) (ssize_t)(x>y?x:y)
#define SIDE(x) ((1==x)? LEFT : RIGHT )


typedef struct avl_node avl_node_t;

static void _DestroyAssistRec(avl_node_t *curr_node);
static avl_status_t _InsertAssistRec(avl_compare_t Compare,
avl_node_t *node_traversed, void *data, void *param, avl_t *tree);
static int _ForEachAssistRec(avl_node_t *node, avl_visitor_t visitor,
void *param);
static void _CountAssistRec(avl_node_t *node, size_t *count);
static  ssize_t _UpdateNodeHeight (avl_node_t *node);
static avl_node_t *_RemoveFindRec(avl_node_t *node, avl_compare_t compare,
 void *key, void *param);
static avl_node_t *GetNext(avl_node_t *to_remove, avl_t *tree);
static avl_node_t *_GetMostChildRec(avl_node_t *node, int side, avl_t *tree);
static avl_node_t **ParentFieldToChild(avl_t *tree, avl_node_t 
**parent_field_to_child, void *key, int *compare_result);
static ssize_t _GetNodeHeight(avl_node_t *node);
static ssize_t _GetBalance(avl_node_t* node);
static avl_node_t *RotateRight(avl_node_t* root, avl_t *tree);
static avl_node_t *RotateLeft(avl_node_t* root, avl_t *tree);
static void _Balance(avl_node_t **root, ssize_t balance, avl_t *tree);

struct avl_node
{
    void *data;
    ssize_t height;
    avl_node_t *children[2];
};

struct avl
{
    avl_node_t *root;
    avl_compare_t Compare;
    void *param;
};

/********** P  R  I  N  T *************************************/
#ifndef NDEBUG
#include <stdio.h>
static void PrintTree(avl_node_t * root, int space) 
{ 
    int i = 0;

    if (root == NULL) 
        return; 

    space += 5; 

    PrintTree(root->RIGHT_CHILD, space); 
    printf("\n"); 

    for (i = 0; i < space; i++) 
    {
        printf(" "); 
    }
 
    if(root)
    {
         printf("%d   {%ld}\n ", *(int*)(root->data), root->height); 
    }

     PrintTree(root->LEFT_CHILD, space);
}

#else
#define PrintTree(root, space);
#endif

/*____________________________________________________________________________*/

avl_t *AvlCreate(avl_compare_t compare, void *param)
{
    avl_t *tree = NULL;
	
    assert(compare);

    tree = (avl_t*)malloc(sizeof(avl_t));

	if(tree)
	{
		tree->root = NULL;
        tree->Compare = compare;
        tree->param = param;
	}
	return tree;
}

/*____________________________________________________________________________*/

/* TODO DestroyNode maybe a better name for this function */
static void _DestroyNode(avl_node_t *node)
{
    assert(node);

    node->data = NULL;
    node->LEFT_CHILD = NULL;
    node->RIGHT_CHILD = NULL;

    free(node);
}

/*____________________________________________________________________________*/

/*LEFT RIGHT ROOT "post order" */
void AvlDestroy(avl_t *tree)
{
    if(tree)
    {
        if(NULL ==  tree->root)
        {
            tree->param = NULL;
            tree->root = NULL;
            tree->Compare = NULL;
            free(tree);
            tree = NULL;
            return;
        }
        else
        {
            _DestroyAssistRec(ROOT);
            tree->root = NULL;
            tree->param = NULL; 
            tree->Compare = NULL;
            free(tree);
            tree = NULL;
        } 
    }  
}

/*___________________________________________________________________________ */

static void _DestroyAssistRec(avl_node_t *curr_node)
{
    if(curr_node->LEFT_CHILD)
    {
        _DestroyAssistRec(curr_node->LEFT_CHILD);
    }
    if (curr_node->RIGHT_CHILD)
    {
        _DestroyAssistRec(curr_node->RIGHT_CHILD);
    }

    _DestroyNode(curr_node);

    curr_node = NULL;
}

/*____________________________________________________________________________*/

static avl_node_t *_CreateNode(void *data)
{
    avl_node_t *new = (avl_node_t*)malloc(sizeof(avl_node_t));

    if(new)
    {
        new->data = data;
        new->height = 0;
        new->LEFT_CHILD = NULL;
        new->RIGHT_CHILD = NULL; 
    }

    return new;
}

/*___________________________________________________________________________ */

avl_status_t AvlInsert(avl_t *tree, void *data)
{
    avl_node_t *node_traversed = NULL;
    avl_status_t status= AVL_SUCCESS;

    assert(tree);

    node_traversed = tree->root;

    /*if no root */
    if( NULL == (tree->root))
    {
        tree->root = _CreateNode(data);
        if( NULL == (tree->root))
        {
            status = AVL_FAIL;
        }

    }
    /*traverse tree to find insert */
    else
    { 
       status = _InsertAssistRec(tree->Compare ,node_traversed, 
                                        data, tree->param, tree);
    }
     
    PrintTree(ROOT, 0); 
    return status;
}

/*___________________________________________________________________________ */

static  ssize_t _UpdateNodeHeight (avl_node_t *node)
{
    if (!node)
    {
        return 0;
    }
    else
    {
        node->height = (1+ MAX_HEIGHT(_GetNodeHeight(node->LEFT_CHILD),
                                 _GetNodeHeight(node->RIGHT_CHILD)));
    }
    
    return node->height;
}

/*___________________________________________________________________________ */

static void _Balance(avl_node_t **root, ssize_t balance, avl_t *tree) 
{
    /*left is longer */
    if ( 1 < balance) 
    {
       if(0 < _GetBalance((*root)->LEFT_CHILD))
       {
           *root = RotateRight(*root, tree);
       } 
       else
       {
           (*root)->LEFT_CHILD = RotateLeft((*root)->LEFT_CHILD, tree);
           *root = RotateRight(*root, tree);
       }

       _UpdateNodeHeight(*root);
       _UpdateNodeHeight((*root)->LEFT_CHILD);
       _UpdateNodeHeight((*root)->RIGHT_CHILD);
    }
    /*right is longer */
    if( -1 > balance)
    {
       if(0 > _GetBalance((*root)->RIGHT_CHILD))
       {
           *root = RotateLeft(*root, tree);
       } 
       else
       {
          (*root)->RIGHT_CHILD = RotateRight((*root)->RIGHT_CHILD, tree);
          *root = RotateLeft(*root, tree);
       }

       _UpdateNodeHeight(*root);
       _UpdateNodeHeight((*root)->LEFT_CHILD);
       _UpdateNodeHeight((*root)->RIGHT_CHILD);
    }
}

/*___________________________________________________________________________ */

static avl_status_t _InsertAssistRec(avl_compare_t Compare, 
            avl_node_t *node_traversed, void *data, void *param, avl_t *tree)
{
    /* returns 1 if data is smaller, -1 if bigger, 0 equal */

    int cmp_result = Compare(node_traversed->data, data, param);
    avl_status_t status = AVL_SUCCESS;

    /*if data smaller than node's data */
    if( 1 == cmp_result)
    {
        if(!node_traversed->LEFT_CHILD)
        {
            node_traversed->LEFT_CHILD = _CreateNode(data);

            if(NULL == (node_traversed->LEFT_CHILD))
            {
                status =  AVL_FAIL;
            }
        }
        else
        {
           status =  _InsertAssistRec(Compare, 
                        node_traversed->LEFT_CHILD, data, param, tree);
           _UpdateNodeHeight(node_traversed);
        }
    }
     /*if data bigger than node's data */
    else if ( -1 == cmp_result)
    {
        if(!node_traversed->RIGHT_CHILD)
        {
            node_traversed->RIGHT_CHILD = _CreateNode(data);

            if( NULL == (node_traversed->RIGHT_CHILD))
            {
                status = AVL_FAIL; 
            }
        }
        else
        {
            status =  _InsertAssistRec(Compare, node_traversed->RIGHT_CHILD, 
            data, param, tree); 
            _UpdateNodeHeight(node_traversed);
        }
    }
    else
    {
         /*if trying to insert duplicate  */
         status = AVL_FAIL;   
    }
   
     _UpdateNodeHeight(node_traversed); 
     _Balance(&node_traversed,_GetBalance(node_traversed), tree);
   
    return status;
}

/*____________________________________________________________________________*/

int AvlIsEmpty(const avl_t *tree)
{
    assert(tree);

    return (!!(NULL == ROOT));
}

/*LEFT, ROOT, RIGHT , "in order" */
int AvlForEach(avl_t *tree, avl_visitor_t visitor, void *param)
{
    int op_result = 0;
    assert(tree);
    assert(visitor);

    /*0 pass, else fail */
    op_result |= _ForEachAssistRec(ROOT, visitor, param);

    return op_result; 
}

/*_________________________________________________________________________________________________________ */

static int _ForEachAssistRec(avl_node_t *node, 
                                avl_visitor_t visitor, void *param)
{
    int op_result = 0;

    if(node->LEFT_CHILD)
    {
        op_result|=_ForEachAssistRec(node->LEFT_CHILD, visitor, param);
        if( 0 != op_result)
        {
            return op_result;
        }
    }

    op_result |= visitor(node->data, param); 
    if( 0 != op_result)
        {
            return op_result;
        }

    if(node->RIGHT_CHILD)
    {
       op_result |= _ForEachAssistRec(node->RIGHT_CHILD, visitor, param);
    }

    return op_result;
}

/*_________________________________________________________________________________________________________ */

/*ROOT, LEFT, RIGHT, "pre order" */
size_t AvlCount(const avl_t *tree)
{
    size_t count =0ul;

    assert(tree);

    if(ROOT)
    {
        _CountAssistRec(ROOT, &count);
    }

    return count;  
}

/*_________________________________________________________________________________________________________ */

static void _CountAssistRec(avl_node_t *node, size_t *count)
{
    ++*count;

    if(node->LEFT_CHILD)
    {
        _CountAssistRec(node->LEFT_CHILD, count);
    }
    if(node->RIGHT_CHILD)
    {
        _CountAssistRec(node->RIGHT_CHILD, count);
    }
}

/*_________________________________________________________________________________________________________ */

void *AvlFind(const avl_t *tree, void *key)
{
    avl_node_t *found = NULL;

    int compare_result = -1;

    assert(tree);
    
    if(ROOT)
    {                                  
       found = *(ParentFieldToChild((avl_t*)tree,(avl_node_t**)&ROOT,
        key, &compare_result));
    }

    /*if not found (or no root)*/
    if(compare_result)
    {
        return NULL;
    }

    return (found->data);
}

/*_________________________________________________________________________________________________________ */

ssize_t AvlHeight(const avl_t *tree)
{
    assert(tree);

    if( NULL == ROOT)
    {
        return -1;
    }

    else
    {
        return ROOT->height;
    }
}

/*_________________________________________________________________________________________________________ */

void AvlRemove(avl_t *tree, void *data)
{
	avl_node_t *next = NULL;
	avl_node_t **pointer_to_next = NULL;
    avl_node_t *to_remove = NULL;

    int next_compare_result = -1;

	assert(tree);
	
    to_remove = _RemoveFindRec(ROOT, tree->Compare, data, tree->param);

 	if( to_remove )
    {
 		/*if has 2 kids*/
 		if( to_remove->LEFT_CHILD && to_remove->RIGHT_CHILD )
 		{ 
 			next = GetNext(to_remove, tree);

            pointer_to_next = ParentFieldToChild(tree, &ROOT, next->data, &next_compare_result);

            if(next->LEFT_CHILD)
            {
                *pointer_to_next = next->LEFT_CHILD;
            }
            else if (next->RIGHT_CHILD)
            {
                *pointer_to_next = next->RIGHT_CHILD;
            }
            else
            {
                *pointer_to_next = NULL;
            }
            GetNext(to_remove, tree);
            to_remove->data =  next->data; 
 		}
         /*if has 1 kid */
        else if(to_remove->LEFT_CHILD) 
        {
            pointer_to_next = ParentFieldToChild(tree, &ROOT, to_remove->data, &next_compare_result);
            *pointer_to_next = to_remove->LEFT_CHILD;

            /*call func again to recursively update height */
           ParentFieldToChild(tree, &ROOT, to_remove->data, &next_compare_result);
            next = to_remove;
        }
        else if(to_remove->RIGHT_CHILD)
        {
            pointer_to_next = ParentFieldToChild(tree, &ROOT, to_remove->data, &next_compare_result);
            *pointer_to_next = to_remove->RIGHT_CHILD;
            
            /*call func again to recursively update height */
            ParentFieldToChild(tree, &ROOT, to_remove->data, &next_compare_result);

            next = to_remove;
        }
        /*if is leaf */
        else
        {
            next = to_remove;

            pointer_to_next = ParentFieldToChild(tree, &ROOT, next->data, &next_compare_result);
            *pointer_to_next= NULL;

             /*call func again to recursively update height */
            ParentFieldToChild(tree, &ROOT, next->data, &next_compare_result); 
        }
				
 		_DestroyNode(next);
     }	
} 

/*___________________________________________________________________________ */

/*will return pointer to pointer to node (thus giving us access to both 
    parent's pointer and node)*/
static avl_node_t **ParentFieldToChild(avl_t *tree, avl_node_t **parent_field_to_child, void *key, int *compare_result)
{
    *compare_result = tree->Compare((*parent_field_to_child)->data, key, tree->param);
    /*stopping condition: if match found or child is NULL return its parent's pointer   */
    if(!*compare_result || (!((*parent_field_to_child)->children[SIDE(*compare_result)])))
    {
        _UpdateNodeHeight(*parent_field_to_child);
        return parent_field_to_child;
    }

    _UpdateNodeHeight(*parent_field_to_child);
    /*else continue to child on this side */
    return(ParentFieldToChild(tree, (&(*parent_field_to_child)->children[SIDE(*compare_result)]), key, compare_result));

}

/*_________________________________________________________________________________________________________ */

static avl_node_t *GetNext(avl_node_t *to_remove, avl_t *tree)
{
    avl_node_t *next= NULL;
   
    if(to_remove->RIGHT_CHILD)
    {
        next = _GetMostChildRec(to_remove->RIGHT_CHILD, LEFT, tree);
    }
    
     _UpdateNodeHeight(to_remove);
    
    return next;
}

/*_________________________________________________________________________________________________________ */

static avl_node_t *_GetMostChildRec(avl_node_t *node, int side, avl_t *tree)
{
    if(node->children[side])
    {
        node = _GetMostChildRec(node->children[side] ,side, tree);
    }

    _UpdateNodeHeight(node);
    return node;
}

/*_________________________________________________________________________________________________________ */

static avl_node_t *_RemoveFindRec(avl_node_t *node, avl_compare_t compare, void *key, void *param)
{
    avl_node_t *found = NULL;

    /*if found */
    if(( 0 == compare(node->data, key, param)))
    {
        found = node;
    }
    /*searched key is smaller than node data */
    else if( 1 == compare(node->data, key, param))
    {
        if(node->LEFT_CHILD)
        {
            found = _RemoveFindRec(node->LEFT_CHILD, compare, key, param);
        }
        /*else already NULL */
    }
    /*searched key is bigger than node data */
    else if( -1 == compare(node->data, key, param))
    {
        if(node->RIGHT_CHILD)
        {
            found = _RemoveFindRec(node->RIGHT_CHILD, compare, key, param);
             /*else already NULL */
        }    
    }

    return found;
}

/*_________________________________________________________________________________________________________ */

static ssize_t _GetBalance(avl_node_t* node)
{
    if(!node)
    {
        return -1;
    }
   
   return (_GetNodeHeight(node->LEFT_CHILD) - _GetNodeHeight(node->RIGHT_CHILD));
}

/*_________________________________________________________________________________________________________ */

static ssize_t _GetNodeHeight(avl_node_t *node)  
{  
    if (node == NULL) 
    { 
        return -1; 
    } 
    return node->height;  
} 

/*_________________________________________________________________________________________________________ */

/*returns new root */
static avl_node_t *RotateRight(avl_node_t* root, avl_t *tree)
{
    avl_node_t *new_root = NULL;
    avl_node_t *left_child = /* init with NULL first  because of assert down
                             here */ root->LEFT_CHILD;
    avl_node_t **pointer_to_root = NULL;
    int cmp = -1;

    assert(root);

    root->LEFT_CHILD = left_child->RIGHT_CHILD;
    left_child->RIGHT_CHILD = root;

    new_root = left_child;

    pointer_to_root = ParentFieldToChild(tree, &ROOT, root->data, &cmp);
    *pointer_to_root = new_root; 

    return new_root;
}
/*_________________________________________________________________________________________________________ */

/*returns new root */
static avl_node_t *RotateLeft(avl_node_t* root, avl_t *tree)
{
    avl_node_t *new_root = NULL;
    avl_node_t *right_child = root->RIGHT_CHILD;
    avl_node_t **pointer_to_root = NULL;
    int cmp = -1;

    assert(root);

    root->RIGHT_CHILD = right_child->LEFT_CHILD;
    right_child->LEFT_CHILD = root;

    new_root = right_child;

    pointer_to_root = ParentFieldToChild(tree, &ROOT, root->data, &cmp);
    *pointer_to_root = new_root;

    return new_root;
}
