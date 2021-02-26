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
					  with a task creating infastructure.
*
* Version           : 1.1.2
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 02/07/2019       	  Michelle Gelfand           Katy C. *														  
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>/*system*/

#include "scheduler.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

int SchedulerCreate_test();
int SchedulerDestroy_test();
int SchedulerAdd_test();
int SchedulerRemove_test();
int SchedulerSize_test();
int SchedulerIsEmpty_test();
int SchedulerRun_test();
int SchedulerStop_test();
int  XEYES_test();
int Action(void *param);

int system_test();

int main()
{
	int test_result = 0;

	test_result |= SchedulerCreate_test();
	test_result |= SchedulerDestroy_test();
	test_result |= SchedulerAdd_test();
	test_result |= SchedulerSize_test();
	test_result |= SchedulerIsEmpty_test();
	test_result |= SchedulerRemove_test();
	test_result |= SchedulerRun_test();
	test_result |= SchedulerStop_test();
	/*test_result |= XEYES_test();*/
	(0 == test_result)? printf(KCYN"\n\nALL TESTS PASSED\n\n"WHITE) :
						printf(RED"\n\nFailed on some tests\n\n"WHITE);
	return 0;
}

int Action(void *param)
{
	int result = 1;
	*(int*)param+= 10;

	printf("\ntask1 running\n");

	if( 30 == *(int*)param)
	{

		printf("\ntask 1 complete\n");
		result = 0;
	} 

	return result;
}
int Action2(void *param)
{
	int result = 1;
	*(int*)param+= 10;

	printf("\ntask2 running\n");

	if( 10 == *(int*)param)
	{
		printf("\ntask 2 complete\n");
		result = 0;
	} 

	return result;
}

int Action3(void *param)
{
	(void)param;

	printf("\ntask3 running and must fail\n");

	/*fail*/
	return -1;
}

int XeyesOnPc(void *param)
{
  char* ip_addresses[] = 
	{ "sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.14 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & ",
	"sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.1 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & ",
	"sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.26 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & ",
	"sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.23 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & ",
	"sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.22 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & ",
	"sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.19 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & ",
	"sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.20 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & ",
	"sshpass -p \"ct,h kvmkhj\" ssh -o StrictHostKeyChecking=no -X 		  		       student@10.3.0.55 'DISPLAY=:0.0 xeyes -geometry 1000x1000' & "
	};
	srand(time(NULL));
	system(ip_addresses[rand()%8]);
	system("exit");

    (void)param;

	return 0;
}

int Action4(void *param)
{

	printf("\nSTOP!!! \n");

	SchedulerStop(param);
	/*fail*/
	return -1;
}
int SchedulerCreate_test()
{
	int test_result = 1;
	scheduler_t *new_scheduler = SchedulerCreate();
	
	printf(YELLOW"\n\nS C H E D U L E R   C R E A T E\n\n"WHITE);

	if(NULL != new_scheduler)
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
	}

	SchedulerDestroy(new_scheduler);

	return test_result;
}

int SchedulerDestroy_test()
{
	scheduler_t *new_scheduler = SchedulerCreate();
	
	printf(YELLOW"\n\nS C H E D U L E R   D E S T R O Y\n\n"WHITE);

	SchedulerDestroy(new_scheduler);

	printf(BLUE"\nCombine this test with vlg\n"WHITE);
	
	return 0;
}

int SchedulerAdd_test()
{
	int test_result = 1;
	
	uniq_id_t task_added = {0};

	scheduler_t *new_scheduler = SchedulerCreate();
	
	task_added = SchedulerAdd(new_scheduler, 10,
							     3, Action, 
								 NULL);

	printf(YELLOW"\n\nS C H E D U L E R   A D D\n\n"WHITE);

	if(UidIsValid(task_added) && 1 == SchedulerSize(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
	}

	SchedulerDestroy(new_scheduler);
	return test_result;
}

int SchedulerSize_test()
{
	int test_result = 0;
	
	scheduler_t *new_scheduler = SchedulerCreate();

	printf(YELLOW"\n\nS C H E D U L E R   S I Z E\n\n"WHITE);

	if( 0 == SchedulerSize(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
		test_result+=1;
	}

	SchedulerAdd(new_scheduler, 10, 3, Action, NULL);
	SchedulerAdd(new_scheduler, 10, 3, Action, NULL);
	SchedulerAdd(new_scheduler, 10, 3, Action, NULL);
	SchedulerAdd(new_scheduler, 10, 3, Action, NULL);

	if( 4 == SchedulerSize(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
		test_result+=1;
	}

	SchedulerDestroy(new_scheduler);

	return test_result;	
}

int SchedulerIsEmpty_test()
{
	int test_result = 0;
	
	scheduler_t *new_scheduler = SchedulerCreate();

	printf(YELLOW"\n\nI S   E M P T Y\n\n"WHITE);

	if( SchedulerIsEmpty(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
		test_result+=1;
	}

	SchedulerAdd(new_scheduler, 10, 3, Action, NULL);

	if( !SchedulerIsEmpty(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
		test_result+=1;
	}

	SchedulerDestroy(new_scheduler);
	return test_result;
}
int SchedulerRemove_test()
{
	int test_result = 0;
	
	uniq_id_t new_uid = {0};
	
	scheduler_t *new_scheduler = SchedulerCreate();

	printf(YELLOW"\n\nS C H E D U L E R   R E M O V E\n\n"WHITE);

	new_uid = SchedulerAdd(new_scheduler, 10, 3, Action, NULL);

	SchedulerRemove(new_scheduler, new_uid);	

	if( SchedulerIsEmpty(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
		test_result+=1;
	}

	SchedulerDestroy(new_scheduler);
	return test_result;
}
int SchedulerRun_test()
{
	int test_result = 0;
	
	int param1 = 0;
 	int param2 = 0;
	scheduler_t *new_scheduler = SchedulerCreate();

	SchedulerAdd(new_scheduler, 1, 1, Action, &param1);
	SchedulerAdd(new_scheduler, 1, 1, Action2, &param2);
	printf(YELLOW"\n\nS C H E D U L E R   R U N\n\n"WHITE);
	if( 0 == SchedulerRun(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
		test_result+=1;
	}

	
	SchedulerAdd(new_scheduler, 1, 1, Action3, &param2);
	
	if( -1 == SchedulerRun(new_scheduler))
	{
		printf(GREEN"\nSuccess\n"WHITE);
	}
	else
	{
		printf(RED"\nFail\n"WHITE);
		test_result+=1;
	}

	SchedulerDestroy(new_scheduler);
	return test_result;

}
int SchedulerStop_test()
{
	
	int test_result = 0;
	
	int param1 = 0;
 	int param2 = 0;
	scheduler_t *new_scheduler = SchedulerCreate();

	SchedulerAdd(new_scheduler, 2, 1, Action, &param1);
	SchedulerAdd(new_scheduler, 2, 1, Action2, &param2);
	SchedulerAdd(new_scheduler, 1, 1, Action4, new_scheduler);

	printf(YELLOW"\n\nS C H E D U L E R   S T O P\n\n"WHITE);

	SchedulerRun(new_scheduler);
	
	SchedulerDestroy(new_scheduler);
	return test_result;

}

int XEYES_test()
{
 	int param2 = 0;
	scheduler_t *new_scheduler = SchedulerCreate();
	SchedulerAdd(new_scheduler, 1, 1, XeyesOnPc, &param2);

	printf(YELLOW"\n\nX E Y E S\n\n"WHITE);

	SchedulerRun(new_scheduler);
	
	SchedulerDestroy(new_scheduler);
	return 0;

}

