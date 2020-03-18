#define _XOPEN_SOURCE
#define _POSIX_SOURCE

#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc */
#include <signal.h>  /* SIGUSR1, SIGUSR2 */
#include <unistd.h>  /* fork, execv, getppid */
#include <sys/sem.h> /* semop */

#include "test_tools.h" 
#include "wd_shared.h"

#define NUM_OF_SEMS 2
#define SEM_PERMISSIONS 0666
#define DELAY 0
#define INTERVAL 1
#define WAIT  -1
#define POST   1

#define WHICH(wd_or_c) wd_or_c? printf(YELLOW"WATCHDOG SAYS:"WHITE): printf(BLUE"CLIENT SAYS:"WHITE);

static void UpdateSemaphore(int client_or_wd, int wait_or_post, int flag, int sem_id);
static void AssurePingPong(watchdog_t *wd_args);
static void SetUpSignals();
static int  ImAliveTickTock(void *param);
static void KmaHandler(int sig_num);
static void LmdHandler(int sig_num);
static void CleanUp(watchdog_t *wd_args, uniq_id_t task_id);

int print_is_wd = 0;  
volatile sig_atomic_t counter = 3;
int let_me_die = 0;

void *ImAliveYoureAlive(void *args)
{
	watchdog_t *wd_args = (watchdog_t*)args;
	uniq_id_t task_id = {0};

	if(wd_args->who_am_i) /* TODO */
	{
		print_is_wd = wd_args->who_am_i;
	}

	wd_args->scheduler = SchedulerCreate();

	if(NULL == wd_args->scheduler)
	{
		perror("scheduler alloc failed");
		abort();
	}

	UpdateSemaphore(wd_args->who_am_i, WAIT, SEM_UNDO, wd_args->sem_id);
	let_me_die = 0;

    while(!let_me_die)
    {
		AssurePingPong(wd_args);
		SetUpSignals();

    	UpdateSemaphore(!(wd_args->who_am_i), POST, SEM_UNDO, wd_args->sem_id);
        UpdateSemaphore(wd_args->who_am_i, WAIT, SEM_UNDO, wd_args->sem_id);

		task_id = SchedulerAdd(wd_args->scheduler, DELAY, INTERVAL, ImAliveTickTock, wd_args);

		while(0 < counter)
		{
			SchedulerRun(wd_args->scheduler);

			if(let_me_die)
			{	
				break;
			}			
		}

		SchedulerRemove(wd_args->scheduler, task_id);
		counter = 3;
	}

	CleanUp(wd_args, task_id);

	return NULL;
}

/******************************************************************************/

static void AssurePingPong(watchdog_t *wd_args)
{
	int partner_sem_state = semctl(wd_args->sem_id, !(wd_args->who_am_i) , GETVAL);
	semun_t semun  = {0};

	if(0 != partner_sem_state)
	{
		semun.val = 1;
		semctl(wd_args->sem_id, !(wd_args->who_am_i), SETVAL, semun);

		wd_args->partner_pid = fork();
	
        if((!wd_args->partner_pid) && (!wd_args->who_am_i))
        {
            execv("wd_exec.out", wd_args->argv);
        }

		if((!wd_args->partner_pid) && (wd_args->who_am_i))
        {
            execv(wd_args->argv[0], wd_args->argv);
        }

		signal(SIGCHLD,SIG_IGN); 
	}
	else
	{
		wd_args->partner_pid = getppid();
	}
}

/******************************************************************************/

static int ImAliveTickTock(void *param)
{
	kill(((watchdog_t*)param)->partner_pid, SIGUSR1);

	--counter;
	
	SchedulerStop(((watchdog_t*)param)->scheduler);

	return 1;
}

/******************************************************************************/

static void UpdateSemaphore(int client_or_wd, int wait_or_post,
							int flag, int sem_id)
{
    struct sembuf sem_buf = {0};

    sem_buf.sem_num = client_or_wd;
    sem_buf.sem_op  = wait_or_post;               
    sem_buf.sem_flg = flag;
    semop(sem_id, &sem_buf, 1); 
}

/******************************************************************************/

static void SetUpSignals()
{
    struct sigaction sigact_kma = {0};
    struct sigaction sigact_lmd = {0};

	sigact_kma.sa_handler = KmaHandler;

	if(-1 == sigaction(SIGUSR1, &sigact_kma, NULL))
	{
	    perror("SetUpSignals, kma");
		abort();
	}

    sigact_lmd.sa_handler = LmdHandler;

	if(-1 == sigaction(SIGUSR2, &sigact_lmd, NULL))
	{
	    perror("SetUpSignals, lma");
		abort();
	}
}

/******************************************************************************/

static void KmaHandler(int sig_num)
{
	(void)sig_num;

    counter = 3;
	WHICH(print_is_wd); printf("Ping! Pong! recieved my partner is alive\n"); /* TODO */
}

/******************************************************************************/

static void LmdHandler(int sig_num)
{
	(void)sig_num;

	let_me_die = 1;
	WHICH(print_is_wd); printf("Recieved let me die! Goodbye!\n"); /* TODO */
}

/******************************************************************************/

static void CleanUp(watchdog_t *wd_args, uniq_id_t task_id)
{
	if(wd_args->who_am_i)
	{
		kill(wd_args->partner_pid, SIGUSR2);
	}

	SchedulerRemove(wd_args->scheduler, task_id);
	SchedulerDestroy(wd_args->scheduler);
}

/******************************************************************************/

key_t GetSemKey()
{
    key_t sem_key = ftok("/tmp", 'a');

    if(-1 == sem_key)
    {
        perror("GetSemKey no key\n");
        abort();
    }

    return sem_key;
}

/******************************************************************************/

int GetSemId(key_t key)
{
    int sem_id = semget(key, NUM_OF_SEMS, IPC_CREAT | IPC_EXCL | SEM_PERMISSIONS);
    unsigned short sem_val[2]= {0};
    semun_t sem_un = {0};
    
    if(-1 != sem_id)
    {
        /*semset doesnt exist, create it */
        sem_val[0] = 1;
        sem_val[1] = 1;
        sem_un.array = sem_val;

        if(-1 == semctl(sem_id, 0, SETALL, sem_un))
        {
            perror("GetSemID failed");
            abort();
        }
    }
    else
    {
        /*already have semaphores, grab 'em */
        sem_id = semget(key, NUM_OF_SEMS, IPC_CREAT | SEM_PERMISSIONS);
    }
    
    return sem_id;
}

/******************************************************************************/

void SetArgsForWD(int who_am_i, char **argv, int sem_id, watchdog_t **wd_args)
{
	*wd_args = (watchdog_t*)malloc(sizeof(watchdog_t));

	(*wd_args)->who_am_i = who_am_i;
	(*wd_args)->argv = argv;
	(*wd_args)->sem_id = sem_id;
}

