
/************************************************************;
* Project           : Data Structures
*
* Program name      : sys_v_sem.c
*
* Author            : Michelle Gelfand	
*************************************************************/

#define _POSIX_C_SOURCE 199309L /*sigaction */

#include <signal.h>/*kill */
#include <sys/types.h>/*pid_t */
#include <unistd.h>/*write */
#include <semaphore.h>/*sem_t*/
#include <sys/wait.h>/*wait*/


void parent_signal_handler();
void child_signal_handler();
void StartPingPong(size_t loops, pid_t child_pid, pid_t parent);

sem_t sem = {0};

int main()
{
    struct sigaction sa_parent;
    struct sigaction sa_child;
    size_t loops = 10;
    pid_t parent = 0;
    pid_t child_pid = 0;
    int child_status = 0;
    sem_init(&sem, 0 ,0);

    sigemptyset(&sa_parent.sa_mask);
    sigemptyset(&sa_child.sa_mask);

    sa_child.sa_handler = child_signal_handler;
    sa_parent.sa_handler = parent_signal_handler;
    sa_child.sa_flags = 0;
    sa_parent.sa_flags = 0;

    sigaction(SIGUSR2, &sa_parent, NULL);
    sigaction(SIGUSR1, &sa_child, NULL);
    child_pid = fork();

    /*serve! */
    if(child_pid)
    {
        kill(child_pid, SIGUSR1);
    }

    StartPingPong(loops, child_pid, parent);

    wait(&child_status);

    return 0;
}

void child_signal_handler()
{
    write(STDOUT_FILENO, "\npong", 5);
    sem_post(&sem);
}

void parent_signal_handler()
{
    write(STDOUT_FILENO, "\nping", 5);
    sem_post(&sem);
}

void StartPingPong(size_t loops, pid_t child_pid, pid_t parent)
{
    /*child_pid returns when when fork finishes */
    while(loops)
    {
        if(child_pid)
        {
            /*parent process */
            while(sem_wait(&sem))
            {
                ;  
            }    
            --loops;
            kill(child_pid, SIGUSR1);
        }
        else
        {
            /*child process */
            parent = getppid();
            
            while(sem_wait(&sem))
            {
                ;  
            }       
            --loops;
            kill(parent, SIGUSR2);
            
        }
    }
}
