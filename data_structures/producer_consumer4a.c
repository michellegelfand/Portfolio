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
#include <stdlib.h>/*rand*/
#include <time.h>/*time*/
#include <string.h>/*memset*/
#include <semaphore.h>/*sem*/

#include "cbuff.h"
#include "test_tools.h"

#define CONSUMER_NUM 3
#define N 8/*message length*/
#define M 1/*producer count*/
#define O 3/*consumer count*/

void *Consumer(void *param);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t sem; 

void *Producer(void *param)
{
    int random = 0;
    int i=0;
    
    while(1)
    {
        for(; i<CONSUMER_NUM; ++i)
        {
            while(sem_wait(&sem))
            {
                ;
            }
        } 
        pthread_mutex_lock(&mutex);
        
        srand(time(NULL));
        random = rand()%255;

        memset(param, random, N);
        printf(RED"\nproducer");

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
        printf("\n");
        sleep(1);
    }
}

void *Consumer(void *param)
{
    while(1)
    {  
        pthread_mutex_lock(&mutex);
        sem_post(&sem);

        while(pthread_cond_wait(&cond, &mutex))
        {
            ;
        }
        printf(GREEN"\nconsumer");
        printf("\n %s", (char*)param);

        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t producer[M];
    pthread_t consumer[O];
    char message[N] = {0};
    int i=0;

    sem_init(&sem, 0, 0);

    for(; i<M; ++i)
    {
        pthread_create(&producer[i], NULL, Producer, &message);
    }
    for(i =0; i<O; ++i)
    {
        pthread_create(&consumer[i], NULL, Consumer, &message);
    }

    for(i =0; i<M; ++i)
    {
        pthread_detach(producer[i]);
    }
   
    for(i =0; i<O; ++i)
    { 
        pthread_join(consumer[i], NULL);
    }
   
    for(i =0; i<M; ++i)
    {
        pthread_detach(producer[i]);
    }

    for(i =0; i<O; ++i)
    {
         pthread_join(consumer[i], NULL);
    }

    return 0;
}
