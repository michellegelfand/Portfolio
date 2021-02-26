/**********************************************************************;
* Project           : Data Structures
*
* Program name      : simple_watchdog.c
*
* Author            : Michelle Gelfand
*
* Version           : 1.0
*														  
******************************************************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* abort */
#include <sys/types.h> /* pid_t*/
#include <sys/wait.h> /* WEXITSTATUS, wait */
#include <unistd.h> /*fork, execpv */


#include "test_tools.h"

int SimpleWatchDog (char* prog, char** arg_list) 
{
	pid_t pid = fork();

	if (pid!= 0)
	{
		printf("prog is %d\n", pid);
		return pid;
	}
	else 
	{
		printf("program id %d\n", pid);
		execvp (prog, arg_list);

		/* only reached if execvp failed */
        printf("\noh noes!");
		abort();
	}

}


int SimpleWatchDogSystem (char* prog, char** arg_list) 
{
	/*for future if ill want to run a different program that
	requires args*/
	(void)arg_list;

	system(prog);
	abort();
}


int main()
{
    int status = 0;

    char* arg_list[] = {
	 					"./a.out", /*the name of the program. */
						NULL /* end of arg list*/
					};

    while(!WEXITSTATUS(status))
	{
        /* SimpleWatchDog ("./a.out", arg_list); */
		SimpleWatchDogSystem("./a.out", arg_list);

		/* Wait for the child process to complete. */
		wait (&status);
	}

	return 0;
}