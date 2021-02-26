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


#include <stdio.h>     /* printf */
#include <stdlib.h>    /* malloc */
#include <pthread.h>   /* pthread_create */
#include <semaphore.h> /* semphore */

#define FREE(ptr) free(ptr); ptr = NULL;
#define THREADS 10  

void *Sum(void* args);

typedef struct args
{
    size_t sum;
    size_t num;
    size_t thread_num;
    size_t thread_count;
    pthread_mutex_t *mutex_key;
    sem_t sem;
}args_t;

int main()
{
    size_t num = 10535467372;
    size_t sum = 0;
    size_t i = 0;   
    size_t thread_count = THREADS;
    pthread_mutex_t mutex;
    pthread_t *threads = NULL;
    args_t    *args    = calloc(thread_count, sizeof(args_t));
    
    if(!args)
    {
        return 1;
    }

    threads = calloc(thread_count, sizeof(pthread_t));

    if(!threads)
    {
        FREE(args);
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < thread_count; ++i)
    {
        (&args[i])->num = num;
        (&args[i])->sum = 0;
        (&args[i])->thread_num = i;
        (&args[i])->thread_count = thread_count;
        (&args[i])->mutex_key = &mutex;

        while( 0 != pthread_create(&threads[i], NULL, Sum, (&args[i]))){};

        pthread_detach(threads[i]); 
    }

    for(i = 0; i < (&args[i])->thread_count; ++i)
    {
        while(sem_wait(&(&args[i])->sem)){};  
    }

    printf("%lu\n", thread_count);

    for(i = 0; i < ((&args[i])->thread_count); ++i)
    {
        printf("i:%lu   %lu\n", i, args[i].sum);
        sum += args[i].sum;
    }

    if(num % thread_count)
    {
        sum += num;
    }

    printf("Sum of dividers of %ld is %ld.\n", num, sum);

    FREE(args);
    FREE(threads);

    return 0;
}

void *Sum(void* args)
{
    args_t thread_args = *(args_t*)args;
    size_t i = 0;
    size_t divider = 0;
    size_t sums_this_thread = ((args_t*)args)->num / 
                              ((args_t*)args)->thread_count;

    for (i = 1; i <= sums_this_thread; ++i)
    {
        divider = i + (sums_this_thread * thread_args.thread_num);
        
        if (!(((args_t*)args)->num % divider))
        {
            pthread_mutex_lock(((args_t*)args)->mutex_key);
         
            ((args_t*)args)->sum += divider;  
       
            pthread_mutex_unlock(((args_t*)args)->mutex_key);
        }
    }

    sem_post(&((args_t*)args)->sem);

    return NULL;
}
