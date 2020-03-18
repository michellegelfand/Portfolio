/**********************************************************************;
* Project           : Data Structures
*
* Author            : Michelle Gelfand
*
* Review Status		: Approved
*
*                     Author	 	             Reviewer 
*                 	  Michelle Gelfand           Doron W. 														  
*******************************************************************/

#include <unistd.h>/*getpid*/
#include <pthread.h>/*pthread create*/

#include "ts_uid.h"

uniq_id_t invalid_uid = {0ul, -1l, 0};
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

uniq_id_t UidCreate()
{
	static size_t count = 0;	
		
	uniq_id_t new_uid = {0ul,0l,0};
	
	new_uid.time = time(NULL);

    pthread_mutex_lock(&mutex);
	new_uid.count = ++count;		
    pthread_mutex_unlock(&mutex);

	new_uid.pid = getpid();
	
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
