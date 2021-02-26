/******************************************************************************/
/*	File:		fsm.h											              */
/*	Created:	7.07.19 													  */
/*  Version: 	1.2  														  */
/*	Modified:																  */
/*	Author:		Doron Weitzman 									              */
/*																			  */
/*	Brief:		FSM Functions:				FsmInit	         				  */
/*										   	FsmAlloc                          */
/*											FsmFree					     	  */	
/*							  				FsmCountFree                      */
/*											FsmSuggestSize                    */
/*																  			  */ 	
/******************************************************************************/

/* log:

	v1.1 - undefined behaviour of init function changed. 
		  (capacity is smaller than block_size + word size)

		  removed 'const' from mem_area in FsmCountFree

	v1.2 - undefined behaviour of init function changed. 
		  (capacity is smaller than 2 word size ( when block_size < word size)
*/

#ifndef __FSM_H__
#define __FSM_H__


#include <stddef.h> /* size_t */

typedef struct mem_area mem_area_t;

/*
typedef struct free_block
{
	struct free_block *next;
	
}free_block_t;


struct mem_area
{
	free_block_t *head;
	
};
*/
/*******************************************************************************

FsmInit - creates memory management system for user's memory area.

  		  note : Undefined behaviour if block_size is bigger than capacity
			     or when capacity is smaller than block_size + word size
				and smaller than 2 word size ( when block_size < word size)
						     
ARGS - mem_area 		: pointer to user's memory area (must be word alligned)
	   capacity_bytes   : memory area's size in bytes
	   block_size       : memory block's size in bytes
	   
RETURN - SUCCESS : pointer to built memory area							*/												 
mem_area_t *FsmInit(void *mem_area, size_t capacity_bytes, size_t block_size);

/*******************************************************************************

FsmAlloc - allocates a block of memory of a specific size as defined by user.

ARGS - mem_area : pointer to user's memory area

RETURN - SUCCESS : pointer to allocated memory block (word alligned)
	     FAIL    : NULL														  */

void *FsmAlloc(mem_area_t *mem_area);

/*******************************************************************************

FsmFree - frees an allocated block of memory.
		  note : Undefined behaviour if block is not located in memory area.
		  
ARGS - mem_area : pointer to user's memory area.
	   block    : pointer to allocated memory block. 

RETURN - none.
																	    	  */
void FsmFree(mem_area_t *mem_area, void *block);

/*******************************************************************************

FsmCountFree - counts the number of free blocks available for allocation.

ARGS - mem_area : pointer to user's memory area

RETURN - number of free blocks
	   																		  */

size_t FsmCountFree (mem_area_t *mem_area);

/*******************************************************************************

FsmSuggestedSize - calculates the minimal memory area size required to 
				   contain the desired number of blocks of the size specified
				   (word alligned).

ARGS - block_size : memory block's size in bytes
	   n_blocks   : number of blocks required

RETURN - suggested size of memory area in bytes.							  */
	     
size_t FsmSuggestedSize (size_t block_size, size_t n_blocks);


#endif /* __FSM_H__ */

