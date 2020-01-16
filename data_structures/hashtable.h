/**
 * File:       hashtable.h 
 * Created:    01.08.19
 * Version:    1.1
 * 
 */

#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stddef.h> /* size_t */

/* TODO: in the c file

#include "doubly_list.h"

typedef struct hash_table 
{
    size_t capacity;
    hash_func_t hash_func;
 	ht_ismatch_t is_match;
	void *param;
	dl_list_t **table;

};
*/

/*
 * visitor return: on error: non zero
 *                 on success: 0 
 */
typedef int (*hash_visitor_t)(void *data, void *param);

typedef size_t (*hash_func_t)(const void *data);

/*returns 1 if data1 = data2, 0 otherwise*/
typedef int (*ht_ismatch_t)(const void *data1, void *param, const void *data2);

typedef struct hash_table hash_t;

typedef enum hash_status
{
    HASH_SUCCESS,
    HASH_FAIL

}hash_status_t;

/******************************************************************************/
/*
  RETURNS: 	Success: pointer to a hash table 
			Failure: NULL   	
 */
hash_t *HashCreate(size_t capacity, hash_func_t hash_func, 
				   ht_ismatch_t is_match, void *param);
/******************************************************************************/
/**
 * 
 */
void HashDestroy(hash_t *table);
/******************************************************************************/
/*
	RETURNS: 	Success: HASH_SUCCESS
				Failure: HASH_FAIL  	
 */
 hash_status_t HashInsert(hash_t *table, void *data);
/******************************************************************************/
 /**

 */
void HashRemove(hash_t *table, void *data);
/******************************************************************************/
/**
	RETURNS: 	void *data if data found
				otherwise NULL  
 */
void *HashFind(const hash_t *table, void *data);
/******************************************************************************/
/**
 	RETURNS: 	1 if empty
				0 if not empty
 */
int HashIsEmpty(const hash_t *table);
/******************************************************************************/
/**
 * 
 */
size_t HashSize(const hash_t *table);
/******************************************************************************/
/**
 * RETURNS:	Status of the last action performed.			      
 */
int HashForEach(hash_t *table , hash_visitor_t visitor, void *param);
/******************************************************************************/

#endif /* __HASHTABLE_H__ */

