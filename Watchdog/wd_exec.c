#define _XOPEN_SOURCE
#define _POSIX_SOURCE

#include <sys/sem.h> /* key_t */
#include <stdio.h> /* printf,TODO */
#include <unistd.h>  /* getpid TODO */
#include "test_tools.h" /*TODO*/
#include "wd_shared.h"

#define WATCHDOG 1

int main(int argc, char **argv)
{
	watchdog_t *watchdog_args = NULL;
	key_t sem_key = 0;
	int sem_id = 0;

	printf(YELLOW"WATCHDOG HAS LAUNCHED\n"WHITE);
	(void)argc;

	sem_key = GetSemKey();
    sem_id  = GetSemId(sem_key);

	SetArgsForWD(WATCHDOG, argv, sem_id, &watchdog_args);

    ImAliveYoureAlive(watchdog_args);

    return 0;
}

