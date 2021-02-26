
/************************************************************;
* Project           : Data Structures
*
* Program name      : sys_v_sem.c
*
* Author            : Michelle Gelfand	
*************************************************************/

#define _POSIX_C_SOURCE 199309L/*sigaction */
#include <sys/types.h>/*pid_t */
#include <signal.h>/*sig_atomic_t */
#include <stdlib.h>/*NULL */
#include <unistd.h>/*write */
#include <semaphore.h>/*sem_t*/
#include <stdio.h>/*perror*/

#define PINGPONGS 10

void Pong(int sig);

sem_t sem = {0};

int main(int argc, char *argv[])
{
    int pingpongs = PINGPONGS;
    pid_t pong_id = atoi(argv[1]);
    struct sigaction pong = {0};

    pong.sa_handler = Pong;
    
    if( 2 > argc)
    {
    	perror("no cmd input");
    	abort();
    }

    sigemptyset(&pong.sa_mask);
    
    sigaction(SIGUSR1, &pong, NULL);
	
	sem_init(&sem, 0, 0);

	kill(pong_id, SIGUSR2);
	
    while(pingpongs)
    {
        while(sem_wait(&sem))
        {
        	;
        }
           
        --pingpongs;

        write(STDOUT_FILENO, "\nPONG! --woosh\n", 15);
        sleep(2);
        kill(pong_id, SIGUSR2);
        
    }
    return 0; 
}

void Pong(int sig)
{
    (void)sig;
    while(sem_post(&sem))
    {
    	;
    }
}
