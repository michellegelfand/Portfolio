
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
#include <sys/wait.h>/*wait */

#define PINGPONGS 10

void Ping(int sig);
void StartPingPong(pid_t child, size_t pingpongs);

sem_t sem = {0};

int main()
{
    int pingpongs = PINGPONGS;
    pid_t child = {0};
    int child_status = 0;
    struct sigaction ping = {0};

    sem_init(&sem, 0 ,0);
    ping.sa_handler = Ping;

    sigemptyset(&ping.sa_mask);

    sigaction(SIGUSR2, &ping, NULL); 

    child = fork();

    StartPingPong(child, pingpongs);

	wait(&child_status);
    return 0;    
}

void StartPingPong(pid_t child, size_t pingpongs)
{
    if(child)
    {
        /*im the parent */
        while (0 != pingpongs)
        {
            while(sem_wait(&sem))
            {
        	   ;
            }

            write(STDOUT_FILENO,"Ping!\n", 6); 
            kill(child, SIGUSR1);
            --pingpongs;
        }
    }
    else
    {
        /*im the child */
        char *const args[2]	= {"pong.out", 0};
        execv("pong2.out", args);
    }
}

void Ping(int sig)
{
    (void)sig;
    while(sem_post(&sem))
    {
        ;
    }
}
