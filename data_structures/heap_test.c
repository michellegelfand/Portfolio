/**********************************************************************;
* Project           : Data Structures
*
* Program name      : heap.c
*
* Author            : Michelle Gelfand
*
* Purpose           : provide heap data structure	
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer 
* 06/08/2019       	  Michelle Gelfand           Doron W.														  
*******************************************************************/

#include <stdio.h>/*printf */

#include "heap.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"
#define KCYN "\033[40;96m"

void CreateDestroy();
void InsertRemovePeek();
void SizeIsEmpty();
void FindRemove();

int Compare(const void *heap_data, const void *user_data, void *param);
int IsMatch(const void *data1, void *param,
							  const void *data2);

int main()
{
     CreateDestroy(); 
      InsertRemovePeek();
   SizeIsEmpty(); 
     FindRemove();
     return 0;
}


void CreateDestroy()
{
    heap_t *heap = HeapCreate(Compare, NULL);
    if (!heap)
    {
        printf(RED"\nfailed create\n"WHITE);
    }
    HeapDestroy(heap);
}

int Compare(const void *heap_data, const void *user_data, void *param)
{
    int result = 0;

    (void)param;
    if(*(int*)heap_data > *(int*)user_data)
    {
        result = 1;
    }
     if(*(int*)heap_data < *(int*)user_data)
    {
        result = -1;
    }
    return result;
}
void InsertRemovePeek()
{
   heap_t *heap = HeapCreate(Compare, NULL);
   int data[] = {1,2,3,4,5, 56, 34, 12, 90, 87, 24};
    HeapPeek(heap);
   HeapPush(heap, data);
   HeapPush(heap, data+1);
   HeapPush(heap, data+2);
   HeapPush(heap, data+3);
   HeapPush(heap, data+4);
   HeapPush(heap, data+5);
   HeapPush(heap, data+6);
   HeapPush(heap, data+7);
   HeapPush(heap, data+8);
   HeapPush(heap, data+9);
   HeapPush(heap, data+10);

   if( 90 != *(int*)HeapPeek(heap))
   {
        printf("\n\nPeek Failed\n\n");
        printf("\n\n%d\n\n", *(int*)HeapPeek(heap));
   }

    printf(BLUE"\n\nPOP STARTS HERE\n\n\n\n"WHITE);


   HeapPop(heap);

   if( 87 != *(int*)HeapPeek(heap))
   {
        printf("\n\n 1 Pop Failed\n\n");
        printf("\n\n%d\n\n", *(int*)HeapPeek(heap));
   }

   HeapPop(heap);


   if( 56 != *(int*)HeapPeek(heap))
   {
        printf("\n\n 2 Pop Failed\n\n");
        printf("\n\n%d\n\n", *(int*)HeapPeek(heap));
   } 

   HeapDestroy(heap);
}
void SizeIsEmpty()
{
    heap_t *heap = HeapCreate(Compare, NULL);
   int data[] = {1,2,3,4,5, 56, 34, 12, 90, 87, 24};

    if(HeapSize(heap) || 1 != HeapIsEmpty(heap))
    {
        printf(RED"\n\nSize Count test failed\n\n");
    }

   HeapPush(heap, data);

   if(1 != HeapSize(heap) || 0 != HeapIsEmpty(heap))
    {
        printf(RED"\n\nSize Count test failed\n\n");
    }

    HeapDestroy(heap);
}

int IsMatch(const void *data1, void *param,
							  const void *data2)
{
    (void)param;
    return (!!(*(int*)data1 == *(int*)data2));
}

void FindRemove()
{
     heap_t *heap = HeapCreate(Compare, NULL);
   int data[] = {1,2,3,4,5, 56, 34, 12, 90, 87, 24};
    int not_in_heap = 9000;

   HeapPush(heap, data);
   HeapPush(heap, data+1);
   HeapPush(heap, data+2);
   HeapPush(heap, data+3);
   HeapPush(heap, data+4);
   HeapPush(heap, data+5);
   HeapPush(heap, data+6);
   HeapPush(heap, data+7);
   HeapPush(heap, data+8);
   HeapPush(heap, data+9);
   HeapPush(heap, data+10);

   if( NULL != HeapRemove(heap, &not_in_heap, IsMatch, NULL))
   {
        printf(RED"\nRemove failed for not found\n\n"WHITE);  
   } 

    if( 87!= *(int*)HeapRemove(heap, data+9, IsMatch, NULL))
   {
        printf(RED"\nRemove failed for found\n\n"WHITE);   
   }

     if( 5!= *(int*)HeapRemove(heap, data+4, IsMatch, NULL))
   {
        printf(RED"\nRemove failed for found\n\n"WHITE);   
   }

  HeapDestroy(heap);
}