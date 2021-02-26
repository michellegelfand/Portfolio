/**********************************************************************;
* Project           : Data Structures
*
* Program name      : bit_array.c
*
* Author            : Michelle Gelfand
*
* Date created      : 02.06.19
*
* Purpose           : This program provides the user with operations to 
*					  effeciently append bit arrays 
*	
* Header Version    : 1			  
*
* Review Status		: Approved	
*
* Date Approved        Author			          Reviewer 
*  4/6/19          	   Michelle Gelfand         Olga Kondrashova     *														  
*												       __
*													o-''|\_____/)
*											(woof)	 \_/|_)     )
*														\  __  /
*														(_/ (_/
**********************************************************************/
#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stddef.h>
typedef size_t bit_array_t;


#ifndef NDEBUG /*if in debug mode*/
 	#include <stdio.h>
	/*prints out bit array, ONLY DEBUG MODE*/
	void PrintBitArray(bit_array_t bit_array);
#else
	/*replace func decleration with white space to avoid warnings*/
	#define PrintBitArray(bit_array)

#endif /*NDEBUG*/


/*returns all bits on*/
bit_array_t BitArraySetAllBitsOn ();

/*returns all bits on*/
bit_array_t BitArraySetAllBitsOff ();

/*set  bit at index to 1. idx values: 1-64*/
bit_array_t BitArraySetBitOn(bit_array_t bit_Array, size_t idx);

/*set  bit at index to 0. idx values: 1-64*/
bit_array_t BitArraySetBitOff(bit_array_t bit_Array, size_t idx);

/*set bit at index to selected value. idx values: 1-64*/
bit_array_t BitArraySetBit(bit_array_t bit_Array, size_t idx, int value);

/*checks if bit at index is 1. idx values: 1-64*/
int BitArrayIsBitOn(bit_array_t bit_Array, size_t idx);

/*checks if bit at index is 0. idx values: 1-64*/
int BitArrayIsBitOff(bit_array_t bit_Array, size_t idx);

/*flip bit to opposite value. idx values: 1-64*/
bit_array_t BitArrayFlipBit(bit_array_t bit_Array, size_t idx);

/*rotate bits right n rotations*/
bit_array_t BitArrayRotateRight(bit_array_t bit_Array, size_t shift);

/*rotate bits left n rotations*/
bit_array_t BitArrayRotateLeft(bit_array_t bit_Array, size_t shift);

/*mirror bits left-side right*/
bit_array_t BitArrayMirror(bit_array_t bit_array);

/*count set (1) bits*/
unsigned int BitArrayCountBitsOn(bit_array_t bit_array);

/*count unset (0) bits*/
unsigned int BitArrayCountBitsOff(bit_array_t bit_array);

/*count set (1) bits*/
size_t BitArrayLUTCountBitsOn(size_t bit_array);
/*mirror bits left-side right*/
bit_array_t BitArrayLUTMirrorBits(bit_array_t bit_array);

#endif /*__BITARRAY_H__*/




