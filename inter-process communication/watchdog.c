#include <semaphore.h>/*sem_t */
#include <pthread.h>/*pthread_create */
#include <sys/ipc.h> 
#include <sys/sem.h>/*SETALL */
#include <sys/types.h>
#include <error.h> /*perror */
#include <sys/types.h>
#include <unistd.h>/*execv */
#include <signal.h>/*sigaction*/

#include "task.h"
#include "scheduler.h"

#define DELAY 0 /*time to start task*/
#define INTERVAL 1 /* time between tasks*/
#define SEM_WAIT -1
#define SEM_POST 1


volatile sig_atomic_t life_counter;

static int ImAliveYoureAlive(void *param);
static void Thread2(void *param);
static void InitScheduelr(char **argv);
static int ImAliveYoureAlive(void *param);
static void YoureAlive();
static void *LetMeDieHelper(void* param);
static int Binary_Semaphore_Init(int semid);
static void *RunScheduler(void *scheduler);

typedef union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *__buff;
}semun_t;


void *KeepMeAlive(char **argv)
{
    pthread_t kma = {0};
    scheduler_t *scheduler = SchedulerCreate();
    struct sembuf sem_buf = {0};

    int sem_id = {0};
    semun_t semun = {0};
    int status = Binary_Semaphore_Init(sem_id);
    key_t sem_key = ftok("/tmp", 'M');
    sem_id = semget(sem_key, 2, IPC_CREAT | IPC_EXCL);

    if( (-1 == sem_id) && semctl(sem_id, semun.val, GETVAL, NULL) )
    {
        /*no semaphore- no watchdog*/
        /*i have a semaphore & therefore watchdog*/
        sem_id = semget(sem_key, 1, IPC_CREAT);
        sem_buf.sem_num = 0;
    
        sem_buf.sem_op = SEM_WAIT;               
    
        sem_buf.sem_flg = 0;
        semop(sem_id, &sem_buf, 1);  
    }
    else
    {
        /*i had no previous semaphore, now i have a new semaphore,
        so i create a watchdog*/
        pid_t watchdog_pid = fork();

        if(!watchdog_pid)
        {
            sem_buf.sem_num = 0;
    
            sem_buf.sem_op = SEM_POST;               
    
            sem_buf.sem_flg = 1;

            /*im the child*/
            execv(argv[0], argv);
        }

    }

    /* sigaction(SIGUSR2, &LetHimDie);  */
    sigaction(SIGUSR1, &YoureAlive);
    SchedulerAdd(scheduler, DELAY, INTERVAL, ImAliveYoureAlive, argv[0]);
    
    if(semop(sem_id, &sem_buf, 1))
    {
        kma = pthread_create(&kma, NULL, RunScheduler, argv);
    }
}

static void *RunScheduler(void *scheduler)
{
    SchedulerRun((scheduler_t*)scheduler);
    return NULL;
}

static int ImAliveYoureAlive(void *param)
{
    kill(param ,SIGUSR1); /*I'm alive*/

    _sync_fetch_and_add(life_counter, 1);
 
    if( 3 <= life_counter)
    {
        pid_t child = fork();

        if(!child)
        {
            /*I'm the child*/
            execv(param, param);
        }
    }

    return 1; /*incomplete*/
}

static void YoureAlive()
{
    life_counter = 0;
}

static void *LetMeDieHelper(void* param)
{

}

static int Binary_Semaphore_Init(int semid)
{
    /*inits semaphore to value 1 */

    semun_t argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;

    return semctl(semid, 0, SETVAL, argument);
}