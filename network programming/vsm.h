/*******************************************************************************
*	File:		vsm.h											               *
*	Author:		Olga Komarovsky Chashka							               *
*	Created:	8.07.19 													   *
*   Version: 	1.0 														   *
*	Modified:	-															   *
*	Reviewer:	-												  			   *
*																			   *
*	Brief:		VSM Functions:				VsmInit	         				   *
*										   	VsmAlloc                           *
*											VsmFree					     	   *	
*																  			   * 	
*******************************************************************************/

#ifndef __VSM_H__
#define __VSM_H__

#include <sys/types.h> /* ssize_t */

typedef struct vsm_mem_pool vsm_mem_pool_t;

/*
struct vsm_mem_pool
{
	ssize_t size;
	size_t magic_number;  DEBUG ONLY
}
*/


/*******************************************************************************

VsmInit - creates memory management system for user's memory area.

  		  note : Undefined behaviour if pool size is
					 smaller than 3 word size
						     
ARGS - memory 		 : pointer to user's memory area (must be word aligned)
	   pool_size  	 : memory pool's size in bytes
	   
RETURN - SUCCESS : pointer to built memory pool								  */	
											 
vsm_mem_pool_t *VsmInit(void *memory, size_t pool_size);

/*******************************************************************************

VsmAlloc - allocates a block of memory of a requested size as 
		   defined by the user.

ARGS -  vsm_mem_pool : pointer to user's memory area
		block_size: required allocation size

RETURN - SUCCESS : pointer to allocated memory block (word aligned)
	     FAIL    : NULL														  */

void *VsmAlloc(vsm_mem_pool_t *vsm_mem_pool, size_t block_size);

/*******************************************************************************

VsmFree - frees an allocated block of memory.
		  note : Undefined behaviour if block is not located in memory area.
		  
ARGS - block    : pointer to allocated memory block. 

RETURN - none.
																	    	  */
void VsmFree(void *block);



#endif /* __VSM_H__ */
