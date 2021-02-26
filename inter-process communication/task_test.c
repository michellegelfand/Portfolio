/**********************************************************************;
* Project           : Data Structures
*
* Program name      : task.c
*
* Author            : Michelle Gelfand
*
* Date created      : 25.06.19
*
* Purpose           : This program provides the developer
					  with a task creating infastructure.
*
* Version           : 1.1
*
* Review Status		: 
*
* Date Approved       Author	 	             Reviewer 
* 27/06/2019       	  Michelle Gelfand           Katy C. *														  
*******************************************************************/
#include <stdio.h>/*printf*/
#include <time.h>/*time*/

#include "task.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

int TaskDestroy_test();
int TaskCreate_test();
int TaskGetUid_test();
int TaskIsBefore_test();
int TaskUidIsMatch_test();
int TaskRun_test();
int TaskUpdateNextRunTime_test();
int TaskGetNextRunTime_test();
int TaskIsBefore_test();

int Action(void *param);

int main()
{
	int test_result = 0;

	test_result |= TaskCreate_test();
	test_result |= TaskDestroy_test();
	test_result |= TaskGetUid_test();
	test_result |= TaskIsBefore_test();
	test_result |= TaskUidIsMatch_test();
	test_result |= TaskRun_test();
	test_result |= TaskUpdateNextRunTime_test();
    test_result |= TaskGetNextRunTime_test();
    test_result |= TaskIsBefore_test();	


	(0 == test_result)? printf(KCYN"\n\nALL TESTS PASSED\n\n"WHITE) :
						printf(RED"\n\nFailed on some tests\n\n"WHITE);

	return 0;
}

int Action(void *param)
{
	printf("\ntask run succesfully\n");
	(void)param;
	return 1;
}

int TaskCreate_test()
{
	/*default to fail*/
	int test_result = 1;	

	task_t *task = TaskCreate(10, 2, Action, NULL);
	
	printf(YELLOW"\nT A S K   C R E A T E   T E S T\n");

	if( NULL != task)
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;	
	}
	else
	{
		printf(RED"\nfailed\n"WHITE);
	}

	printf(BLUE"\nCombine this test with vlg\n"WHITE);

	TaskDestroy(task);

	return test_result;
}

int TaskDestroy_test()
{
	task_t *task = TaskCreate(10, 2, Action, NULL);
	
	printf(YELLOW"\nT A S K   D E S T R O Y   T E S T\n"WHITE);

	TaskDestroy(task);

	printf(BLUE"\nCombine this test with vlg\n"WHITE);

	return 0;
}

int TaskGetUid_test()
{
	task_t *task = NULL;
	uniq_id_t uid = {0};

	task = TaskCreate(10, 2, Action, NULL);

	uid = TaskGetUid(task);	

	printf(YELLOW"\nT A S K   G E T   U I D   T E S T\n"WHITE);
	printf("\n %lu - %ld - %d\n", uid.count, uid.time, uid.pid);

	TaskDestroy(task);

	return 0;
}

int TaskIsBefore_test()
{
	int test_result = 1;
	task_t *task1 = NULL;
	task_t *task2 = NULL; 

	task1 = TaskCreate(9, 2, Action, NULL);
	task2 = TaskCreate(10, 2, Action, NULL);
	
	printf(YELLOW"\nT A S K   I S   B E F O R E   T E S T\n"WHITE);

	if( TaskIsBefore(task2, task1) )
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;
	}
	else
	{
		printf(RED"\nfailed\n"WHITE);
	}

	TaskDestroy(task1);
	TaskDestroy(task2);
	
	return test_result;
}

int TaskUidIsMatch_test()
{
	int test_result = 1;
	task_t *task1 = NULL;
	task_t *task2 = NULL; 
	uniq_id_t uid1 = {0};
	uniq_id_t uid2 = {0};

	task1 = TaskCreate(9, 2, Action, NULL);
	task2 = TaskCreate(10, 2, Action, NULL);
	
	uid1 = TaskGetUid(task1);
	uid2 = TaskGetUid(task2);

	printf(YELLOW"\nT A S K   U I D   I S   M A T C H   T E S T\n"WHITE);

	if(( 0 == TaskUidIsMatch(task1, NULL,&uid2) )&& 
	   (TaskUidIsMatch(task1,NULL, &uid1))) 
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;
	}
	else
	{
		printf(RED"\nfailed\n"WHITE);
	}

	TaskDestroy(task1);
	TaskDestroy(task2);

	return test_result;
}

int TaskRun_test()
{	
	task_t *task1 = TaskCreate(9, 2, Action, NULL);
	
	printf(YELLOW"\nT A S K   R U N  T E S T\n"WHITE);

	TaskRun(task1);

	TaskDestroy(task1);
	return 0;

}

int TaskGetInterval_test()
{
	int test_result = 1;
	task_t *task1 = TaskCreate(9, 5,Action, NULL);
	
	printf(YELLOW"\nT A S K   G E T   I N T E R V A L   T E S T\n"WHITE);

	if( 5 == TaskGetInterval(task1))
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;
	}
	else
	{
		printf(RED"\nfailed\n"WHITE);
	}

	TaskDestroy(task1);
	return test_result;

}

int TaskGetNextRunTime_test()
{
	int test_result = 1;
	task_t *task1 = TaskCreate(9, 5,Action, NULL);
	
	printf(YELLOW"\nT A S K   G E T   R U N   T I M E   T E S T\n"WHITE);

	if( time(NULL) + 9 == TaskGetNextRunTime(task1))
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;
	}
	else
	{
		printf(RED"\nfailed\n"WHITE);
	}

	TaskDestroy(task1);
	return test_result;
}

int TaskUpdateNextRunTime_test()
{
	int test_result = 1;
	task_t *task1 = TaskCreate(9, 5,Action, NULL);
	
	printf(YELLOW"\nT A S K   U P D A T E   R U N   T I M E   T E S T\n"WHITE);

	TaskUpdateNextRunTime(task1, 1);
	if( 1 == TaskGetNextRunTime(task1))
	{
		printf(GREEN"\nSuccess\n"WHITE);
		test_result = 0;
	}
	else
	{
		printf(RED"\nfailed\n"WHITE);
	}

	TaskDestroy(task1);
	return test_result;
}


