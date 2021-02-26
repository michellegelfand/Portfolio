/**
 * @File:       searches.h 
 * @Created:    07.08.19 
 * @Version:    1.0
 * 
 */

#ifndef __SEARCHES_H__
#define __SEARCHES_H__

#include <stddef.h> /* size_t */

typedef int (*search_cmp_t)(const void *data1, const void *data2, void *param );

/******************************************************************************/

void *BinarySearch(const void *base, size_t size, size_t element_size, 
                search_cmp_t compare, void *param, const void *required_data);

/******************************************************************************/

void *BinarySearchRecursively(const void *base, size_t size, size_t element_size, 
                    search_cmp_t compare, void *param, const void *required_data);

/******************************************************************************/

void *JumpSearch(const void *base, size_t size, size_t element_size, 
                    search_cmp_t compare, void *param, const void *required_data);

#endif /* __SEARCHES_H__*/
