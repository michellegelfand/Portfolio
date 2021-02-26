/**********************************************************************;
* Project           : Data Structures
*
* Program name      : 100kthreads.c TODO name! 
*
* Author            : Michelle Gelfand		  
*
* Author	 	                 Reviewer 
* Michelle Gelfand               Evegeni S.					  
**********************************************************************/

#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/
#include <omp.h> /* Open MP */

size_t SumOfDividers(size_t num)
{
    size_t i = 0;
    size_t sum = num;

    int thread_num; /* thread num */
    int thread_count; /* threads count change names */
    size_t range;
    size_t end;

#pragma omp parallel num_threads(4)  shared(sum, num)\
                                     private(i, thread_num, thread_count, range, end)
    { /*use block of code for parallel section*/
        thread_num = omp_get_thread_num();
        thread_count = omp_get_num_threads();
        range = num / 2 / thread_count;
        i = 1 + (thread_num * range);
        end = i + range;

        for (; i <= end; ++i)
        {
            if(!(num % i))
            {
#pragma omp critical
                sum += i;
            }
        }

#pragma omp barrier
    }
    
    return sum;
}

int main()
{
    size_t sum = 0;
    size_t num = 12000000000;
    sum = SumOfDividers(num);
    printf("holy molly %ld\n", sum);
    return 0;
}
