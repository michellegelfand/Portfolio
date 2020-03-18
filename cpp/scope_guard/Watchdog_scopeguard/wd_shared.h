#ifndef __WD_SHARED_H__
#define __WD_SHARED_H__

#include "scheduler.h"
#include <pthread.h>

typedef union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;

}semun_t;

typedef struct watchdog
{
	scheduler_t *scheduler;
	pthread_t thread;
    int who_am_i; /* 0-client , 1-watchdog */
    pid_t partner_pid;
    char **argv;
    int sem_id;
}watchdog_t;

void *ImAliveYoureAlive(void *args);
key_t GetSemKey();
int   GetSemId(key_t key);
void  SetArgsForWD(int who_am_i, char **argv, int sem_id, watchdog_t **watchdog_args);


#endif /* __WD_SHARED_H__ */
