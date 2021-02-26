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


#include <stdio.h>

#include "uid.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

int UidCreate_test();
int UidIsSame_test();
int UidIsValid_test();
void PrintUID(uniq_id_t uid);


int main()
{	
	int test_result = 0;

	test_result |= UidCreate_test();
	test_result |= UidIsSame_test();
	test_result |= UidIsValid_test();


	(0 == test_result)? printf(KCYN"\n\nALL TESTS PASSED\n\n"WHITE) :
						printf(RED"\n\nFailed on some tests\n\n"WHITE);


	return 0;
}
void PrintUID(uniq_id_t uid)
{
	printf("\n %lu - %ld - %d\n", uid.count, uid.time, uid.pid);
}
int UidCreate_test()
{
	int test_result = 0;

	uniq_id_t new_id = UidCreate();
	
	PrintUID(new_id);	

	if(UidIsSame(new_id, invalid_uid))
	{
		printf(RED"\n\nFailed to create valid uid\n\n");
		test_result = 1;
	}	
	new_id = UidCreate();
	
	PrintUID(new_id);

	return test_result;
}

int UidIsSame_test()
{
	int test_result = 0;

	uniq_id_t new_id = UidCreate();
	
	PrintUID(new_id);

	if(UidIsSame(new_id, invalid_uid))
	{
		printf(RED"\n\nFailed to return is not same\n\n");
		test_result = 1;
	}

	if(!UidIsSame(invalid_uid, invalid_uid))
	{
		printf(RED"\n\nFailed to return is same\n\n");
		test_result = 1;
	}

	return test_result;
}

int UidIsValid_test()
{
	int test_result = 0;

	uniq_id_t invalid = {0,-1,0};
	uniq_id_t new_id = UidCreate();
	
	PrintUID(new_id);
	PrintUID(invalid);
	if(!UidIsValid(new_id))
	{
		printf(RED"failed to return id is valid"WHITE);
		test_result = 1;
	}
	if(UidIsValid(invalid))
	{
		printf(RED"failed to return id is invalid"WHITE);
		test_result = 1;
	}

	return test_result;
}

