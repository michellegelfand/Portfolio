/**********************************************************************;
* Project           : Data Structures
*
* Program name      : knight.c
*
* Author            : Michelle Gelfand
*
* Date created      : 04.06.19			  
*
* Date Approved       Author	 	             Reviewer 
* 13/09     	  Michelle Gelfand               Saae Y.	
							  
**********************************************************************/
#include "bit_array.h"
#include "test_tools.h"

/*place: enter starting tile: 0-63
  moves: pointer to array of size_t 
  returns moves in order to completion (or partial moves if failed)*/
size_t **KnightsTour(long place, size_t **moves); 
