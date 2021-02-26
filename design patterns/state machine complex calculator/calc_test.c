/**********************************************************************;
* Project           : Data Structures
*
* Program name      : calc.c
*
* Author            : Michelle Gelfand
*
* Date created      : 23.07.19
*
* Purpose           : This program provides the user
					  with a state machine based calculator
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 24/07/2019       	  Michelle Gelfand           Olga K. *														  
*******************************************************************/
#include <stdio.h>/*printf*/

#include "calc.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"

void CreateDestroyTest();
void AdditionSubstractionTest();
void MultDevideTest();

int main()
{
	/*CreateDestroyTest();*/
	/* AdditionSubstrationTest();*/
	MultDevideTest();	

	return 0;
}

void CreateDestroyTest()
{
	char* polynom = "1+1";
	double res = 0;

	if ( CALC_SUCCESS == Calculate(polynom, &res))
	{
		printf(GREEN"\n\nCreate passed\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\nCreate failed\n\n"WHITE);
	}

	printf(BLUE"\n\nCombine this test with valgrind to check memory leaks\n\n \
					"WHITE);
}


void AdditionSubstractionTest()
{
	char polynom[20]="7.2+3.2-0.4";
	double res = 0;
	calc_status_t status = CALC_FAIL;

	status = Calculate(polynom, &res);

	if(CALC_SUCCESS == status &&  10 == res)
	{
		printf(GREEN"\n\nAddition substration Success wheepee\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\nAddition substraction failed oh noes\n\n"WHITE);
		printf("\nresult: %f\n" ,res);
		printf("status: %s\n" ,status);
	}

}
void MultDevideTest()
{
	char polynom[20]="7+4*3";
	double res = 0;
	calc_status_t status = CALC_FAIL;

	status = Calculate(polynom, &res);

	if(CALC_SUCCESS == status &&  3 == res)
	{
		printf(GREEN"\n\nmult & div Success wheepee\n\n"WHITE);
	}
	else
	{
		printf(RED"\n\nmult & div oh noes\n\n"WHITE);
		printf("\nresult: %f\n" ,res);
		printf("status: %s\n" ,status);
	}

}
