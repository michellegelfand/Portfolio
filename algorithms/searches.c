/******************************************************************************;
* Project           : Data Structures
*
* Program name      : searches.c
*
* Author            : Michelle Gelfand
*
*
* Purpose           : This program provides the user
					  with 5 sorting algorithms
*
* Version           : 1.0
*
* Review Status		: Approved
*
* Date Approved       Author	 	             Reviewer
* 10/08/2019       	  Michelle Gelfand           Inbar D.
*******************************************************************************/

#include <assert.h>/*assert */
#include <stdlib.h>/*size_t */
#include <unistd.h>/*ssize_t */
#include <math.h> /*sqrt */

#include "searches.h"




void *BinarySearchRecursivelyHelper(const void *base, 
                                    size_t lower_bound,
                                    size_t upper_bound,
                                    size_t element_size, 
                                    search_cmp_t compare,
                                    void *param,
                                    const void *required_data);





void *BinarySearch(const void *base, 
                    size_t size,
                    size_t element_size, 
                    search_cmp_t compare,
                    void *param,
                    const void *required_data)
{
    ssize_t upper_bound = 0; /*ssize_t if middle is 0, so minus 1 would give large 
                               num in size_t, -1 wont enter while loop  */
    ssize_t lower_bound = 0;
    size_t middle_element = 0;

    assert(base);
    assert(size);
    assert(element_size);
    assert(compare);

    upper_bound = size-1;

    while(lower_bound <= upper_bound)
    {
        middle_element = lower_bound+((upper_bound - lower_bound)/2);

        /*if middle bigger than requested element */
        if(0 < compare((void*)((char*)base+ (middle_element*element_size)),
                                         required_data, param))
        {
            upper_bound = middle_element -1;
        }
        /*if middle smaller than requested element */
        else if (0 > compare((void*)((char*)base+ 
                 (middle_element*element_size)), required_data, param))
        {
            lower_bound = middle_element +1;
        }
        else
        {
            return ((void*)((char*)base+ (char)(middle_element*element_size)));
        }
    }

    /*if not found */
    return NULL;
}

void *BinarySearchRecursively(const void *base, 
                              size_t size,
                              size_t element_size, 
                              search_cmp_t compare,
                              void *param,
                              const void *required_data)
{
    assert(base);
    assert(size);
    assert(element_size);
    assert(compare);

   return  BinarySearchRecursivelyHelper(base, 0,size-1, element_size, compare,
              param, required_data);
}





void *BinarySearchRecursivelyHelper(const void *base, 
                                    size_t lower_bound,
                                    size_t upper_bound,
                                    size_t element_size, 
                                    search_cmp_t compare,
                                    void *param,
                                    const void *required_data)
{
    size_t middle_element = lower_bound+((upper_bound - lower_bound)/2);

    if(lower_bound > upper_bound)
    {
        return NULL;
    }
    else
    {

        /*if middle bigger than requested element */
        if(0 < compare((void*)((char*)base+ (middle_element*element_size)),
                                            required_data, param))
        {
            return  BinarySearchRecursivelyHelper(base, lower_bound, 
            middle_element-1, element_size, compare, param, required_data);
        }
        /*if middle smaller than requested element */
        else if (0 > compare((void*)((char*)base+ 
                    (middle_element*element_size)), required_data, param))
        {
            return  BinarySearchRecursivelyHelper(base, middle_element+1,
            upper_bound, element_size, compare, param, required_data);
        }
     
          return ((void*)((char*)base+ (char)(middle_element*element_size)));
    }

}

void *JumpSearch(const void *base, size_t size, size_t element_size, 
                    search_cmp_t compare, void *param, const void *required_data)
{

    size_t jump_factor = 0;
    size_t curr_idx = 0;
    size_t prev_idx = 0;
    void *current = NULL;
    void *previous = NULL;

    assert(base);
    assert(size);
    assert(element_size);
    assert(compare);

    jump_factor = (size_t)sqrt(size);
    current = (void*)base;

    while(size > curr_idx)
    {
        current = (void*)((char*)base + (char)(curr_idx*element_size));
        /*if current bigger than requested data */
       if( 0 < compare(current, required_data, param))
       {
           break;
       }
        prev_idx = curr_idx;
       curr_idx += jump_factor;
    }

    /*if didnt find bigger element */
    if(! (size > curr_idx))
    {
        return NULL;
    }
    else
    {
        
        previous = (void*)((char*)base + (char)(element_size * prev_idx));
        
        return BinarySearchRecursively(previous, curr_idx - prev_idx, element_size,
        compare, param, required_data);
    }
    

}
