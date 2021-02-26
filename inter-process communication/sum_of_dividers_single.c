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

#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/

size_t SumOfDividers(size_t num)
{
    size_t i = 0;
    size_t sum = 0;

    for (i = 1; i <= num; ++i)
    {
        if(!(num % i))
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    size_t sum = 0;
    size_t num = 113000800;
    sum = SumOfDividers(num);
    printf("holy molly %ld\n", sum);
    return 0;
}