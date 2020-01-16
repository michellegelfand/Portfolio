/**********************************************************************;
* Project           : Data Structures
*
* Program name      : hashtable.c
*
* Author            : Michelle Gelfand
*
* Purpose           : This program provides the user	
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 04/08/2019       	  Michelle Gelfand           Olga K.														  
*******************************************************************/

#include <stdio.h>/*printf */
#include <string.h>/*strcmp */
#include <stdlib.h>/*malloc */

#include "hashtable.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

int IsMatch(const void *data1, void *param, const void *data2);
size_t HashFunc(const void *data);
int Visitor (void *data, void *param);
int DictMatch(const void *data1, void *param, const void *data2);
size_t HashDict(const void *data);

void CreateDestroy();
void InsertSizeRemove();
void FindIsEmpty();
void ForEach();
void Dictionary();


int main()
{
    CreateDestroy();
    InsertSizeRemove();
   FindIsEmpty();
    ForEach();
    Dictionary();
 
    return 0;
}

void CreateDestroy()
{
    size_t capacity = 10;
    hash_t *hash = HashCreate(capacity ,HashFunc, IsMatch, NULL);

    if(!hash)
    {
        printf("\n\n failed create!\n\n");
    }

    HashDestroy(hash);
}
void InsertSizeRemove()
{
    int data[] = {3,5,7,1,74,678};
    size_t capacity = 10;
    hash_t *hash = HashCreate(capacity ,HashFunc, IsMatch, NULL);

    if(0 != HashSize(hash))
    {
        printf("\n\n failed size!\n\n");
    }

    HashInsert(hash, data);
    if( 1 != HashSize(hash))
    {
        printf("\n\n failed insert size!\n\n");
    }

    HashInsert(hash, data+1);
    HashInsert(hash, data+2);

    if( 3 != HashSize(hash))
    {
        printf("\n\n failed insert size!\n\n");
    }

    HashRemove(hash, data);

    if( 2 != HashSize(hash))
    {
        printf("\n\n failed remove!\n\n");
    }
    HashDestroy(hash);
}

void FindIsEmpty()
{

    int data[] = {3,5,7,1,74,678};
    size_t capacity = 10;
    hash_t *hash = HashCreate(capacity ,HashFunc, IsMatch, NULL);

    if(1!= HashIsEmpty(hash))
    {
         printf("\n\n failed is empty!\n\n");
    }
    HashInsert(hash, data+1);
    if(0!= HashIsEmpty(hash))
    {
         printf("\n\n failed is empty when full!\n\n");
    }
    HashInsert(hash, data+2);
    HashInsert(hash, data+3);

    if( NULL != HashFind(hash, &data ))
    {
         printf("\n\n failed find when not present!\n\n");
    }

    if( 7!= *(int*)HashFind(hash, data+2 ))
    {
         printf("\n\n failed find!\n\n");
    }

    HashDestroy(hash);
}

void ForEach()
{

    int data[] = {3,5,7,1,74,678};
    size_t capacity = 10;
    hash_t *hash = HashCreate(capacity ,HashFunc, IsMatch, NULL);

    HashInsert(hash, data+1);
    HashInsert(hash, data+2);
    HashInsert(hash, data+3);

    HashForEach(hash, Visitor, data+4);

    HashDestroy(hash);
}


int Visitor (void *data, void *param)
{
    return *(int*)data+*(int*)param;
}
size_t HashFunc(const void *data)
{
    return (*(size_t*)data%10);
}

int IsMatch(const void *data1, void *param, const void *data2)
{
    (void)param;
    return (!!(*(int*)data1 == *(int*)data2));
}

int DictMatch(const void *data1, void *param, const void *data2)
{
    (void)param;
    return (0 == strcmp((char*)data1, (char*)data2));
}

size_t HashDict(const void *data)
{
    size_t hash = 5381;
    char *str  = (char*)data;

    while(*str)
    {
        hash = ((hash << 5) + hash) + *str;
       ++str;
    }

    return (hash%100);
}

void Dictionary()
{
    FILE *dict = NULL;
    size_t word_count = 0;
    size_t idx = 0;
    char **words = NULL;
	char buffer[100] = {0};
	hash_t *hash = NULL; 

    dict = fopen("/usr/share/dict/american-english","r");

	printf("\nenter word:\n");
    while( EOF != fscanf(dict, "%s", buffer))
    {
		++word_count;
    }

    words = (char**)malloc(word_count * sizeof(char*));
	fseek(dict, 0, 0);

    hash = HashCreate(word_count ,HashDict, DictMatch, NULL);

    for(idx =0 ; idx <word_count; ++idx)
    {
        fscanf(dict, "%s", buffer);
        words[idx] = (char*)malloc(strlen(buffer)+1);
        strcpy(words[idx], buffer);
        HashInsert(hash, words[idx]);
    }

    fclose(dict);
 
 	while ( 0 != strcmp(buffer, "quit"))
    {
        memset(buffer, 0, 100);
        scanf("%s", buffer);

        if(HashFind(hash, buffer))
        {
            printf(GREEN"\n\nSpelling correct!\n\n"WHITE);
        }
        else
        {
            printf(WHITE"\n\nNo such word\n\n"WHITE);
        }
    }    
    
    for(idx =0 ; idx <word_count; ++idx)
    {
        free(words[idx]);
    }

    free(words);
    HashDestroy(hash);
}
