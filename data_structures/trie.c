/**********************************************************************;
* Project           : Data Structures
*
* Program name      : Trie.c
*
* Author            : Michelle Gelfand
*
* Date created      : 14.08.19
*
* Date Approved       Author	 	             Reviewer 
* 15/08/2019       	  Michelle Gelfand           Katy C. *														  
*******************************************************************/

#include <stdlib.h>/*malloc*/
#include <string.h>/*memset*/
#include <assert.h>/*assert */

#include "trie.h"


#define FREE(str) memset(str, 0, sizeof(*str)); free(str);
#define LEFT_CHILD children[0]
#define RIGHT_CHILD children[1]

static trie_node_t *NodeCreate(int value, trie_node_t *parent);
static void RemoveUpTree(trie_node_t *parent);
static void TrieDestroyRec(trie_node_t *node);
static void NodeDestroy(trie_node_t *node);

#ifndef NDEBUG
static void PrintTree(trie_node_t * root, int space);
#endif

struct trie_node
{
	trie_node_t *children[2];
    trie_node_t *parent;
	int value; 
	int is_subtree_full;
};

struct trie
{
	trie_node_t *dummy;
    size_t height;
    size_t count;
};

trie_t *TrieCreate(size_t height)
{
    trie_t *new_trie = (trie_t*)malloc(sizeof(trie_t));

    if(new_trie)
    {
        new_trie->dummy =  NodeCreate(9, NULL);
        new_trie->height = height;
        new_trie->count = 0;

        if(!(new_trie->dummy))
        {
            FREE(new_trie);
        }
    }

    return new_trie;
}

static trie_node_t *NodeCreate(int value, trie_node_t *parent)
{
    trie_node_t *new_node = (trie_node_t*)malloc(sizeof(trie_node_t));

    if(new_node)
    {
        new_node->LEFT_CHILD = NULL;
        new_node->RIGHT_CHILD = NULL;
        new_node->parent = parent;
        new_node->value= value;
        new_node->is_subtree_full = 0;
    }

    return new_node;
}

int TrieInsert(trie_t *trie, bit_array_t requested_address,
     bit_array_t *recieved_address, int *result)
{
    trie_node_t *path_finder = NULL;
    trie_node_t *path_finder_parent =NULL;
    int side = 0;
    size_t depth_traveled = 0;
    int subtree_full = 0;

    assert(trie);

    path_finder = trie->dummy;
    path_finder_parent =  trie->dummy;
    
    for(; depth_traveled < trie->height; ++depth_traveled)
    {
        path_finder_parent = path_finder;
        side = BitArrayIsBitOn(requested_address, trie->height -depth_traveled);

        if( NULL == path_finder->children[side]) 
        {
           path_finder = NodeCreate(side, path_finder);
           path_finder_parent->children[side] = path_finder;

           if(!path_finder)
           {
               RemoveUpTree(path_finder_parent);
              /*  PrintTree(trie->dummy, 5); */
               return 1;
           }

           if(trie->height - 1 == depth_traveled)
           {
               path_finder->is_subtree_full = 1;     
           }
        }
        else if(path_finder->children[side]->is_subtree_full)
        {
            subtree_full =1;
            break;
        }  
        else
        {
            path_finder_parent= path_finder;
            path_finder = path_finder->children[side];
        }

        *recieved_address = BitArraySetBit(*recieved_address, 
                trie->height - depth_traveled, side);
    }

    if(subtree_full)
    {
        *result = 1;
        return TrieInsert(trie, ++requested_address,
                                recieved_address, result);
    }

    ++trie->count;

    #ifndef NDEBUG
    PrintTree(trie->dummy, 5);
    #endif
    
    /* PrintBitArray(*recieved_address);    */
    return *result;
}

void TrieDestroy(trie_t *trie)
{
    TrieDestroyRec(trie->dummy);
    FREE(trie);
}

static void TrieDestroyRec(trie_node_t *node)
{
    if(NULL == node)
    {
        return;
    }

    TrieDestroyRec(node->LEFT_CHILD);
    TrieDestroyRec(node->RIGHT_CHILD);
    NodeDestroy(node);
}

static void NodeDestroy(trie_node_t *node)
{
    FREE(node);
}

static void RemoveUpTree(trie_node_t *parent)
{
    trie_node_t *to_remove = parent;

    while(!!(to_remove->RIGHT_CHILD && to_remove->LEFT_CHILD))
    {
        FREE(to_remove);
        to_remove= parent;
        parent = to_remove->parent;
    }
}

void TrieRemove(trie_t *trie, bit_array_t path)
{
    size_t depth_traveled = 0;
    int side = 0;
    trie_node_t *path_traverser = trie->dummy;

    for(; depth_traveled<trie->height; ++depth_traveled)
    {
        side = BitArrayIsBitOn(path,  trie->height - depth_traveled );
        path_traverser = path_traverser->children[side];
    } 

    RemoveUpTree(path_traverser);
    --trie->count;
}

size_t TrieCount(const trie_t *trie)
{
    if(!trie)
    {
        return 0;
    }
    return ((trie_t*)trie)->count;
}
/********** P  R  I  N  T *************************************/
#ifndef NDEBUG
#include <stdio.h>
static void PrintTree(trie_node_t * root, int space) 
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
         printf("%d \n ", (root->value)); 
    }

     PrintTree(root->LEFT_CHILD, space);
}

#else
#define PrintTree(root, space);
#endif

/*____________________________________________________________________________*/