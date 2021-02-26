/**********************************************************************;
* Project           : Data Structures
*
* Author            : Michelle Gelfand
*
* Review Status		: Approved
*
*                     Author	 	             Reviewer 
*                 	  Michelle Gelfand           Doron W. 														  
*******************************************************************/

#include <stdio.h>

#include "uid.h"
#include <pthread.h>/*threads*/

#define NUM_THREADS 5

typedef struct args
{
    pid_t pid[10];
}args_t;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t barrier = PTHREAD_COND_INITIALIZER;

void *CreateUids(void *param);
void PrintUID(uniq_id_t uid);

int main()
{	
    pthread_t threads[NUM_THREADS];
    size_t i = 0;
    size_t counter = 0;

    for(i = 0; i < NUM_THREADS; ++i )
    {
        pthread_create(&threads[i], NULL, CreateUids, &counter);
    }

    for(i = 0; i < NUM_THREADS; ++i )
    {
        pthread_join(threads[i], NULL);
    }

	return 0;
}

void PrintUID(uniq_id_t uid)
{
	printf("\n %lu - %ld - %d\n", uid.count, uid.time, uid.pid);
}

void *CreateUids(void *param)
{
    int i = 0;
    uniq_id_t uid = {0};

    pthread_mutex_lock(&mutex);
    ++*(size_t*)param;

    if(NUM_THREADS > *(size_t*)param)
    {
        pthread_cond_wait(&barrier, &mutex);
    }
    else
    {
        pthread_cond_broadcast(&barrier);
        *(size_t*)param = 0;
    }

    pthread_mutex_unlock(&mutex);

    for(; i < 3; ++i)
    {
        uid = UidCreate();

        PrintUID(uid);
    }
    
    return NULL;
}
