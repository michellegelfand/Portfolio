#ifndef __STAYING_ALIVE_H__
#define __STAYING_ALIVE_H__

/************************************************************************
* Project           : WatchDog                      	 	            *
*										                                *
* File Name         : wd_main.h    								*    	*								                           			    *       
* Version           : 1.0							 					*
************************************************************************/

#include "wd_shared.h"

/*
    RETURN: NULL on failure
*/
watchdog_t *KeepMeAlive(int argc, char **argv);

/*
    Args:
        watchdog_key - returned value from KeepMeAlive
*/
void LetMeDie(watchdog_t *watchdog_key);


/*----------------------------------------------------------------------------*/
#endif /* __STAYING_ALIVE_H__ */
