/**********************************************************************;
* Project           : Data Structures
*
* Program name      : bst.c
*
* Author            : Michelle Gelfand
*
* Date created      : 19.07.19
*
* Purpose           : This program provides the user
					  with a binary search tree
*
* Version           : 1.3
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 22/07/2019       	  Michelle Gelfand           Saar Y. *														  
*******************************************************************/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*memset*/

#include "bst.h"

#define LEFT 0
#define RIGHT 1

#define ROOT tree->dummy.LEFT_CHILD
#define LEFT_CHILD children[0] 
#define RIGHT_CHILD children[1]

struct bst_node
{
	void *data;
    bst_node_t *parent;
	bst_node_t *children[2];  
};

struct bst
{
	bst_node_t dummy;
    bst_compare_t compare;
    void *param;
};

/************ S  T  A  T  I  C **********************************/
static bst_iterator _FirstSideParentImp(bst_iterator iterator, int side)
{
	int is_found = 0;

	while(!is_found && iterator->parent)
	{
		if( BstIsSameIterator(iterator->parent->children[side], iterator) )		
		{
			is_found = 1;
		}

		iterator = iterator->parent;
	}

	if(!is_found)
	{
		iterator = NULL;
	}
	
	return iterator;
}

/******************************************************************************/
static bst_iterator SideMostChildImp(const bst_iterator iterator, int side)
{
	bst_iterator most_side_child = NULL;

	assert(iterator);

	most_side_child = iterator;

	while(most_side_child->children[side])
	{
		most_side_child = most_side_child->children[side];
	}

	return most_side_child;
}
/******************************************************************************/
static int CountImp(void* data, void *param)
{
    (void)data;
    ++*(size_t*)param;
    return 0;
}
/******************************************************************************/
static void _RealRemove(bst_iterator to_remove)
{
	to_remove->LEFT_CHILD = NULL;
	to_remove->RIGHT_CHILD = NULL;
	to_remove->parent = NULL;

	free(to_remove);
	to_remove = NULL;

}
/******************************************************************************/
static bst_iterator _CreateNewNode(void* data, bst_iterator parent, bst_iterator 
										left_child, bst_iterator right_child)
{
	bst_iterator new_node = (bst_iterator)malloc(sizeof(bst_node_t));
	
	if(new_node)
	{
		new_node->data = data;
		new_node->parent = parent;
		new_node->LEFT_CHILD  = left_child;
		new_node->RIGHT_CHILD = right_child;
	}
	return new_node;
}

/************************ A   P   I ******************************/
bst_t *BstCreate(bst_compare_t compare, void *param)
{
	bst_t *new_bst = NULL;
	
	bst_node_t dummy = {0}; 
	dummy.data = (void*)0xBADDCAFE;
	
	assert(compare);

	new_bst = (bst_t*)malloc(sizeof(bst_t));

	if(new_bst)
	{
		new_bst->dummy = dummy;
		new_bst->compare = compare;
		new_bst->param = param;
	}

	return new_bst;	
}
/******************************************************************************/
void BstDestroy(bst_t *tree)
{
	assert(tree);

	while(!BstIsEmpty(tree))
	{
		BstRemove(tree ,BstBegin(tree));
	}

	free(tree);
}
/******************************************************************************/
/*0 is smaller, 1 is bigger*/
bst_iterator BstBegin(const bst_t *tree)
{
	bst_iterator begin = NULL;	

	assert(tree);

	begin = SideMostChildImp(BstEnd(tree), LEFT);

	return begin;
}
/******************************************************************************/
bst_iterator BstEnd(const bst_t *tree)
{
	assert(tree);

	return (bst_iterator)(&(tree->dummy));

}
/******************************************************************************/
int BstIsEmpty(const bst_t *tree)
{
	assert(tree);
	
	return (!ROOT);
	
}
/******************************************************************************/
int BstIsSameIterator(const bst_iterator first, const  bst_iterator second)
{
	return (!!(first == second));
}
/******************************************************************************/
void *BstGetData(bst_iterator iterator)
{
	assert(iterator);

	return (iterator->data);
}
/******************************************************************************/
void BstRemove(bst_t *tree, bst_iterator to_remove)
{
	int remove_side = 0;
	bst_iterator replacer = NULL;
	bst_iterator parent = NULL;

	assert(tree);
	assert(to_remove);

	if( !BstIsSameIterator(to_remove, BstEnd(tree)) )
	{
		parent = to_remove->parent;

		/*return if to_remove is 0 or 1 (which side child)*/
		remove_side =
			 BstIsSameIterator((parent->RIGHT_CHILD), to_remove);

		/*if has kids*/
		if( to_remove->LEFT_CHILD || to_remove->RIGHT_CHILD )
		{ 
			parent->children[remove_side] = to_remove->LEFT_CHILD;
			
			if(to_remove->LEFT_CHILD)
			{
				replacer = SideMostChildImp(to_remove->LEFT_CHILD , RIGHT);
				replacer->RIGHT_CHILD = to_remove->RIGHT_CHILD;
		
				if(to_remove->RIGHT_CHILD)
				{
					to_remove->RIGHT_CHILD->parent = replacer;				
				}
				
				if(to_remove->LEFT_CHILD)
				{
					to_remove->LEFT_CHILD->parent = parent;
				}
			}
			else
			{
				/*if no left child*/
				parent->children[remove_side] = to_remove->RIGHT_CHILD;
				
				if(to_remove->RIGHT_CHILD->parent)
				{
					to_remove->RIGHT_CHILD->parent = parent;
				}			
			}
		}
		else
		{
			parent->children[remove_side] = to_remove->LEFT_CHILD;
		}		
		
		_RealRemove(to_remove);	
	}
}
/******************************************************************************/
bst_iterator BstNext(bst_iterator iterator)
{
	if( iterator && iterator->children[RIGHT])
	{
		iterator = SideMostChildImp(iterator->children[RIGHT], LEFT);
	}
	else
	{
		/*else if no right child, go up until first left parent*/
		iterator = (bst_iterator)_FirstSideParentImp(iterator, LEFT);
	}
	
	return iterator;	
}
/******************************************************************************/
bst_iterator BstPrev(bst_iterator iterator)
{
	bst_iterator prev = NULL;

	assert(iterator);

	if(iterator->LEFT_CHILD)
	{
		prev = SideMostChildImp(iterator->LEFT_CHILD, RIGHT);
	}

	/*else if no left child, go up until first right parent*/
	else
	{
		prev = (bst_iterator)_FirstSideParentImp(iterator, RIGHT);
	}
	
	return prev;	
}
/******************************************************************************/
int BstForEach(bst_iterator from, bst_iterator to,
 					bst_visitor_t visitor, void*param)
{
	bst_iterator current = from;
	int op_result = 0;

	assert(from);
	assert(to);
	assert(visitor);

	while(!BstIsSameIterator(to, current) &&(0 == op_result) ) 
	{
		op_result |= visitor(current->data, param);
		current = BstNext(current);
	}

	return op_result;
}
/******************************************************************************/
size_t BstCount(const bst_t *tree)
{
	size_t count = 0ul;

	assert(tree);

	BstForEach(BstBegin(tree), BstEnd(tree), CountImp, &count);

	return count;
}
/******************************************************************************/
static bst_iterator _FindImp(bst_t *tree, void *data)
{
	bst_iterator finder = ROOT;
	int found = 0;

	/*can only insert as leaf!*/
	while( ( NULL != finder) && (1 != found) )
	{
		found = tree->compare(finder->data, data, NULL);

		if( 0 == found)
		{
			found = 1;
		} 
		else if( 1 == found)
		{
			finder = finder->LEFT_CHILD;
		} 

		else if( -1 == found)
		{
			finder = finder->RIGHT_CHILD;
		}	 
	}	

	return finder; 	
}
/******************************************************************************/
static bst_iterator _InsertFindImp(bst_t *tree, void *data, int *side)
{
	bst_iterator finder = NULL;
	bst_iterator finder_parent = NULL; 
	int traverser = 0;

	if(ROOT)
	{
		finder_parent = ROOT->parent;
		finder = ROOT;
		/*can only insert as leaf!*/
		while( NULL != finder )
		{
			traverser = tree->compare(finder->data, data, NULL);
	 
			if( 1 == traverser )
			{
				*side = LEFT;
				finder_parent = finder;
				finder = finder->LEFT_CHILD;
			} 

			else if( -1 == traverser )
			{
				*side = RIGHT;	
				finder_parent = finder;
				finder = finder->RIGHT_CHILD;
			}
			else if( 0 == traverser)
			{
				*side = -1;
				break;
			}
			
		}
		finder = finder_parent;	
	}
	else
	{
		*side = LEFT;
		finder = BstEnd(tree);
	}

	return finder; 	
}
/******************************************************************************/
bst_iterator BstFind(bst_t *tree, void *data)
{
	bst_iterator finder = NULL;
	assert(tree);			

	finder  = (bst_iterator)_FindImp(tree, data);
	if( BstEnd(tree) == finder )
	{
		finder = NULL;
	} 

	return finder;
}
/******************************************************************************/
bst_iterator BstInsert(bst_t *tree, void *data)
{
	bst_iterator where_to_insert = NULL;	
	bst_iterator new_node = NULL;
	int side = 0;

	assert(tree);

	new_node = _CreateNewNode(data, NULL, NULL, NULL);

	if(new_node)	
	{
		where_to_insert = _InsertFindImp(tree, data, &side);
		
		/*flag that data already exists in tree*/
		if( -1 == side)
		{
			_RealRemove(new_node);
			new_node = BstEnd(tree);
		}

		else if(where_to_insert)
		{
			where_to_insert->children[side] = new_node;
			new_node->parent = where_to_insert;
		}
		else
		{
			_RealRemove(new_node);
		}
	}

	return new_node;
}





