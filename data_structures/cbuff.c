/**********************************************************************;
* Project           : Data Structures
*
* Program name      : cbuff.c
*
* Author            : Michelle Gelfand
*
* Date created      : 13.06.19
*
* Purpose           : This program provides the user with a circular
*					  buffer to write and read from, as well as 
*					  additional operations		 				  
*
* Review Status		: Approved
*
* Date Approved        Author			          Reviewer 
* 15.06.19		       Michelle Gelfand           Inbar Duek   *														  
**********************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h>/*assert*/
#include <errno.h>/*errno*/
#include <string.h>/*memcpy#*/

#include "cbuff.h"

static void AdvanceWrite(cbuff_t *c_buff);
static void AdvanceRead(cbuff_t *c_buff);

struct circular_buffer
{
	size_t capacity;
	char *write; 
	char *read;
	char data[1];
};


/*****************************************************************************/
cbuff_t *CBuffCreate(size_t n_bytes)
{
	cbuff_t *c_buff = NULL;

	assert (n_bytes);

	/*minus size_t because data takes up size_t because of padding*/
	/*+1 for extra byte sp we dont need IsEmpty flag in struct*/
	/*if read is on write buffer empty, if write is 1 before read
	  buffer is full*/
	c_buff = (cbuff_t*)malloc( ( sizeof(cbuff_t) - sizeof(size_t) ) 
								+ (n_bytes + 1) );
	if ( NULL != c_buff )
	{
		c_buff -> capacity = n_bytes;
		c_buff -> read = c_buff -> data;
		c_buff -> write = c_buff -> read;
	}

	return c_buff;		

}
/*****************************************************************************/
void CBuffDestroy(cbuff_t *c_buff)
{
	assert ( c_buff );

	c_buff -> write = NULL;
	c_buff -> read  = NULL;
	
	free(c_buff);
	c_buff = NULL;

}

/*****************************************************************************/
ssize_t CBuffRead(cbuff_t *c_buff, void *dest, size_t n_bytes)
{	
	ssize_t copied = 0;
	size_t original_n_bytes = n_bytes;
	int i = 0;

	assert(c_buff);
	assert(n_bytes);

	/*while bytes left to copy and write and read not on same byte*/
	while ( (n_bytes) && (c_buff -> write != c_buff -> read) )
	{
		memcpy( (char*)dest+i ,(c_buff -> read ), 1 ); 
		++copied;
		
		/*move read +1 or jump to start*/
		AdvanceRead(c_buff);
		--n_bytes;
		++i;
	}
	
	if ( ( original_n_bytes > (size_t)read ) || ( 0 == copied ) )
	{
		errno = ENODATA;
	}

	return copied;
	
}
static void AdvanceRead(cbuff_t *c_buff)
{
	int distance_from_reset = 0;

	assert(c_buff);

	distance_from_reset = (c_buff -> data + (c_buff->capacity) )-
						  (c_buff->read);

	if (distance_from_reset)
	{
		++(c_buff -> read);
	}
	else
	{
		c_buff -> read = c_buff -> data;
	}
}
/*****************************************************************************/
ssize_t CBuffWrite(cbuff_t *c_buff, const void *src, size_t n_bytes)
{
	ssize_t written = 0;
	int i = 0;
	size_t original_n_bytes = n_bytes;

	assert(c_buff);
	assert(n_bytes);

	while ( (n_bytes)	&& 0 != CBuffFreeSpace(c_buff) )
	{
		memcpy( c_buff -> write ,(char*)src + i, 1 ); 
		++written;
		++i;

		/*move write +1 or jump to start*/
		AdvanceWrite(c_buff);
		--n_bytes;
	}
		
	if ( ( original_n_bytes > (size_t)written ) || ( 0 == written ) )
	{
		errno = EOVERFLOW;
	}


	return written;

}

static void AdvanceWrite(cbuff_t *c_buff)
{
	int distance_from_reset = 0;

	distance_from_reset = 
	(c_buff -> data + (c_buff->capacity)) - (c_buff->write);
	
	if (distance_from_reset)
	{
		(c_buff -> write)+=1;
	}
	else
	{
		c_buff -> write = c_buff -> data;
	}

}
/*****************************************************************************/

size_t CBuffCapacity(const cbuff_t *c_buff)
{
	return c_buff -> capacity;
}

/*****************************************************************************/ 
int CBuffIsEmpty(const cbuff_t *c_buff)
{
	int result = 0;
	
	if ( c_buff -> write == c_buff -> read )
	{
		result = 1;
	}

	return result;	

}

/*----------------------------------------------------------------------------*/ 

size_t CBuffFreeSpace(const cbuff_t *c_buff)
{
	/*we begin assuming the buffer is empty*/
	size_t free_space = c_buff -> capacity;

	/*if write comes first*/
	if ( ( c_buff -> write ) <  ( c_buff -> read ) )
	{

		/*minus one because we have 1 extra byte in buffer*/
		free_space = ( c_buff -> read ) - ( c_buff -> write ) - 1 ;
	}
	/*if read comes first*/
	if ( ( c_buff -> write ) >  ( c_buff -> read ) )
	{
		free_space = ( c_buff -> capacity ) - 
					 ( ( c_buff -> write ) - ( c_buff -> read ) );
	}

	return free_space;
}

