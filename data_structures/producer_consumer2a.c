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

#include "doubly_list.h"

#define N 2

void *Consumer(void *param);

pthread_mutex_t mutex;
dl_list_t *list = NULL;

void *Producer(void *param)
{
    int data =1;
    (void)param;

    while(1)
    {
        pthread_mutex_lock(&mutex);

        DListPushBack(list, &data);
        printf("popped. count: %lu\n", DListCount(list));
 
        pthread_mutex_unlock(&mutex);
    }
}

void *Consumer(void *param)
{
    (void)param;
    while(1)
    {
        while(DListIsEmpty(list))
        {
            ;
        }

        pthread_mutex_lock(&mutex);

        /*in case 2 consumers exit above while at same time*/
        if(!DListIsEmpty(list))
        {
            if(!DListPopFront(list))
            {
                return NULL;
            }
        
            printf("pushed. count: %lu\n", DListCount(list));
        }

        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t producer[N]; 
    pthread_t consumer[N];
    int i=0;

    list = DListCreate();
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
