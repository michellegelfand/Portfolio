#include <stdio.h>/*printf */

#include "avl.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0m"
#define BLUE "\033[1;34m"
#define YELLOW "\033[0;33m"

void CreateDestroyTest();
void InsertTest();
void IsEmptyTest();
void ForeachTest();
void CountTest();
void FindTest();
void HeightTest();
void RemoveTest();

int Compare(const void *data1, const void *data2, void *param);
int AddParam(void *data, void *param);

int main()
{
    CreateDestroyTest();
     
    InsertTest(); 
     
    IsEmptyTest();
     
    ForeachTest();
     
    CountTest();
    
    FindTest(); 
     
    HeightTest();
    
    RemoveTest();   
  


    return 0;
}

void CreateDestroyTest()
{
    avl_t *tree = AvlCreate(Compare, NULL);
    avl_status_t status = AVL_SUCCESS;

    int data[] = {1,2,3,4,5};

    status |= AvlInsert(tree, &data);
    status |= AvlInsert(tree, &data[1]);

    if( NULL ==  tree)
    {
        printf(RED"\nfailed create\n"WHITE);
    }

    AvlDestroy(tree);

    printf(BLUE"\nCombine destroy test with valgrind\n"WHITE);
}

int Compare(const void *data1, const void *data2, void *param)
{
    int result = 0;
    if (*(int*) data1 > *(int*)data2)
    {
        result = 1;
    }
    else if (*(int*)data1<*(int*)data2)
    {
        result = -1;
    }

    (void)param;

    return result;
}

void InsertTest()
{
    avl_t *tree = AvlCreate(Compare, NULL);
    avl_status_t status = AVL_SUCCESS;

    int data1 = 18;
    int data2 = 14;
    int data3 = 16;
    int data4 = 20;
    int data5 = 19;
    int data13 = 13;
    int data12 = 21;
     int data22 = 22;
    int data23 = 23;

    status |= AvlInsert(tree, &data1);
    status |= AvlInsert(tree, &data2);
    status |= AvlInsert(tree, &data13);
    status |= AvlInsert(tree, &data3);
    status |= AvlInsert(tree, &data4);
    status |= AvlInsert(tree, &data5);
    status |= AvlInsert(tree, &data12);
    status |= AvlInsert(tree, &data22);
    status |= AvlInsert(tree, &data23);

    AvlDestroy(tree);
}
void IsEmptyTest()
{
    avl_t *tree = AvlCreate(Compare, NULL);
    avl_status_t status = AVL_SUCCESS;

    int data1 = 18;
    int data2 = 14;
    int data3 = 16;
    int data4 = 20;
    int data5 = 19;
    int data6 = 18;

    if( 0 != AvlIsEmpty(tree))
    {
      printf(RED"\nfailed IsEmpty empty\n"WHITE);  
    }

    status |= AvlInsert(tree, &data1);
    status |= AvlInsert(tree, &data2);
    status |= AvlInsert(tree, &data3);
    status |= AvlInsert(tree, &data4);
    status |= AvlInsert(tree, &data5);
    status |= AvlInsert(tree, &data6);

    if( 0 == AvlIsEmpty(tree))
    {
      printf(RED"\nfailed IsEmpty full\n"WHITE);  
    }

    AvlDestroy(tree);
}

void ForeachTest()
{
    avl_t *tree = AvlCreate(Compare, NULL);
    avl_status_t status = AVL_SUCCESS;

    int data1 = 18;
    int data2 = 14;
    int data3 = 16;
    int data4 = 20;
    int data5 = 19;
    int data6 = 18;
    int data444 = 444;
    int data666 = 666;
    int data888 = 888;

    int param = 100;

    status |= AvlInsert(tree, &data1);
    status |= AvlInsert(tree, &data2);
    status |= AvlInsert(tree, &data3);
    status |= AvlInsert(tree, &data4);
    status |= AvlInsert(tree, &data5);
    status |= AvlInsert(tree, &data6);

    if ( 0!= AvlForEach(tree, AddParam, &param ))
    {
        printf(RED"\n for each failed 1"WHITE);
    }

    status |= AvlInsert(tree, &data444);
    status |= AvlInsert(tree, &data666);
    status |= AvlInsert(tree, &data888);

    if ( 0 == AvlForEach(tree, AddParam, &param ))
    {
        printf(RED"\n for each failed 2"WHITE);
    }

     AvlDestroy(tree);
}

/*visitor func */
int AddParam(void *data, void *param)
{
    if ( 444 == *(int*)data )
    {
        /*fail condition */
        return 1;
    }

    *(int*)data += *(int*)param;

    return 0;
}
void CountTest()
{

    avl_t *tree = AvlCreate(Compare, NULL);
    avl_status_t status = AVL_SUCCESS;

    int data1 = 18;
    int data2 = 14;
    int data3 = 16;
    int data4 = 20;
    int data5 = 19;
    int data6 = 18;

    if(AvlCount(tree))
    {
       printf(RED"\n count failed for empty "WHITE); 
    }

    status |= AvlInsert(tree, &data1);
    status |= AvlInsert(tree, &data2);
    status |= AvlInsert(tree, &data3);
    status |= AvlInsert(tree, &data4);
    status |= AvlInsert(tree, &data5);
    status |= AvlInsert(tree, &data6);

    if( 5ul != AvlCount(tree))
    {
       printf(RED"\n count failed for full "WHITE); 
       printf("\n%lu\n", AvlCount(tree));
    }

    AvlDestroy(tree);
}

void FindTest()
{
    avl_t *tree = AvlCreate(Compare, NULL);
    avl_status_t status = AVL_SUCCESS;

    int data1 = 18;
    int data2 = 14;
    int data3 = 16;
    int data4 = 20;
    int data5 = 19;
    int data6 = 18;
    int data778 = 778;

    status |= AvlInsert(tree, &data1);
    status |= AvlInsert(tree, &data2);
    status |= AvlInsert(tree, &data3);
    status |= AvlInsert(tree, &data4);
    status |= AvlInsert(tree, &data5);
    status |= AvlInsert(tree, &data6);
    /* status |= AvlInsert(tree, &data778);*/

    printf("\n\n\n\n\n$$$$$$$$$$$$$$$found : %d\n\n",*(int*)AvlFind(tree, &data3) );
     printf("\n\n\n\n\n$$$$$$$$$$$$$$$found : %p\n\n",AvlFind(tree, &data778) );


    if ( 16!= *(int*)AvlFind(tree, &data3))
    {
        printf(RED"\n find failed for found"WHITE);
        printf("\n\n\n\n%d\n\n ", *(int*)AvlFind(tree, &data1)); 
    }

    if ( NULL!= AvlFind(tree, &data778))
    {
        printf(RED"\n find failed for NOT found"WHITE); 
    }

    AvlDestroy(tree);
}
void HeightTest()
{
    avl_t *tree = AvlCreate(Compare, NULL);  

    int data1 = 18;
    int data2 = 14;
    int data3 = 16;
    int data4 = 20;
    int data5 = 19;
    int data6 = 18;
    int data778 = 778;
    int data779 = 779;

    if( -1 != AvlHeight(tree))
    {
        printf(RED"\n height failed for empty tree"WHITE); 
    }

    AvlInsert(tree, &data1);
    AvlInsert(tree, &data2);
    AvlInsert(tree, &data3);
    AvlInsert(tree, &data4);
    AvlInsert(tree, &data5);
    AvlInsert(tree, &data6);
    AvlInsert(tree, &data778);
    AvlInsert(tree, &data779);

    if( 3 != AvlHeight(tree))
    {
        printf(RED"\n height failed for full tree"WHITE); 
    }
     AvlDestroy(tree);
}

void RemoveTest()
{
     avl_t *tree = AvlCreate(Compare, NULL); 

    int data1 = 18;
    int data2 = 14;
    int data3 = 16;
    int data4 = 20;
    int data5 = 19;
    int data80 = 80;

    AvlInsert(tree, &data1);
    AvlInsert(tree, &data2);
    AvlInsert(tree, &data3);
    AvlInsert(tree, &data4);
    AvlInsert(tree, &data5);
    AvlInsert(tree, &data80);

    AvlRemove(tree, &data3);
    AvlRemove(tree, &data4);

    AvlDestroy(tree);
}
