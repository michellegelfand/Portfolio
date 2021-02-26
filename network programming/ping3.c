
/************************************************************;
* Project           : Data Structures
*
* Program name      : sys_v_sem.c
*
* Author            : Michelle Gelfand	
*************************************************************/

#define _POSIX_C_SOURCE 199309L /*sigaction */
#include <sys/types.h>          /*pid_t */
#include <signal.h>             /*sig_atomic_t */
#include <stdlib.h>             /*abort, NULL */
#include <unistd.h>             /*write */
#include <stdio.h>              /*printf */
#include <semaphore.h>/*sem_t*/

#define PINGPONGS 10

void Ping(int signum, siginfo_t *siginfo, void *ucontext);

sem_t sem = {0};

pid_t pong_id = {0};

int main()
{
    int pingpongs = PINGPONGS;
    struct sigaction ping = {0};

    ping.sa_flags = SA_SIGINFO;
    ping.sa_sigaction = Ping;

    sigemptyset(&ping.sa_mask);

    if (0 != sigaction(SIGUSR2, &ping, NULL))
    {
        perror("BUG!");
        abort();
    }

    while (pingpongs)
    {
        while (sem_wait(&sem))
        {
            ;
        }
            
        write(STDOUT_FILENO, "\nPING! clank\n", 12 );
        kill(pong_id, SIGUSR1);
        --pingpongs;
    }

    return 0;
}

void Ping(int signum, siginfo_t *siginfo, void *ucontext)
{
    (void)signum;
    (void)ucontext;
    pong_id = siginfo->si_pid;
    sem_post(&sem);
}
