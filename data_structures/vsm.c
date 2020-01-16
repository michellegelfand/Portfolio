/**********************************************************************;
* Project           : Data Structures
*
* Program name      : vsm.c
*
* Author            : Michelle Gelfand
*
* Date created      : 09.07.19
*
* Purpose           : This program provides the user
					  with a dynamic size allocatable memory segment.
*
* Version           : 1.1.2
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 11/07/2019       	  Michelle Gelfand           Assaf B. *														  
*******************************************************************/
#include <assert.h> /* assert */
#include <stddef.h> /* NULL */
#include <stdlib.h> /* labs  */ 

#include "vsm.h"

#define WORD_SIZE sizeof(size_t)
#define HEAD_SIZE sizeof(vsm_mem_pool_t) 

/*macros to set blocks by WORD_SIZE*/
#define NEEDS_ALIGN (block_size + WORD_SIZE - (block_size % WORD_SIZE) ) 
#define ALIGNED_BLOCK_SIZE (( block_size % WORD_SIZE) ? \
							(NEEDS_ALIGN) : (block_size) )

struct vsm_mem_pool
{
	#ifndef NDEBUG 				
		size_t magic_number;
	#endif /*NDEBUG*/

	ssize_t size;
};


#ifndef NDEBUG

	#include <stdio.h>/*printf*/	

	void PrintPool(void *memory)
	{
		int seg_num = 1;

		vsm_mem_pool_t* current_head = (vsm_mem_pool_t*)memory;	

		printf("\n\nNow Printing Segment Heads:\n");	
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

		while( 0 != current_head->size )
		{
			printf("\nseg num: %d : size: %ld\n", seg_num, current_head->size);
			printf("\n magic: %X\n",(unsigned)current_head->magic_number);

			current_head = (vsm_mem_pool_t*)( (char*)current_head + 
										 labs(current_head->size) + HEAD_SIZE);
			++seg_num;
		}

		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}

#else
	#define PrintPool(memory)
#endif /*NDEBUG*/

vsm_mem_pool_t *VsmInit(void *memory, size_t pool_size)
{
	/*place head & tail at start and end of mem pool*/
	vsm_mem_pool_t *mem_pool_head = (vsm_mem_pool_t*)memory;  
	vsm_mem_pool_t *mem_pool_tail = (vsm_mem_pool_t*)( (char*)memory + 
									(pool_size - HEAD_SIZE) );
	assert(memory);
	assert (5 * WORD_SIZE <= pool_size); 

	mem_pool_head->size = pool_size - (2 * HEAD_SIZE);
	mem_pool_tail->size = 0;

	#ifndef NDEBUG 
		mem_pool_head->magic_number = 0xBADDCAFE;
		mem_pool_tail->magic_number = 0xBADDCAFE;
	#endif /*NDEBUG*/

	PrintPool(memory);

	return (vsm_mem_pool_t*)memory;
}


/*succesful alloc returns pointer to memory block, fail returns null.
each alloc is aligned to WORD_SIZE and if a gap of an unallocated segment
of less than 1 struct + wordsize remains, we allocate that as well to assure we dont get
a head of size zero mid pool 
minus num is occupied space, positive if free */

void *VsmAlloc(vsm_mem_pool_t *vsm_mem_pool, size_t block_size)
{
	size_t space_needed = ALIGNED_BLOCK_SIZE + HEAD_SIZE + WORD_SIZE; 
	vsm_mem_pool_t *start_head = vsm_mem_pool;
	vsm_mem_pool_t *next_head = NULL;
	vsm_mem_pool_t *new_head = NULL;
	int is_found = 0;
	size_t sum = 0;

	assert(vsm_mem_pool);

	if(0 < (start_head->size))
	{
		sum = (start_head->size);
	}

	while( (0 != start_head->size) && (0 < block_size) )
	{
		/*if match found*/
		if( space_needed <= sum )
		{
			/*place new head and set its size*/
			new_head = (vsm_mem_pool_t*)((char*)start_head + 
						space_needed - WORD_SIZE);
			new_head->size = sum - space_needed + WORD_SIZE;  

			#ifndef NDEBUG 
				new_head->magic_number = 0xBADDCAFE;
			#endif /*NDEBUG*/

			/*set in header aligned requested size occupied*/
			start_head->size = (-1l) * (ssize_t)ALIGNED_BLOCK_SIZE;
			
			is_found = 1;
			break;
		}

		/*if seg is free but too small*/
		else if( 0 < (start_head-> size)) 
		{
			next_head = (vsm_mem_pool_t*)( (char*)start_head  + 
							 			   (start_head->size) + HEAD_SIZE );

			/*sum up all following unalloc'd chunks*/
			while( ((ssize_t)0 < (next_head-> size) ))
			{
				/*add them up*/
				sum += (next_head->size) + HEAD_SIZE;
				
				next_head = (vsm_mem_pool_t*)( (char*)next_head  + 
							 				   (next_head->size) + HEAD_SIZE);
			}
		}

		/*if space is large enough only if we dont include a new head*/
		if( (  start_head->size < (ssize_t)space_needed)         &&
			(  start_head->size >= (ssize_t)ALIGNED_BLOCK_SIZE ) && 
			( (sum < space_needed) || ((ssize_t)sum ==  start_head->size) ) )
		{
			start_head->size *= (-1);
			is_found = 1;
			break;
		}

		/*if chunk unalloc'd or size too small after summing consecutive frees*/
		if( 0 > (start_head-> size)  || (space_needed > sum)) 
		{
			sum = 0;
		
			/*get start_head to next unoccupied chunk*/
			do 
			{	/*jump start to next head*/
				start_head = (vsm_mem_pool_t*)( (char*)start_head + 
						 				    labs(start_head->size) + HEAD_SIZE);
			}
			while( (start_head->size < 0) && ( 0 != start_head->size ));

			sum += start_head->size;
		}
	}
	
	PrintPool(vsm_mem_pool);
	
	if ( 0 == is_found)
	{
		return NULL;
	}
	
	return (void*)((char*)start_head + HEAD_SIZE);
}

/*frees an allocated block of memory.
  Undefined behaviour if block is not located in memory area. */

void VsmFree(void *block)
{
	assert(block);
	
	block = (vsm_mem_pool_t*)((char*)block - HEAD_SIZE);

	/*minus num means allocated. to turn to free must turn to plus.
	  extra safety layer -  if user tries to free freed block
	  it doesnt change anything*/
	((vsm_mem_pool_t*)block)->size = labs(((vsm_mem_pool_t*)block)->size);
}

