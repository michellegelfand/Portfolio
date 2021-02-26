/******************************************************************************;
* Project           : Data Structures
*
* Program name      : mt_shuffle_sort.c
*
* Author            : Michelle Gelfand
*
* Purpose           : This program shuffles & sorts the words in the
                      dictionary in multiple threads
*
*                     Author	 	             Reviewer
*               	  Michelle Gelfand           Saar Y. *
********************************************************************/

#include <stdlib.h>   /* calloc */
#include <stdio.h>    /* fopen, printf */    
#include <pthread.h>  /* pthread_create */
#include <string.h>   /* strcmp */
#include <unistd.h>   /* ssize_t */

#define FREE(ptr) free(ptr); ptr = NULL;
#define RANGE ((word_count * NUM_OF_DICTS)/NUM_OF_THREADS)
#define LEFTOVER (word_count * NUM_OF_DICTS) % NUM_OF_THREADS
#define NUM_OF_DICTS   2
#define NUM_OF_THREADS 3
#define ASCII 256

typedef struct args
{
    size_t from;
    size_t to;
    unsigned char **words;
    size_t word_count;
    unsigned char **shared_result;
    size_t max_word_len;
}args_t;


static unsigned char **InitArrays(FILE *dict, unsigned char **words,  
                        size_t *word_count, size_t *max_word_len);
static void Shuffler(unsigned char **words, size_t word_count);
static void Swap(unsigned char **ptr1, unsigned char **ptr2);
static void InitThreads(unsigned char **shared_result, unsigned char **words,
						size_t word_count, args_t *args, pthread_t *threads,
						size_t max_word_len);
static void *RadixMT(void *param);
static void RadixSort(unsigned char **local_sort, size_t range,
					  size_t max_word_len,  unsigned char **sort_for_iteration);
static void WordCounts(size_t *counts,unsigned char **local_sort,
        size_t range, size_t char_idx);
static void AccumulateCounts(size_t *counts);
static void SharedResultFailHandler(unsigned char **words, size_t word_count);
static void WordsFailHandler(unsigned char **words, size_t i);
static void MergeArrays(unsigned char **arr, unsigned char **arr2,
                 size_t length1, size_t length2, unsigned char **merged);

int main() 
{   
    unsigned char **words = NULL;
    unsigned char **shared_result = NULL;
    unsigned char **merged = NULL;
    pthread_t threads[NUM_OF_THREADS];
    args_t args[NUM_OF_THREADS] = {0};
    size_t max_word_len =0;
    size_t i =0;
    ssize_t j = 0;
    size_t word_count = 0;
    size_t length1 = 0;
    size_t length2 = 0;
    FILE *out  = fopen("out.txt", "w"); 
    FILE *dict = fopen("/usr/share/dict/american-english", "r"); 
   /* FILE *dict = fopen("dictio.txt", "r"); */

    if(!dict)
    {
        perror("BUG");
        abort();
    }

    words = InitArrays(dict, words, &word_count, &max_word_len);

    shared_result = calloc(word_count * NUM_OF_DICTS, sizeof(char*));

    if(!shared_result)
    {
        SharedResultFailHandler(words, word_count);
    }

 	Shuffler(words, word_count);

    InitThreads(shared_result, words, word_count, args, threads, max_word_len);

    for(j =0; j<  NUM_OF_THREADS -1 ; ++j)
    {
        length1  = (j+1)* RANGE;

        if(j != NUM_OF_THREADS- 2)
        {
            length2  = RANGE;
        }
        else
        {
            length2 += LEFTOVER;
        }
               
        merged   = calloc(length1 +length2, sizeof(char*));

        MergeArrays(shared_result, shared_result + length1,
                                     length1, length2, merged);

        memcpy(shared_result, merged, (length1 +length2)*sizeof(char*));

        FREE(merged);

    }

    for(i =0; i < word_count * NUM_OF_DICTS ; ++i)
    {
        fprintf(out,"%s \n", shared_result[i]);
    }

	WordsFailHandler(words, (word_count * NUM_OF_DICTS - 1));
	WordsFailHandler(shared_result,(word_count * NUM_OF_DICTS - 1));
	fclose(dict);
	fclose(out);

    return 0;
}

/******************************************************************************/

static unsigned char **InitArrays(FILE *dict, unsigned char **words,
                        		  size_t *word_count, size_t *max_word_len)
{
    size_t i =0;
    size_t j =0;
    char buffer[30] = {0};

    while( EOF != fscanf(dict, "%s", buffer))
    {
		++(*word_count);
    }

    words =(unsigned char**)calloc(*word_count * NUM_OF_DICTS, sizeof(char*)); 

    for(; j < NUM_OF_DICTS; ++j)
    {
        rewind(dict);

        while(EOF != fscanf(dict, "%s", buffer))
        {
            *(words+i) = calloc(30, sizeof(char));

            if(!words[i])
            {
                WordsFailHandler(words, i); 
            }

            memcpy(words[i], buffer, strlen(buffer)+1);
            i += 1;

            if( *max_word_len < strlen(buffer))
            {
                *max_word_len = strlen(buffer);
            }
        } 
    }

    return words;
}

/******************************************************************************/

static void Shuffler(unsigned char **words, size_t word_count)
{
    size_t i =0;

    srand(time(NULL));

    for(i =0; i < (word_count * NUM_OF_DICTS); ++i)
    {
        Swap(&words[i], &words[rand() % (word_count * NUM_OF_DICTS)]);
    }
}

/******************************************************************************/

static void Swap(unsigned char **word1, unsigned char **word2)
{
    unsigned char *tmp = NULL;

    tmp = *word1;
    *word1 = *word2;
    *word2 = tmp;
}

/******************************************************************************/

static void InitThreads(unsigned char **shared_result, unsigned char **words,
						size_t word_count,args_t *args, pthread_t *threads,
						size_t max_word_len)
{
    size_t i =0;

    for(i =0; i < NUM_OF_THREADS; ++i)
    {
        args[i].from = i * RANGE; 
        args[i].to = args[i].from + RANGE -1;
        args[i].shared_result = shared_result;
        args[i].words = words;
        args[i].word_count = word_count;
        args[i].max_word_len = max_word_len;

        if(NUM_OF_THREADS -1 == i)
        {
            args[NUM_OF_THREADS -1].to += LEFTOVER;
        } 

        pthread_create(&threads[i], NULL, RadixMT, &args[i]);
    }

	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
}

/******************************************************************************/

static void *RadixMT(void *param)
{
    size_t i = 0;
	size_t j = 0;
	size_t idx = 0;
    args_t *args = ((args_t*)param);
	size_t range = (args->to - args->from) +1 ;

	/***  init local sort ***/
  	unsigned char **local_sort = calloc(range, sizeof(char*));
	unsigned char **sort_for_iteration = calloc( range , sizeof(char*));

	if( (!sort_for_iteration) || (!local_sort) )
    {
	   SharedResultFailHandler(args->words, args->word_count);
       perror("BUG");
       abort();
    }

    for(j=0, i = args->from; i <= args->to; ++j, ++i)
    {
        local_sort[j] = calloc(30, sizeof(char));

    	strcpy((char*)local_sort[j], (char*)args->words[i]);
    }   

    RadixSort(local_sort, range, args->max_word_len, sort_for_iteration);

	for(i = 0; i < range; ++i)
	{
		idx = args->from++;
		args->shared_result[idx] = local_sort[i];
	}

	free(local_sort);
	free(sort_for_iteration);

	return NULL;
}

/******************************************************************************/

static void RadixSort(unsigned char **local_sort, size_t range,
					  size_t max_word_len, unsigned char **sort_for_iteration)
{
    size_t i = 0;
    ssize_t j = 0;
	size_t k = 0;
    size_t counts[ASCII] = {0};
    size_t char_idx = max_word_len - 1;
    unsigned char ch = 0;

    for (i = 0; i < max_word_len ; ++i)
    {
        memset (counts, 0, ASCII* sizeof(size_t));

        WordCounts(counts, local_sort, range, char_idx);

        AccumulateCounts(counts);

        for(j = range - 1; j >= 0; --j)
        {
            ch = local_sort[j][char_idx];
			
			if(!ch)
			{
				ch = 0;
			}

            counts[ch] -= 1;

            sort_for_iteration[counts[ch]] = local_sort[j];
        }

		for(k = 0; k < range; ++k)
		{
			 local_sort[k] =  sort_for_iteration[k];
		}

        --char_idx;
    }
}

/******************************************************************************/

static void WordCounts(size_t *counts,unsigned char **local_sort,
        size_t range, size_t char_idx)
{
    size_t i = 0;
    unsigned char ch = 0;

    for (i = 0; i < range; ++i)
    {   
        ch = local_sort[i][char_idx];
        counts[(size_t)ch] += 1;
    }
}

/******************************************************************************/

static void AccumulateCounts(size_t *counts)
{
    size_t i = 0;

    for (i = 1; i <= (ASCII - 1); ++i)
    {
        counts[i] += counts[i-1];
    }
}
/******************************************************************************/

static void SharedResultFailHandler(unsigned char **words, size_t word_count)
{
    size_t i = 0;

    for(i = 0; i < (word_count * NUM_OF_DICTS); ++i)
    {
        FREE(words[i]);
    }

    FREE(words);
    perror("BUG");
    abort();
}

/******************************************************************************/

static void WordsFailHandler(unsigned char **words, size_t i)
{
    for(; 0 < i; --i)
    {
        FREE(words[i]);
    }

    if(words[0])
    {
        FREE(words[0]);
    }

    FREE(words);
}

static void MergeArrays(unsigned char **arr1, unsigned char **arr2,
                 size_t length1, size_t length2, unsigned char **merged)   
{ 
    size_t i = 0;
    size_t j = 0;
    size_t k = 0; 

    while ((i < length1) && (j < length2)) 
    { 
        if (strcmp((char*)arr1[i], (char*)arr2[j]) < 0) 
        {       
            merged[k] = arr1[i];
            ++i;
            ++k;
        } 
        else
        {
            merged[k] = arr2[j];
            ++k;
            ++j;
        }    
    } 
  
    while (i < length1) 
    {
        merged[k] = arr1[i];
        ++k;
        ++i;
    }   
  
    while (j < length2) 
    {
        merged[k] = arr2[j];
        ++k;
        ++j;
    }   
} 
