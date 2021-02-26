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

#include <stdio.h>/*print */
#include <stdlib.h>/*size_t */
#include <unistd.h>/*ssize_t*/
#include <time.h>/*time*/

#include "knight.h"

static size_t **Solve(bit_array_t board, long place, 
    bit_array_t *possible_moves, size_t **solutions, size_t loc_arr, 
        long count, clock_t time_passed);
static void PrintMove(bit_array_t board, size_t place);
static void InitPossibleMovesTable( bit_array_t *possible_moves);
static bit_array_t GetPossibleMoves( bit_array_t location);
static int IsInBoardRange(ssize_t xfield, ssize_t yfield);
static void SetPossibleMoves(bit_array_t *possible_moves,
     bit_array_t location, ssize_t xfield, ssize_t yfield);
static ssize_t GetNextMove(bit_array_t board, long place, 
    bit_array_t *possible_moves);
static size_t CountValidNeighbours(bit_array_t board,
     bit_array_t possible_moves);

#define MAX_TIME 300
 
#define WHITE_BG(str) printf("\x1b[30;107m")
#define BLACK_BG(str) printf("\x1b[97;40m")

size_t **KnightsTour(long place, size_t **moves)
{
    bit_array_t board = 0;
    bit_array_t possible_moves[64] = { 0 };

    clock_t time_passed = ((double)(clock()))/CLOCKS_PER_SEC;
    InitPossibleMovesTable(possible_moves);

     return Solve(board, place, possible_moves, 
            moves, 0, 0, time_passed);
}

void InitPossibleMovesTable( bit_array_t *possible_moves)
{
    int i=0;

    for(i =0; i < 64; ++i)
    {
        possible_moves[i] = GetPossibleMoves(i);
    }
}

 static bit_array_t GetPossibleMoves( bit_array_t location)
 {
    bit_array_t possible_moves = {0};

    ssize_t xfield[8] = {  2, 1, -1, -2, -2, -1,  1,  2 }; 
    ssize_t yfield[8] = {  1, 2,  2,  1, -1, -2, -2, -1 }; 
    long i =0;
 
    for(i=0; i < 8; ++i)
    {
        SetPossibleMoves(&possible_moves, location, xfield[i], yfield[i]);
    }

    return possible_moves;
 }

static void SetPossibleMoves(bit_array_t *possible_moves,
      bit_array_t location, ssize_t xfield, ssize_t yfield)
{
    yfield = location/8 +yfield;
    xfield = location%8 +xfield;

    if(IsInBoardRange(xfield, yfield))
    {
        *possible_moves |= 
            BitArraySetBitOn(*possible_moves, (8*yfield +xfield)+1);
    }
}

static int IsInBoardRange(ssize_t xfield, ssize_t yfield)
{
    return (!!((0<=xfield  && 8 > xfield) && (0<=yfield  && 8 > yfield)));
}

static size_t **Solve(bit_array_t board, long place,
     bit_array_t *possible_moves, size_t **solutions, size_t loc_arr, 
        long count, clock_t time_passed)
{ 
    size_t prev = 0;

    time_passed +=((double)(clock()))/CLOCKS_PER_SEC;

    if( !BitArrayCountBitsOff(board) || 63 < count  || MAX_TIME < time_passed )
    {
        return solutions;
    }
    else 
    {
        prev = place;

        printf("\033c");
        *((size_t*)solutions+(size_t)loc_arr) = place;
        printf(BLUE"\n\nKnight to %ld\n\n"WHITE, place); 
        printf("\nMove: %ld\n", count);
        
        PrintMove(board, place); 
        getchar(); 

        board = BitArraySetBitOn(board, 64 - place );
        place = GetNextMove(board, place, possible_moves);
        ++count;

        if( -1 != place )
        {
           return Solve(board, place, possible_moves, solutions, 
                ++loc_arr, count, time_passed);
        }
        else
        {
             BitArraySetBitOff(board, 64-place); 
            return Solve(board, prev, possible_moves, solutions, loc_arr, 
                    --count, time_passed);  
        } 
    } 
    return solutions;
}


static ssize_t GetNextMove(bit_array_t board, long place,
     bit_array_t *possible_moves)
{
    size_t i =0;
    size_t option_with_min_moves = 0;
    size_t moves_count_current_tile = 0;
    ssize_t has_moves = -1;
    ssize_t min_moves_count = 0;

    for(i = 0; i < 64; ++i)
    {
        if( BitArrayIsBitOn(possible_moves[place], i+1) && 
                BitArrayIsBitOff(board, 64-i) )
        {
            if( -1 == has_moves)
            {
               option_with_min_moves = i; 
            }

            has_moves = 1;
            moves_count_current_tile = 
                 CountValidNeighbours(board, possible_moves[i]);
            min_moves_count = 
             CountValidNeighbours(board, possible_moves[option_with_min_moves]);

            if( min_moves_count > (ssize_t)moves_count_current_tile)
            {
                option_with_min_moves = i;
            }
        }
    }

    if( -1 == has_moves)
    {
        return -1;
    }
    
    return option_with_min_moves;
}

static size_t CountValidNeighbours(bit_array_t board, bit_array_t possible_moves)
{
    int i = 0;
    size_t valid_neighbour_count = 0;
    for(i=0; i<64; ++i)
    {
        if(BitArrayIsBitOff(board, 64 - i) &&
             BitArrayIsBitOn(possible_moves, i+1))
        {
            ++valid_neighbour_count;
        }
    }
    return valid_neighbour_count;
}

/***************** P  R  I  N  T ******************************************/
static void PrintMove(bit_array_t board, size_t place)
{
    size_t i = 0;
    bit_array_t mask= 1;
	size_t j =0;
    int black_square = 0;
	mask<<= (sizeof(size_t)*8-1);

    PrintBitArray(board);

    for ( i=0; i<8; ++i)
    {
        for(j =0; j<8; ++j)
        {
            if(black_square)
            {
                BLACK_BG();
            }
            else
            {
                WHITE_BG();
            }
                
            if( place == 8*i +j)
            {
                printf("\033[35m""\xE2\x99\x9E " WHITE);
            }
            else
            {
                if(mask & board)
                {
                    printf(RED"\xE2\x9C\x97 "); 
                }
                else
                {
                    printf("  ");
                }
            }
            
            mask >>=1; 
            black_square^=1;
        }

        printf("\n");
        black_square^=1;
    }
}
