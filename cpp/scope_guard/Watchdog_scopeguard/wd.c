#define _XOPEN_SOURCE
#define _POSIX_SOURCE

#include <stdio.h>   /* printf */
#include <pthread.h> /* pthread_create, pthread_join */
#include <sys/sem.h> /* IPC_RMID */
#include <signal.h>  /* SIGUSR2 */
#include <stdlib.h>/*free */

#include "test_tools.h"
#include "wd.h"

#define NUM_OF_SEMS 2
#define CLIENT 0

watchdog_t *KeepMeAlive(char **argv)
{
	key_t sem_key = 0;
	int sem_id = 0;
	watchdog_t *watchdog_args = NULL;

	printf(GREEN "\n\nKEEP ME ALIIIVEE\n" WHITE);

	sem_key = GetSemKey();
	sem_id  = GetSemId(sem_key);

	SetArgsForWD(CLIENT, argv, sem_id, &watchdog_args);

	while( pthread_create(&watchdog_args->thread,
						  NULL, ImAliveYoureAlive, (void*)watchdog_args));
	return watchdog_args;
}

void LetMeDie(watchdog_t *watchdog_args)
{
	union semun sem_un = {0};

	printf(RED "LET ME DIEE\n" WHITE);

	kill(watchdog_args->partner_pid, SIGUSR2);
    pthread_join(watchdog_args->thread, NULL);

	semctl(watchdog_args->sem_id, NUM_OF_SEMS, IPC_RMID, sem_un);
	free(watchdog_args);
}
