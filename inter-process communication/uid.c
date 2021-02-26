/**********************************************************************;
* Project           : Data Structures
*
* Program name      : pqueue.c
*
* Author            : Michelle Gelfand
*
* Date created      : 27.06.19
*
* Purpose           : This program provides the user with a
*					  Unique ID creation program, as well as an IsSameId
					  func and an IsValid func.
*
* Version           : 1.3
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 27/06/2019       	  Michelle Gelfand           Evegeni S. 														  
*******************************************************************/

#include <unistd.h>/*getpid*/

#include "uid.h"

uniq_id_t invalid_uid = {0ul, -1l, 0};

uniq_id_t UidCreate()
{
	static size_t count = 0;	
		
	uniq_id_t new_uid = {0ul,0l,0};
	
	new_uid.time = time(NULL);

	if((time_t)-1 != new_uid.time)
	{
		new_uid.count = ++count;	

		new_uid.pid = getpid();
	}
	else
	{
		new_uid = invalid_uid;
	}	 

	return new_uid;
}
int UidIsSame(uniq_id_t uid1, uniq_id_t uid2)
{
	return (!!( (uid1.count   == uid2.count) &&
			    (uid1.time == uid2.time) &&
			    (uid1.pid     == uid2.pid) ) );
}
int UidIsValid(uniq_id_t uid)
{
	return !(UidIsSame(invalid_uid, uid));	
}
