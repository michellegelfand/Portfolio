
/************************************************************;
* Project           : Data Structures
*
* Program name      : sys_v_sem.c
*
* Author            : Michelle Gelfand	
*************************************************************/

#define _POSIX_C_SOURCE 199309L/*sigaction */
#include <sys/types.h>/*pid_t */
#include <stdlib.h>/*NULL */
#include <unistd.h>/*write */
#include <semaphore.h>/*sem_t*/
#include <signal.h>/*sigaction*/

#define PINGPONGS 10

void PongHandler(int sig);
sem_t sem = {0};

int main()
{
    int pingpongs = PINGPONGS;
    struct sigaction pong = {0};
    pid_t parent_pid = getppid();

    pong.sa_handler = PongHandler;
    sigaction(SIGUSR1, &pong, NULL); 
    sigemptyset(&pong.sa_mask);
    sem_init(&sem, 0, 0);

    write(STDOUT_FILENO,"Pong!\n", 6); 
    kill(parent_pid, SIGUSR2);
    while (pingpongs)
    { 
        --pingpongs;
         

        while(sem_wait(&sem))
        {
            ;
        } 

        write(STDOUT_FILENO,"Pong!\n", 6); 
        kill(parent_pid, SIGUSR2);
    }
    
    return 0;    
}

void PongHandler(int sig)
{
	(void)sig;
	while(sem_post(&sem))
    {
        ;
    }
}
