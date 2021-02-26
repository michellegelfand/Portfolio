/**********************************************************************;
* Project           : Data Structures
*
* Program name      : task.c
*
* Author            : Michelle Gelfand
*
* Date created      : 30.06.19
*
* Purpose           : This program provides the developer
					  with a task creating infastructure.
*
* Version           : 1.1
*
* Review Status		: 
*
* Date Approved       Author	 	             Reviewer 
* 01/07/2019       	  Michelle Gelfand           Katy C. *														  
*******************************************************************/

#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "task.h"

struct task
{
	time_t run_time;
	task_action_t Action;
	size_t interval;
	uniq_id_t task_id; 
	void* param;	
};

/*recieves values to fill into task struct. if both malloc succeeds
and valid uid created then returns new task, else returns null*/
task_t *TaskCreate(size_t delay, size_t interval, task_action_t Action, void *param)
{
	task_t *new_task = NULL;
	uniq_id_t new_uid = {0};
	time_t current_time = 0l;

	assert(Action);

	new_uid = UidCreate();
	new_task = (task_t*)malloc(sizeof(task_t));	
	current_time = time(NULL);

	/*if malloc succesful*/
	if(new_task)
	{
		if(UidIsValid(new_uid) && ( -1 != current_time ) )	
		{	
			new_task->run_time = current_time + delay; 
			new_task->Action   = Action;
		 	new_task->interval = interval; 
			new_task->task_id  = new_uid; 
			new_task->param    = param; 
		}
		else
		{
			free(new_task);
			new_task = NULL;
		}
	}

	return new_task;
}

/*return uid of the argument task*/
uniq_id_t TaskGetUid(const task_t *task)
{
	assert(task);

	return (task->task_id);		
}

/*frees task, returns void*/
void TaskDestroy(task_t *task)
{
	assert(task);

	free(task);
	task = NULL;	
}

/*prioritize where our task should be compared to scheduler_task,
  1 if before (higher priority)
  0 if after (lower priority)*/
int TaskIsBefore(const task_t *scheduler_task, const task_t *new_task)
{	
	assert(new_task);
	assert(scheduler_task);

	/*if new tasks' runtime is sooner return 1*/
    return !!((new_task->run_time) < (scheduler_task->run_time));
}

/* 1 if task1's UID equals to task2's UID
				 0 if not*/
int TaskUidIsMatch(const task_t *task_to_check, void* param, const uniq_id_t *uid_to_match)
{
	assert(task_to_check);
	assert(uid_to_match);	

	(void)param;	

	return UidIsSame((task_to_check->task_id), *uid_to_match);
}

int TaskRun (task_t *task)
{
	assert(task);
		
	return (task->Action(task->param));
}

/*return tasks interval in seconds*/
size_t TaskGetInterval(const task_t *task)
{
	assert(task);
	
	return(task->interval);
}


/* returns time_t of next run time*/
time_t TaskGetNextRunTime(const task_t *task)
{
	assert(task);

	return (task->run_time);
}


/* Update next run time*/
void TaskUpdateNextRunTime(task_t *task, time_t new_time)
{
	assert(task);

	task->run_time = new_time;
}

