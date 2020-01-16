/**********************************************************************;
* Project           : Data Structures
*
* Program name      : hashtable.c
*
* Author            : Michelle Gelfand
*
* Purpose           : This program provides the user with
*					  a hash table data structure	
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 04/08/2019       	  Michelle Gelfand           Olga K.														  
*******************************************************************/

#include <stdlib.h> /*malloc, size_t */
#include <assert.h>/*assert */
#include <string.h>/*strcmp */

#include "doubly_list.h"
#include "hashtable.h"


static int _AllocTable(dl_list_t ** table, size_t capacity);
static void _DeallocTable(dl_list_t **table, size_t capacity);

struct hash_table 
{
    size_t capacity;
    hash_func_t hash_func;
	ismatch_t is_match;
	void *param;
	dl_list_t **table;

};

hash_t *HashCreate(size_t capacity, hash_func_t hash_func, 
				   ht_ismatch_t is_match, void *param)
{
	hash_t *hash = NULL;
	dl_list_t **table = NULL;

	assert(capacity);
	assert(hash_func);
	assert(is_match);

	hash = (hash_t*)malloc(sizeof(hash_t));
	table = (dl_list_t**)malloc(capacity * sizeof(dl_list_t*));

	if(hash)
	{
		if(table)
		{
			hash->table = table;

			/*create table */
			if(_AllocTable(table, capacity))
			{
				/*if failed */
				HashDestroy(hash);
			}
			else
			{
				hash->capacity = capacity;
				hash->param=param;
				hash->is_match=is_match;
				hash->hash_func = hash_func;
			}
		}
		else
		{
			free(hash);
		}
	}

	return hash;
}

/*success returns 0, else 1 */
static int _AllocTable(dl_list_t ** table, size_t capacity)
{
	size_t idx = 0;
	int status = 0;

	assert(capacity);
	assert(table);

	for(idx = 0; idx < capacity; ++idx)
	{
		table[idx] = DListCreate();

		if(!table[idx])
		{
			status |= 1;
			break;
		}
	}

	return status;
}

void HashDestroy(hash_t *hash)
{
	assert(hash);

	_DeallocTable(hash->table, hash->capacity);
	free(hash->table);

	hash->table = NULL;
	hash->hash_func = NULL;
	hash->is_match = NULL;
	hash->param = NULL;

	free(hash);
	hash = NULL;
}

static void _DeallocTable(dl_list_t **table, size_t capacity)
{
	size_t idx = 0;

	assert(table);
	assert(capacity);

	for(idx =0; idx<capacity; ++idx)
	{
		if(table[idx])
		{
			DListDestroy(table[idx]);
		}
		table[idx] = NULL;
	}
}
hash_status_t HashInsert(hash_t *hash, void *data)
{
	size_t table_idx = 0;
	assert(hash);

	table_idx = hash->hash_func(data) % hash->capacity;

	/*push new data, then check if op was succesful */
	if(DListPushFront(hash->table[table_idx], data) !=
						 DListEnd(hash->table[table_idx]))
	{
		return HASH_SUCCESS;
	}

	return HASH_FAIL;
}
int HashIsEmpty(const hash_t *table)
{
	int is_empty = 0;
	size_t idx = 0;

	assert(table);


	for(idx = 0; idx < table->capacity; ++idx)
	{
		 is_empty -= !DListIsEmpty(table->table[idx]);
	}

	if(0 > is_empty)
	{
		is_empty = 1;
	}
	else
	{
		is_empty = 0;
	}
	
	return !is_empty;
}
 
size_t HashSize(const hash_t *hash)
{
	size_t idx = 0;
	size_t size = 0;

	assert(hash);

	for(idx = 0; idx < hash->capacity; ++idx)
	{
		size += DListCount(hash->table[idx]);
	}

	return size;
}

void *HashFind(const hash_t *table, void *data)
{
	size_t idx = 0;
	iterator_t found = NULL;

	assert(table);

	idx = table->hash_func(data);

	found = DListFind(DListBegin(table->table[idx]),DListEnd(table->table[idx]),
	table->is_match, table->param, data);

	if( NULL != found)
	{
		return DListGetData(found);
	}
	
	return NULL;
}
int HashForEach(hash_t *table , hash_visitor_t visitor, void *param)
{
	size_t idx = 0;
	int op_res = 0;
	assert(visitor);
	assert(table);

	for (idx = 0; idx < table->capacity; ++idx)
	{
		op_res = DListForEach(DListBegin(table->table[idx]),DListEnd(table->table[idx]),
		 visitor, param);
		if( 0 != op_res)
		{
			break;
		}
	}

	return op_res;
}

void HashRemove(hash_t *table, void *data)
{
	iterator_t to_remove = NULL;
	size_t idx = 0;
	assert(table);

	for(idx = 0; idx < table->capacity; ++idx)
	{
		to_remove = DListFind(DListBegin(table->table[idx]),DListEnd(table->table[idx]), 
		table->is_match, table->param, data);

		if( NULL != to_remove)
		{
			DListRemove(to_remove);
			break;
		}
	}
}
