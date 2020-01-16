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
#include <stdatomic.h>/*atomic_int*/ 

void *ConsumerMinusOne(void *num);

volatile atomic_int flag = 0;

void *ProducerPlusOne(void *num)
{
    while(1)
    {
        if(!flag)
        {
            *(int*)num += 1;
            printf("num = %d\n", *(int*)num);
            flag = 1;
        }
    }
}

void *ConsumerMinusOne(void *num)
{
    while(1)
    {
        if(flag)
        {
            *(int*)num -= 1;
            printf("num = %d\n", *(int*)num);
            flag = 0;
        }
    }
}

int main()
{
    pthread_t producer;
    pthread_t consumer;
    int num = 0;

    pthread_create(&producer, NULL, ProducerPlusOne, &num );
    pthread_create(&consumer, NULL, ConsumerMinusOne, &num );
    
    pthread_detach(producer);
    pthread_join(consumer, NULL);
    
    return 0;
}
