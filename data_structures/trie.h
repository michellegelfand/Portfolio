/*
*   @File:      Trie.h
*   @Created:   13.08.19
*   @Version:    1.0
*
*
*/                                                   
                                                   

#ifndef __trie_H__
#define __trie_H__

#include <stddef.h> /* size_t */

#include "bit_array.h"

typedef struct trie_node trie_node_t;
typedef struct trie trie_t;



/* RETURN - pointer to new tree  */

trie_t *TrieCreate(size_t tree_height);

/******************************************************************************/

/* RETURN: none. */

void TrieDestroy(trie_t *trie);

/******************************************************************************/

/* RETURN: number of paths in a Trie */

size_t TrieCount(const trie_t *trie);


/* RETURN:      trie_SUCCESS 
                trie_FAIL    

*/
int TrieInsert(trie_t *trie, bit_array_t requested_address,
     bit_array_t *recieved_address ,int *result);

/******************************************************************************/

/*	RETURN:    none.

*/
void TrieRemove(trie_t *trie, bit_array_t path);



#endif /* __trie_H__*/
