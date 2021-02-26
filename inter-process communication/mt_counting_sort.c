/******************************************************************************;
* Project           : Data Structures
*
* Program name      : mt_counting_sort.c
*
* Author            : Michelle Gelfand
*
* Purpose           : This program sorts the letters in the
                      dictionary in multiple threads
*
*                     Author	 	             Reviewer
*               	  Michelle Gelfand           Amitay N. *
********************************************************************/

#include <stdlib.h> /*calloc*/
#include <stdio.h>/*fopen*/    
#include <pthread.h>/*pthread_create*/
#include <string.h>/*strcpy*/

#define NUM_OF_DICTIONARIES 1
#define NUM_OF_THREADS 10
#define THREAD_RANGE ( *letter_count / NUM_OF_THREADS)   
#define LEFTOVER ( *letter_count % NUM_OF_THREADS) 

#define FREE(ptr) free(ptr); ptr = NULL;

typedef struct args
{
    size_t begin;
    size_t end;
    unsigned char *letters;
    size_t *summed_sorts;
    pthread_mutex_t *transfer_mutex;
}args_t;

void InitDictionary(unsigned char **letters, unsigned char **letters_cpy,
                    size_t **summed_sorts, size_t *letter_count);
void InitThreadArgs(pthread_t *threads, args_t *args, pthread_mutex_t mutex,
        size_t *summed_sorts, unsigned char *letters, 
                     size_t *letter_count);
void *CountSort(void *param);
void MergeThreadCounts(size_t *summed_sorts, unsigned char *letters, 
                         unsigned char *letters_cpy, size_t *letter_count);

int main() 
{   
    unsigned char *letters = NULL;
    unsigned char *letters_cpy = NULL;
    size_t letter_count = 0;
    size_t i = 0;

    args_t args[NUM_OF_THREADS];
    pthread_t threads[NUM_OF_THREADS];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    size_t *summed_sorts = (size_t*)calloc(sizeof(size_t), 256);

    InitDictionary(&letters, &letters_cpy, &summed_sorts, &letter_count);

    InitThreadArgs(threads, args, mutex, summed_sorts, letters, &letter_count);

    MergeThreadCounts(summed_sorts, letters, letters_cpy, &letter_count);

    for(i =0; i < letter_count-1; ++i)
    {
        printf("%c", letters_cpy[i]);
    }

    FREE(letters);
    FREE(letters_cpy);
    FREE(summed_sorts);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void InitDictionary(unsigned char **letters, unsigned char **letters_cpy,
                    size_t **summed_sorts, size_t *letter_count) 
{ 

    FILE *dict = fopen("/usr/share/dict/american-english","r");
    size_t i =0;
    size_t j = 0;
    size_t word_len =0;
    char buffer[20] ={0};

    if(!dict)
    {
        FREE(summed_sorts);
        perror("BUG");
        abort();
    }

    while( EOF != fgetc(dict))
    {
		++(*letter_count);
    }

    *letter_count *= NUM_OF_DICTIONARIES;

    *letters = (unsigned char*)calloc(*letter_count,(sizeof(unsigned char)));
    *letters_cpy = (unsigned char*)calloc(*letter_count,(sizeof(unsigned char)));
   
    if(!*letters || !*letters_cpy || !*summed_sorts)
    {
        if(*letters)
        {
            FREE(*letters);
        }
        if(*letters_cpy)
        {
            FREE(*letters_cpy);
        }
        if(*summed_sorts)
        {
            FREE(*summed_sorts);
        }
        perror("BUG");
        abort();
    }
		
    for(; i< NUM_OF_DICTIONARIES; ++i)
    {
        rewind(dict);
        
        while( EOF != fscanf(dict, "%s", buffer))
        {
            word_len = strlen((char*)&buffer);
            memcpy(&(*letters)[j], &buffer, word_len);
            j += word_len;
        }
    }

    fclose(dict);
}

void InitThreadArgs(pthread_t *threads, args_t *args, pthread_mutex_t mutex,
                    size_t *summed_sorts, unsigned char *letters, 
                                size_t *letter_count)
{   
    size_t i =0;

    for(i=0; i<NUM_OF_THREADS; ++i)
    {
        (args[i]).begin = i * THREAD_RANGE;
        (args[i]).end =  (args[i]).begin + THREAD_RANGE - 1;
        (args[i]).letters = letters;
        (args[i]).transfer_mutex = &mutex;
        (args[i]).summed_sorts = summed_sorts;
    }

    ((args[NUM_OF_THREADS-1])).end += LEFTOVER;

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, CountSort, &(args[i]));
    }

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }
}     

void *CountSort(void *param)
{
    size_t begin = ((args_t*)param)->begin;
    size_t end = ((args_t*)param)->end;
    unsigned char *letters = (unsigned char*)(((args_t*)param)->letters);
    size_t local_sort[256] = {0};
    size_t i =0;

    for(i = begin; i< end; ++i)
    {
        local_sort[(size_t)letters[i]] += 1;   
    }

    pthread_mutex_lock((((args_t*)param)->transfer_mutex));

    for(i = 0; i< 256; ++i)
    {
       ((args_t*)param)->summed_sorts[i] += local_sort[i];
    }

    pthread_mutex_unlock((((args_t*)param)->transfer_mutex));

    return NULL;
}

void MergeThreadCounts(size_t *summed_sorts, unsigned char *letters, 
                         unsigned char *letters_cpy, size_t *letter_count)
{
    size_t i =0;

    /*accumulate counts*/
	for(i = 1; i< 256; ++i)
	{
		summed_sorts[i]+= summed_sorts[i-1];
	}

	/*fill sorted array*/
	for(i = 0; i < *letter_count-1; ++i)
	{
		letters_cpy[ (summed_sorts[letters[i]])] = letters[i];   
        --summed_sorts[letters[i]];   
	}
         
	/*transfer sorted array to original array*/
	for(i = 0; i<*letter_count; ++i)
	{
		letters[i] = letters_cpy[i];
	}
     
}     
