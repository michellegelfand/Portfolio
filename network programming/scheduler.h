/******************************************************************************/
/*	@File:		scheduler.h													  */
/*	@Created:	30.06.19 													  */
/*  @Version: 	1.1.2  														  */
/*	@Modified:	2.07.19														  */
/*	@Author:																  */
/*																			  */
/*	@Brief:		scheduler Functions	:			SchedulerCreate 			  */
/*										   		SchedulerDestroy			  */
/*							  				 	SchedulerAdd				  */
/*							  				 	SchedulerRemove				  */
/*							  				 	SchedulerRun				  */
/*							  				 	SchedulerStop				  */
/*							  				 	SchedulerSize				  */
/*							  				 	SchedulerIsEmpty			  */
/*							  				 								  */
/*                                                                            */
/******************************************************************************/
/*CHANGE LOG 

v1.1		- Added <stddef.h>
			- Changed uid_t to uniq_id_t

v1.1.2 		- Added notes 
	
*/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h> /* size_t */

#include "uid.h"

/*
struct schedule
{
	p_queue_t *pqueue;
	int to_stop/to_run;

}
*/

typedef struct scheduler scheduler_t;

typedef int (*scheduler_action_t)(void *param);




/******************************************************************************/
/*SchedulerCreate - Creates a new scheduler. 
                                             
ARGS: 
			NONE
		
RETURNS: 	Success: pointer to scheduler. 
			Failure: NULL   		  

*/
scheduler_t *SchedulerCreate(void);


/******************************************************************************/


/*SchedulerDestroy - Frees all allocated memory in scheduler. 
                                             
ARGS: 
			pointer to scheduler
		
RETURNS: 	
			void 		  

*/

void SchedulerDestroy(scheduler_t *scheduler);

/******************************************************************************/


/*SchedulerAdd - Adds a task to scheduler.
                                             
ARGS: 
			scheduler - pointer to scheduler
			delay	  - in seconds of execution of the task from now.
			interval  - in seconds, time between runs until fully completed.
			Action 	  - pointer to function, for the action to be done.
						Return values for action:
													0  for SUCCESS
													pos  for PARTIAL (to repeat)
													neg for ERROR   (remove)
			param 	  - For user's usage.
		
RETURNS: 	
			SUCCESS : UID of the schdeduled action	
			FAIL    : invalid UID

*/

uniq_id_t SchedulerAdd(scheduler_t *scheduler, size_t delay, size_t interval,
				  scheduler_action_t Action, void *param);


/******************************************************************************/


/*SchedulerRemove - Removes a task from the scheduler 
					and frees it's allocated memory. 
                                             
ARGS: 
			scheduler - pointer to scheduler
			uid - unique ID of the schdeduled action 
		
RETURNS: 	
			SUCCESS 			 :  0
			FAILED TO FIND UID   : -1		  
*/

int SchedulerRemove(scheduler_t *scheduler, uniq_id_t uid);

/******************************************************************************/

/*schedulerSize - Gets the count of scheduled operations.
                                             
ARGS: 
			Pointer to scheduler
		
RETURNS: 	
			count of operations scheduled in scheduler.

*/

size_t SchedulerSize(const scheduler_t *scheduler);

/******************************************************************************/

/*schedulerIsEmpty - Indication whether we have operations left in the scheduler. `
                                             
ARGS: 
			pointer to scheduler
		
RETURNS: 	
			1 if scheduler is empty
			0 otherwise

*/

int SchedulerIsEmpty (const scheduler_t *scheduler);

/******************************************************************************/


/*SchedulerRun - Runs our scheduler
                                             
ARGS: 
			pointer to scheduler
		
RETURNS: 	
			0  Success
			-1 one or more Errors occured during run.
					
	NOTES: Scheduler will not stop in case of error.
*/

int SchedulerRun (scheduler_t *scheduler);

/******************************************************************************/

/*SchedulerStop - Stops our scheduler from running, 
				NOTE: Should be implemented in one of the actions.
                                             
ARGS: 
			Pointer to Scheduler
		
RETURNS: 	
			void
			

*/

void SchedulerStop (scheduler_t *scheduler);

/******************************************************************************/


#endif /*__SCHEDULER_H__*/
