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

#include "doubly_list.h"
#define N 2

void *Consumer(void *param);

pthread_mutex_t mutex;
dl_list_t *list = NULL;
sem_t sem;

void *Producer(void *param)
{
    int data =1;

    (void)param;

    while(1)
    {
        pthread_mutex_lock(&mutex);

        DListPushBack(list, &data);
        sem_post(&sem);
        printf("producer %lu\n", DListCount(list));

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}  


void *Consumer(void *param)
{
    (void)param;

    while(1)
    {
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);

        if (!DListPopFront(list))
        {
            perror("BUG");
            pthread_mutex_unlock(&mutex);
            return NULL; 
        }

        printf("consumer %lu\n", DListCount(list));

        pthread_mutex_unlock(&mutex);
        
    }
}

int main()
{
    pthread_t producer[N]; 
    pthread_t consumer[N];
    int i=0;

    list = DListCreate();
    sem_init(&sem, 0,0);
    pthread_mutex_init(&mutex, NULL);

    for(; i<N; ++i)
    {
        pthread_create(&producer[i], NULL, Producer, &list);
        pthread_create(&consumer[i], NULL, Consumer, &list);
    }

    for(i =0; i<N; ++i)
    {
        pthread_detach(producer[i]);
    }
   
    for(i =0; i<N; ++i)
    { 
        pthread_join(consumer[i], NULL);
    }

    return 0;
}
