#include <unistd.h>/*ssize_t*/
#include <stdlib.h>/*calloc*/
#include <stdio.h>/*print */
#include <time.h>/*time*/

#include "knight.h"

int main()
{
    size_t start_pos = 0;
    size_t **moves = (size_t**)calloc(64 , 8);
    size_t **returned = NULL;
    int i =0;
    srand(time(NULL));
    start_pos = rand()%64; 
    returned = KnightsTour(start_pos, moves);

    printf("\nresults:\n");

    for(i =0; i<64; ++i)
    {
        printf("%lu ",  *((size_t*)returned+(size_t)i));
    }

    free(moves);

    return 0;
}

