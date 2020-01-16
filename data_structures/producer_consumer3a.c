/**********************************************************************;
* Project           : Data Structures
*
* Program name      : producer_consumer.c
*
* Author            : Michelle Gelfand		  
*
* Author	 	                 Reviewer 
* Michelle Gelfand               Waed B.					  
**********************************************************************/

#include <stdio.h>
#include <pthread.h>/*pthread_create*/
#include <semaphore.h>/*sem_init*/

#include "cbuff.h"

#define N 8
#define M 2
void *Consumer(void *param);

pthread_mutex_t mutex;
cbuff_t *cbuff;
sem_t occupied;
sem_t unoccupied;

size_t buffer;

void *Producer(void *param)
{
    (void)param;
    while(1)
    {
        sem_wait(&unoccupied);
        pthread_mutex_lock(&mutex);

        CBuffWrite(cbuff, &buffer, N);

        printf("\n producer: free space %lu", CBuffFreeSpace(cbuff));

        sem_post(&occupied);
        pthread_mutex_unlock(&mutex);
    }
}

void *Consumer(void *param)
{
    (void)param;
    while(1)
    {
        sem_wait(&occupied);
        pthread_mutex_lock(&mutex);

        CBuffRead(cbuff, &buffer, N);

        printf("\n consumer: free space %lu", CBuffFreeSpace(cbuff));

        pthread_mutex_unlock(&mutex);
        sem_post(&unoccupied);
    }
}

int main()
{
    pthread_t producer[M];
    pthread_t consumer[M];
    int i =0;

    cbuff = CBuffCreate(10*N);

    pthread_mutex_init(&mutex, NULL);
    sem_init(&occupied, 0, 1);
    sem_init(&unoccupied, 0, 0);

    for(; i<M; ++i)
    {
        pthread_create(&producer[i], NULL, Producer, &cbuff);
        pthread_create(&consumer[i], NULL, Consumer, &cbuff);
    }

    for(i =0; i<M; ++i)
    {
        pthread_detach(producer[i]);
    }

    for(i =0; i<M; ++i)
    {
         pthread_join(consumer[i], NULL);
    }

    return 0;
}
