/******************************************************************************/
/*    @File:        task.h                                                    */
/*    @Created:    30.06.19                                                   */
/*  @Version:     1.1.2                                                       */
/*    @Modified:    31.06.19                                                  */
/*    @Author:                                                                */
/*                                                                            */
/*    @Brief:        Task Functions    :              TaskCreate        	  */
/*                                                    TaskDestroy          	  */
/*                                                    TaskIsBefore            */
/*                                                    TaskUidIsMatch          */
/*                                                    TaskGetUid           	  */
/*													  TaskRun				  */
/******************************************************************************/
/*CHANGE LOG

V1.1        - Removed pqueue_is_before_t
            -Removed pqueue_is_match_t
            - Changed uid_t to uniq_id_t
            -Added void* param to task uid
            -Include <stddef.h>
            - Added int TaskRun(task_t *task) function
 v1.1.2
			-Changed IsBefore arguements, for const and order(!!).
			-Added TaskGetInterval
			-Added TaskGetNextRunTime
			-Added TaskUpdateNextRunTime
			-Changed signature of to TaskUidIsMatch
			
 v1.1.3		-Added notes
 */



#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h> /* size_t */
#include <time.h> /*time_t*/

#include "ts_uid.h" /*uniq_id_t*/

                                                         
typedef int (*task_action_t)(void *param);

typedef struct task task_t;

/*
Action - pointer to function to schedule.

next_run_time - Real time of the next run of our Action

Interval - The interval between runs of the actions.

uid - unique ID of the task 

struct task
{
    time_t next_run_time;
    task_action_t Action;
    size_t interval;
    uid_t uid;    
}
*/
/******************************************************************************/
/*TaskCreate - Creates a new task. 
                                             
ARGS: 
            delay for the first run, in seconds.
            interval for the next times the action runs, in seconds.
            Action is pointer function for action to be sent
            			Action returns: 			0  for SUCCESS
													1  for PARTIAL (to repeat)
													-1 for ERROR   (remove)
            param - for user's usage 
            
RETURNS:     Success: pointer to new task 
            Failure: NULL             

*/
task_t *TaskCreate(size_t delay, size_t interval, task_action_t Action
                    , void *param);



/******************************************************************************/
/*TaskDestroy - Frees a task. 
                                             
ARGS: 
            Task to free
        
RETURNS:     void

  

*/
void TaskDestroy(task_t *task);

/******************************************************************************/
/*TaskGetUid - Gives the UID of given task.
                                             
ARGS:             Task of which we want to get a UID from.
            
        
RETURNS:         Uid to the task given.
      

*/
uniq_id_t TaskGetUid(const task_t *task);

/******************************************************************************/

/*

    TaskIsBefore determines whether a new task should be scheduled before a
    different task.
    
ARGS:
        new task we want to prioritize
        scheduler task we compare new task with

RETURNS: 
                  1 if new_task is prioiritized before scheduler_task
                  0 if new_task is prioritized later to scheduler_task
                 
        
*/

int TaskIsBefore(const task_t *scheduler_task, const task_t *new_task);

/******************************************************************************/

/*
    TaskUidIsMatch determines whether the UID of both tasks matches.
ARGS:
        task_to_check 
        uid_to_match the UID we check with the task's uid
        param - data comparison condition
        

RETURNS: 
                 1 if task_to_check matches uid_to_match
                 0 otherwise
                
         
*/

int TaskUidIsMatch(const task_t *task_to_check, void* param, const uniq_id_t *uid_to_match);
/******************************************************************************/

/*	TaskRun executes the action of task1

ARGS:
		*task - pointer to task

RETURNS:
			Same return status of Action.
			
			
*/

int TaskRun (task_t *task);
/******************************************************************************/

/* TaskGetInterval returns the task's interval time in seconds.

ARGS:
			*task - pointer to task of which we want to get interval from.
			
RETURNS:	
			interval in seconds.
				
*/
size_t TaskGetInterval(const task_t *task);

/******************************************************************************/

/* TaskGetNextRunTime will get the next run time of the task

ARGS:		
			task - pointer to task of which we want to get next run time from.
			
RETURNS:
			time_t of next run time.
			
*/

time_t TaskGetNextRunTime(const task_t *task);

/******************************************************************************/

/* TaskUpdateNextRunTime will update the next run time of the task

ARGS:		
			task - pointer to task of which we want to update next run time for.
			
RETURNS:
			
			
*/

void   TaskUpdateNextRunTime(task_t *task, time_t new_time);

/******************************************************************************/

#endif /* __TASK_H__*/
