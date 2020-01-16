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

#include "cbuff.h"
#include "test_tools.h"

#define N 8
#define BLOCKS 8

#define M 2
#define O 3

void *Consumer(void *param);

pthread_mutex_t mutex_read;
pthread_mutex_t mutex_write;
cbuff_t *cbuff;
size_t buffer;
size_t read_idx = 0;
size_t write_idx = 0;

void *Producer(void *param)
{
    (void)param;
    while(1)
    {
        pthread_mutex_lock(&mutex_write);

        if((write_idx +1)%BLOCKS != read_idx )
        {
            write_idx= (write_idx +1)%BLOCKS;
            CBuffWrite(cbuff, &buffer, N);

            printf(GREEN"\n write_idx: %lu", write_idx);

        }
        pthread_mutex_unlock(&mutex_write);
    }
}

void *Consumer(void *param)
{
    (void)param;
    while(1)
    {
        pthread_mutex_lock(&mutex_read);
        if(read_idx != write_idx && !CBuffIsEmpty(cbuff))
        {
            read_idx= (read_idx +1)%BLOCKS;
            CBuffRead(cbuff, &buffer, N);

            printf(YELLOW"\nread_idx: %lu ", read_idx);
        }
        pthread_mutex_unlock(&mutex_read);
    }
}

int main()
{
    pthread_t producer[M]; /*TODO arrays*/
    pthread_t consumer[O];
    int i =0;
    cbuff = CBuffCreate(BLOCKS*N);

    pthread_mutex_init(&mutex_write, NULL);
    pthread_mutex_init(&mutex_read, NULL);

    for(; i<M; ++i)
    {
        pthread_create(&producer[i], NULL, Producer, &cbuff);
    }

    for(i =0; i<O; ++i)
    {
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
