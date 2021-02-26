/******************************************************************************/
/*	File:		uid.h											              */
/*	Created:	27.06.19 													  */
/*  Version: 	1.4 														  */
/*	Modified:	29.06.19													  */
/*	Author:		     											              */
/*																			  */
/*	Brief:		Sorted List Functions:		UidCreate	         			  */
/*										   	UidIsSame					      */	
/*							  				UidIsValid					      */ 	
/*							  				                                  */
/*							  				                                  */
/******************************************************************************/

#ifndef __UID_H__
#define __UID_H__

	
#include <time.h>      /* time_t, size_t */
#include <sys/types.h> /* pid_t */


typedef struct uid
{
	size_t count;
	time_t time;
	pid_t pid;
	
} uniq_id_t;

extern uniq_id_t invalid_uid;

/*------------------------------------------------------------------------------
UidCreate - Creates a new uid. 
                                             
ARGS: 
void
		
RETURNS: 
uid struct
   		  

*/

uniq_id_t UidCreate();

/*------------------------------------------------------------------------------

Checks if uid1 is the same as uid2.        
                                         
ARGS: 
uid1 - first uid 	
uid2 - second uid 	   
 
RETURNS: 	1 if the two uid's are the same
			0 otherwise	
							        	                  	      
*/

int UidIsSame(uniq_id_t uid1, uniq_id_t uid2);

/*------------------------------------------------------------------------------
Checks if the uid1 is valid.
                                        
ARGS: 
uid1 - uid struct	
   
 
RETURNS: 	1 if the uid is valid
			0 otherwise					        	                  	      
*/


int UidIsValid(uniq_id_t uid);


/*----------------------------------------------------------------------------*/


#endif /* __UID_H__ */

