/*******************************************************************************
    @File:       searches.c                                            
    @Created:    07.08.19                                                   
    @Version:    1.0	                                                      
    @Author:     Doron Weitzman                                             
    @Reviewer:   Michelle Gelfand				                                              
     status  :													
*******************************************************************************/

#include <assert.h> /* assert  */
#include <unistd.h> /* ssize_t */
#include <math.h>   /* sqrt    */

#include "searches.h"

#define BASE_AT_IDX(idx) (void*)( (char*)base + (idx * element_size))

/*___________________________________________________________________________ */

void *BinarySearch(const void *base, size_t size, size_t element_size, 
                search_cmp_t Compare, void *param, const void *required_data)
{
	ssize_t left = 0;
	size_t middle_idx = 0;
	ssize_t right = 0;
	void *middle_elem = NULL; 
	int cmp_res = 0;

	assert(base);
	assert(Compare);

	right = size - 1;

	while(left <= right)
	{
		middle_idx = ((left + right) / 2);
		middle_elem = BASE_AT_IDX(middle_idx);
	
		cmp_res = Compare(middle_elem, required_data, param);

		if(0 == cmp_res)
		{
			return middle_elem;
		}
		else if(0 < cmp_res)
		{
			right = middle_idx - 1;
		}
		else
		{
			left = middle_idx + 1;
		}
	}

	return NULL;
}

/*_____________________________________	______________________________________ */

void *BinarySearchRecursively(const void *base, size_t size, size_t element_size, 
                    search_cmp_t Compare, void *param, const void *required_data)
{
	size_t left_sub_arr_size = 0;
	size_t middle_idx = 0;
	size_t right_sub_arr_size = 0;
	void *middle_elem = NULL; 
	char *right_sub_arr = NULL;
	int cmp_res = 0;

	assert(base);
	assert(Compare);

	if(!size)
	{
		return NULL;
	}

	middle_idx  = size / 2;
	middle_elem = BASE_AT_IDX(middle_idx);

	cmp_res = Compare(middle_elem, required_data, param);

	if(0 == cmp_res)
	{
		return middle_elem;
	}
	else if(0 < cmp_res)
	{
		left_sub_arr_size = size / 2;

		return BinarySearchRecursively(base, left_sub_arr_size, element_size,
									   Compare, param, required_data);
	}
	else
	{
		right_sub_arr_size = size - ((size / 2) + 1);

		right_sub_arr = BASE_AT_IDX( ((size / 2) + 1) );

		return BinarySearchRecursively(right_sub_arr, right_sub_arr_size,
								   element_size, Compare, param, required_data);
	}
}

/*___________________________________________________________________________ */

void *JumpSearch(const void *base, size_t size, size_t element_size, 
                 search_cmp_t Compare, void *param, const void *required_data)
{
	size_t i = 0;
	size_t start_idx = 0;
	size_t end_idx = 0;
	size_t sqrt_size = 0;

	assert(base);
	assert(Compare);

	sqrt_size = sqrt(size);

	end_idx = sqrt_size;

	while( (0 >= Compare(BASE_AT_IDX(end_idx), required_data, param)) &&
		   (end_idx < size) )
	{
		start_idx = end_idx;

		end_idx += sqrt_size;

		if(end_idx > (size-1))
		{
			end_idx = size;
			break;
		}
	}

	for(i = start_idx; i < end_idx; ++i)
	{
		if(0 == Compare(BASE_AT_IDX(i), required_data,param))
		{
			return BASE_AT_IDX(i);
		}
	}

	return NULL;
}
