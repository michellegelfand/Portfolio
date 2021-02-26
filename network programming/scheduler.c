/**********************************************************************;
* Project           : Data Structures
*
* Program name      : Scheduler.c
*
* Author            : Michelle Gelfand
*
* Date created      : 30.06.19
*
* Purpose           : This program provides the developer
					  with a task scheduling infrastructure
*
* Version           : 1.1.2
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 02/07/2019       	  Michelle Gelfand           Katy C. *														  
*******************************************************************/

#include <unistd.h>/*sleep*/
#include <stdlib.h>/*malloc, size_t*/
#include <assert.h>/*assert*/
#include <stdio.h>/*printf*/

#include "pqueue.h"
#include "task.h"
#include "scheduler.h"

struct scheduler
{
	p_queue_t *tasks;
	int to_stop;
};

/* returns pointer to new scheduler or NULL*/		  			
scheduler_t *SchedulerCreate(void)
{
	scheduler_t *new_scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));

	if(new_scheduler)
	{
		new_scheduler->tasks = PQCreate((pq_is_before_t)TaskIsBefore);
		new_scheduler->to_stop = 0;		

		if(NULL == new_scheduler->tasks)
		{
			free(new_scheduler);
			new_scheduler = NULL;
		}
	}

	return new_scheduler;
}

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);

	while( !SchedulerIsEmpty(scheduler) )
	{
		TaskDestroy(PQPeek(scheduler->tasks));
		PQDequeue(scheduler->tasks);
	}

	PQDestroy(scheduler->tasks);

	free(scheduler);
	scheduler = NULL;	
}

/*returns UID of added task or invalid id*/	

uniq_id_t SchedulerAdd(scheduler_t *scheduler, size_t delay, size_t interval,
				  scheduler_action_t Action, void *param)
{
	pq_status_t enqueue_status = PQ_SUCCESS;
	uniq_id_t new_task_id = invalid_uid;
	task_t *new_task = NULL;

	assert(scheduler);
	assert(Action);
	
	new_task = TaskCreate(delay, interval, Action, param);

	if(new_task)
	{
		enqueue_status = PQEnqueue(scheduler->tasks, new_task);

		if( PQ_SUCCESS == enqueue_status)
		{
			new_task_id = TaskGetUid(new_task);
		}
		else
		{
			/*func also nullifys pointer for return*/
			TaskDestroy(new_task);
		}
	}

	return new_task_id;
}

/* -1 removal didnt work, 0 succesful*/
int SchedulerRemove(scheduler_t *scheduler, uniq_id_t uid)
{
	task_t *removed_task = NULL;
	int result = -1;

	assert(scheduler);
	
	removed_task = (task_t*)PQRemove(scheduler->tasks, 
				   (pq_ismatch_t)TaskUidIsMatch, NULL, &uid);  

	if(removed_task)
	{
		TaskDestroy(removed_task);
		result = 0;
	}

	return result;
}

/******************************************************************************/
	
/*count of operations schedulerd in scheduler*/

size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(scheduler);

	return PQSize(scheduler->tasks);
}

/******************************************************************************/
int SchedulerIsEmpty (const scheduler_t *scheduler)
{
	assert(scheduler);

	return(PQIsEmpty(scheduler->tasks));
}

/******************************************************************************/

/*for run_result: 0 Success, -1 one or more errors occured during run*/
/*for task_result: neg num task failed, 0 completed, pos num incomplete*/
int SchedulerRun (scheduler_t *scheduler)
{
	int run_result = 0;
	int task_result = 0;
	task_t *current_task = NULL;
	time_t sleep_for = 0;
	time_t current_time = 0l;

	assert(scheduler);

	scheduler->to_stop = 0;

	while(!( (PQIsEmpty(scheduler->tasks))) && (0 == scheduler->to_stop) )
	{
		current_time = time(NULL);
		
		/*if time failed stop the run*/
		if(-1 == current_time)
		{
			run_result = -1;
			break;
		}

		/*next task is at front of queue*/
		current_task = PQPeek(scheduler->tasks);

		/*sleep until run time*/

		sleep_for = TaskGetNextRunTime(current_task) - current_time;

		printf("\n\nsleep for %ld", sleep_for);

		while (0 < sleep_for)
		{
			printf("\nZ Z Z im asleep\n");
			
			sleep_for = sleep(sleep_for);
		}

		/*run task*/
		task_result = TaskRun(current_task);

		/*remove task from queue*/
		PQDequeue(scheduler->tasks);

		/*if task failed update run retrun status, dont return it into queue*/
		if ( 0 > task_result )
		{	
			run_result = -1;
			TaskDestroy(current_task);
		}
		else if ( 0 < task_result )
		{
			current_time = time(NULL);

			if(-1 == current_time)
			{
				run_result = -1;
				break;
			}

			TaskUpdateNextRunTime(current_task, 
			current_time+ TaskGetInterval(current_task));
			if ( PQ_SUCCESS !=PQEnqueue(scheduler->tasks, current_task) )
			{
				TaskDestroy(current_task);
				run_result = -1;
			}
		}
		else
		{
			TaskDestroy(current_task);
		}
		/*else if finished task stays out of queue*/
	}

	return run_result;
}

/******************************************************************************/

/*SchedulerStop - Stops our scheduler from running*/

void SchedulerStop (scheduler_t *scheduler)
{
	assert(scheduler);

	scheduler->to_stop = 1;
}

/******************************************************************************/

