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




#include "bit_array.h"
#include <stdio.h>
static void _Init_LUT_CountBitsOn(size_t* LUT);
static void _Init_LUT_MirrorBits(size_t* LUT);
bit_array_t BitArraySetAllBitsOn ()
{
	return ~0UL ; 
}


bit_array_t BitArraySetAllBitsOff ()
{
	return 0UL; 
}


bit_array_t BitArraySetBitOn(bit_array_t bit_Array, size_t idx)
{
	bit_array_t bitMask = 1UL << (idx - 1);
	bit_Array = bit_Array | bitMask;
	return bit_Array;
}


bit_array_t BitArraySetBitOff(bit_array_t bit_Array, size_t idx)
{
	bit_array_t bitMask = 1UL<<(idx-1);
	bit_Array = bit_Array ^ bitMask;
	return bit_Array;
}


bit_array_t BitArraySetBit(bit_array_t bit_Array, size_t idx, int value)
{
	/*move idx to first bit*/
	bit_array_t mask = bit_Array >> (idx-1);
	/*to cancel other set bits*/
	mask&=1UL;
	mask ^= (unsigned long)value;
	/*back to place*/
	mask<<=(idx-1);
	bit_Array ^= mask; 	
	return bit_Array;

}


int BitArrayIsBitOn(bit_array_t bit_Array, size_t idx)
{
	bit_Array >>= (idx - 1);
	bit_Array &= 1UL;
	return (int)bit_Array;	
}

int BitArrayIsBitOff(bit_array_t bit_Array, size_t idx)
{
	bit_Array >>= (idx-1);
	bit_Array &= 1UL;
	/*to flip results: off is 1*/
	return (int)(bit_Array^1);	
}


bit_array_t BitArrayFlipBit(bit_array_t bit_array, size_t idx)
{
	bit_array_t mask = bit_array >> (idx - 1);
	mask &= 1UL; 
	mask |= 1UL;
	mask <<= (idx-1);
	bit_array ^= mask;
	return bit_array;	
}

bit_array_t BitArrayRotateRight(bit_array_t bit_Array, size_t shift)
{

	size_t mask = 1;
	
	/*set all bits until shift to 1*/
	shift %= sizeof(size_t)*8;
	mask <<= shift;
	--mask;
	mask&=bit_Array;
	
	/*"mirror" set right side to the left*/
	mask <<= sizeof(size_t)*8-shift; 
	bit_Array >>= shift; 			
	bit_Array |= mask;
	return bit_Array;
}                                              


bit_array_t BitArrayRotateLeft(bit_array_t bit_Array, size_t shift)
{
	size_t mask = 1UL;
	
	shift %= sizeof(size_t)*8;
	/*set all bits until shift to 1*/
	mask = (1UL << shift)-1; 
	mask <<= sizeof(size_t)*8-shift;
	/*copy relevant bits to mask*/
	mask &= bit_Array; 
	bit_Array <<= shift; 			
	mask >>= sizeof(size_t)*8 - shift;
	bit_Array|= mask;
	return bit_Array;
	
}


bit_array_t BitArrayMirror(bit_array_t bit_array)
{
	bit_array = ((bit_array & 0x5555555555555555) << 1)  | 
				((bit_array & 0xAAAAAAAAAAAAAAAA) >> 1); 

    bit_array = ((bit_array & 0x3333333333333333) << 2)	 |
			    ((bit_array & 0xCCCCCCCCCCCCCCCC) >> 2);
 
    bit_array = ((bit_array & 0x0F0F0F0F0F0F0F0F) << 4)  | 	
				((bit_array & 0xF0F0F0F0F0F0F0F0) >> 4);
 
    bit_array = ((bit_array & 0x00FF00FF00FF00FF) << 8)  | 
				((bit_array & 0xFF00FF00FF00FF00) >> 8);
 
    bit_array = ((bit_array & 0x0000FFFF0000FFFF) << 16) |
			    ((bit_array & 0xFFFF0000FFFF0000) >> 16);

	bit_array = ((bit_array & 0x00000000FFFFFFFF) << ((sizeof(size_t)*8)-32)) |
			    ((bit_array & 0xFFFFFFFF00000000) >> ((sizeof(size_t)*8)-32));
	return bit_array;
}


unsigned int BitArrayCountBitsOn(bit_array_t bit_array)
{
			/* number of sets in a pair*/ 
	bit_array = ((bit_array & (0xAAAAAAAAAAAAAAAA) ) >>1 ) + 
				( bit_array &  0x5555555555555555); 

	bit_array = ((bit_array & 0xCCCCCCCCCCCCCCCC)    >>2 ) + 
				( bit_array & 0x3333333333333333); 

	bit_array = ((bit_array & 0xF0F0F0F0F0F0F0F0)    >>4 ) +
				 (bit_array & 0x0F0F0F0F0F0F0F0F);
	 
	bit_array = ((bit_array & 0xFF00FF00FF00FF00)    >>8 )+
				 (bit_array & 0x00FF00FF00FF00FF);
	/* 32 bits*/
	bit_array = ((bit_array & 0xFFFF0000FFFF0000)    >>16) + 
   				( bit_array & 0x0000FFFF0000FFFF);
	
	bit_array = ((bit_array & 0xFFFFFFFF00000000)    >>((sizeof(size_t)*8)-32))+ 
				 (bit_array & 0x00000000FFFFFFFF);
	
	return bit_array;
}


unsigned int BitArrayCountBitsOff(bit_array_t bit_array)
{ 
	/*HAMMING WEIGHT*/
	/* number of sets in a pair*/ 
	bit_array = ((bit_array & (0xAAAAAAAAAAAAAAAA) ) >>1 ) + 
				 (  bit_array & 0x5555555555555555); 

	bit_array = ((bit_array & 0xCCCCCCCCCCCCCCCC) >>2 ) + 
				(bit_array & 0x3333333333333333); 

	bit_array = ((bit_array & 0xF0F0F0F0F0F0F0F0) >>4 ) +
				 (bit_array & 0x0F0F0F0F0F0F0F0F);
	 
	bit_array = ((bit_array & 0xFF00FF00FF00FF00) >>8 )+
				 (bit_array & 0x00FF00FF00FF00FF);
	/* 32 bits*/
	bit_array = ((bit_array & 0xFFFF0000FFFF0000) >>16) + 
				(bit_array & 0x0000FFFF0000FFFF);
	
	if (8 == sizeof(size_t))
	{
		bit_array = ((bit_array & 0xFFFFFFFF00000000) >>32) + 
					(bit_array & 0x00000000FFFFFFFF);
	}

	return ((sizeof(size_t)*8)-bit_array);
}

#ifndef NDEBUG 

void PrintBitArray(bit_array_t bit_array)
{
	bit_array_t bitMask= 1;
	unsigned int i =0;
	bitMask<<= (sizeof(size_t)*8-1);
	

	printf("\n\n");

	for (i=0; i<sizeof(size_t)*8; ++i)
	{
		if (bitMask&bit_array)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		bitMask>>=1;
		
	}
	printf("\n\n");
}
#endif


size_t BitArrayLUTCountBitsOn(bit_array_t bit_array)
{
	static size_t LUT[256] = {0};
	unsigned int i=0;
	/*last 8 bits on*/
	size_t mask = 0xFF; 
	size_t bitSum =0;

	if ( 0 == *(LUT+1) )
	{
	   _Init_LUT_CountBitsOn(LUT);
	}
	

	while ( sizeof(size_t) > i )
	{
		bitSum += LUT[mask & bit_array];
		bit_array >>= 8;
		++i;


	}

	return bitSum;

}

bit_array_t BitArrayLUTMirrorBits(bit_array_t bit_array)
{
 	static size_t mirrorLUT[256] ={0};
	unsigned int i=0;
	size_t byteMir =0;
	bit_array_t result=0;
	size_t mask = 0xFF;
	
	if ( 0 == *(mirrorLUT+1))
	{
		_Init_LUT_MirrorBits(mirrorLUT);
	} 	
	
	while (sizeof(size_t) > i)
	{	
		/*byteMir is now mirror of byte*/
		byteMir = mirrorLUT[mask & bit_array]; 
		/*first time move 0, then 8, 16 etc*/
		byteMir >>= 8*i;
		
		/*paste on result*/
		result|=byteMir;		
		
		
		bit_array>>=8;
		++i;
	}
	
	return result;
}

static void _Init_LUT_CountBitsOn(size_t* LUT)
{
	int i=0;
	for (i=0; i<256; ++i)
	{
		*(LUT+i) = BitArrayCountBitsOn(i);
	}

}
static void _Init_LUT_MirrorBits(size_t* LUT)
{
	int i=0;
	for (i=0; i<256; ++i)
	{
		*(LUT+i) =BitArrayMirror(i);
		
	}
}




