/**********************************************************************;
* Project           : Data Structures
*
* Program name      : 100kthreads.c
*
* Author            : Michelle Gelfand		  
*
* Author	 	                 Reviewer 
* Michelle Gelfand               Evegeni S.					  
**********************************************************************/

#include <pthread.h> /*pthread_create*/
#include <stdio.h>/*printf*/
#include <semaphore.h>

typedef struct args
{
    size_t *arr;
    pthread_t thread_num;
    sem_t *sem;
}args_t;


void *InitArrThreadNum(void *args)
{
    size_t num = ((args_t*)args)->thread_num;

    ((args_t*)args)->arr[num-1] = num;

    sem_post(((args_t*)args)->sem);
    
    return NULL;
}

int main()
{
    size_t i = 0;
    size_t array[100000] = {0};
    size_t thread_nums[100000]= {0};
    sem_t sem;
 
    sem_init(&sem, 0, 0);
 
    for(; i<100000 ; ++i )
    {
        args_t args;
        thread_nums[i] = i+1;
        args.arr = array;
        args.thread_num =  thread_nums[i];
        args.sem = &sem;

        while (0 != pthread_create (&(thread_nums[i]), NULL,
                    &InitArrThreadNum, &args))
        {
            ;
        } 

        pthread_detach(thread_nums[i]);     
    }

    for(i = 0; i < 100000; ++i)
    {
        while(sem_wait(&sem))
        {
            ;
        }
    }

    for(i = 0; i < 99999; ++i)
    {
        printf("%lu ", array[i]);

        if(!(i%10))
        {
            printf("\n");
        }

    }

    return 0;
}