/************************************************************************
* Project           : Data Structures (CircularBuffer)	 	            *
*										                                *
* Program name      : CircularBuffer Functions                          *
*										                                *
* Version           : 1.1						                    	*
*										                                *
* Date created      : 12.06.19						                    *
*										                                *
* Purpose           : Define Circular funcs: Create, Destroy, Read,     *	  
*			          Write, Capacity, IsEmpty, FreeSpace		        *
*                								                        *
*										                                *
* Reviewer			: Inbar Duek              				                    *
*										                                *
* Date Approved 	:  08/06/2019          		        	            *
*                       							                    *	
************************************************************************/

#ifndef __CBUFF_H__
#define __CBUFF_H__

#include <stddef.h> /* size_t */
#include <unistd.h> /*ssize_t */


typedef struct circular_buffer cbuff_t;

/*----------------------------------------------------------------------------*/

/* Creates new circular buffer. 
                                             
ARGS: 
- n_bytes - max allowed bytes in the Circular Buffer (must be > 0)				   
 
RETURNS: pointer to a Circular Buffer or NULL if creation failed              */
cbuff_t *CBuffCreate(size_t n_bytes);
 
/*----------------------------------------------------------------------------*/

/* Destroy, frees all allocated memory for this Circular Buffer. 
                                            
ARGS: 
- CircularBuffer - pointer to existing Circular Buffer				   
 
RETURNS: none.                                                                */
 
void CBuffDestroy(cbuff_t *c_buff);
/*----------------------------------------------------------------------------*/

/* Reads from circular buffer to dest   
                                          
ARGS: 
- CircularBuffer - pointer to the existing Circular Buffer
- dest - where to store the value read from circular buffer
- n_bytes - number of bytes to read
			   
RETURNS: number of bytes read , for no data (errno ENODATA)                

It is not an  error  if  this
       number  is smaller than the number of bytes requested */
ssize_t CBuffRead(cbuff_t *c_buff, void *dest, size_t n_bytes);
/*----------------------------------------------------------------------------*/

/* Circular Buffer Write: writes to buffer from src.

ARGS: 
- Circular Buffer - pointer to the existing Circular Buffer
- src - source of data to copy to buffer
- n_bytes - number of bytes to write

RETURN: number of bytes written, for overflow (errno EOVERFLOW)

It is not an error if  this  number  is  smaller
       than the number of bytes requested */
ssize_t CBuffWrite(cbuff_t *c_buff,const void *src, size_t n_bytes);
 
/*----------------------------------------------------------------------------*/ 
 
/* Circular Buffer Capacity .
 
ARGS: 
- Circular Buffer - pointer to the existing Circular Buffer	

RETURN: number of bytes in circular buffer                                    */
 
size_t CBuffCapacity(const cbuff_t *c_buff);
/*----------------------------------------------------------------------------*/ 
 
/*Circular Buffer Is Empty. 

ARGS: 
-Circular Buffer - pointer to the existing Circular Buffer

RETURN : 1 if buffer is empty, else 0                                         */
int CBuffIsEmpty(const cbuff_t *c_buff);
 
/*----------------------------------------------------------------------------*/ 

/* Circular Buffer Free Space.
 
ARGS: 
-Circular Buffer - pointer to the existing Circular Buffer

RETURN: Number of free bytes in circular buffer, available for writing        */
size_t CBuffFreeSpace(const cbuff_t *c_buff);

/*----------------------------------------------------------------------------*/
#endif /* __CBUFF_H__ */
