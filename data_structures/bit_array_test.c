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



#include <stdio.h>
#include "bit_array.h"


void _PrintBitArray_test(bit_array_t bit_array);
void _BitArraySetAllBitsOn_Test();
void _BitArraySetAllBitsOff_Test();
void _BitArraySetBitOn_Test (bit_array_t bit_Array, size_t idx);
void _BitArraySetBitOff_Test (bit_array_t bit_Array, size_t idx);
void _BitArraySetBit_Test (bit_array_t bit_Array, size_t idx, int value);
void _BitArrayIsBitOn_Test(bit_array_t bit_Array, size_t idx);
void _BitArrayIsBitOff_Test(bit_array_t bit_Array, size_t idx);
void _BitArrayFlipBit_Test(bit_array_t bit_Array, size_t idx);
void _BitArrayRotateRight_Test(bit_array_t bit_Array, size_t shift);
void _BitArrayRotateLeft_Test(bit_array_t bit_Array, size_t shift);
void _BitArrayMirror_Test(bit_array_t bit_array);
void _BitArrayCountBitsOn_Test(bit_array_t bit_array);
void _BitArrayCountBitsOff_Test(bit_array_t bit_array);
void _BitArrayLUTCountBitsOn_Test(bit_array_t bit_array);
void _BitArrayLUTMirrorBits_Test(bit_array_t bit_array);
int main()
{

	/*_BitArraySetAllBitsOn_Test();*/
	/*_PrintBitArray_test(79);*/
	/*_BitArraySetAllBitsOff_Test();*/
	 /*_BitArraySetBitOn_Test(1, 6);*/
	 /*_BitArraySetBitOff_Test(4, 3);*/
	/*_BitArraySetBit_Test (32, 2, 1);*/
	/*_BitArrayIsBitOn_Test(32, 6);*/
	/*_BitArrayIsBitOff_Test(32, 3);*/
	/*_BitArrayFlipBit_Test(32, 7);*/
	/*_BitArrayMirror_Test(1);*/
	/*_BitArrayRotateRight_Test(97, 5);*/
	/*_BitArrayRotateLeft_Test(7, 62);*/
	/* _BitArrayCountBitsOn_Test(17);*/
	/*_BitArrayCountBitsOff_Test(17);*/
	/*BitArrayLUTCountBitsOn_Test(0x14224F01290900);*/
	_BitArrayMirror_Test(0x00000000000001FF);
	_BitArrayLUTMirrorBits_Test(0x00000000000001FF);

	return 0;
}






void _BitArraySetAllBitsOn_Test()
{
	
	
	size_t bitArray= BitArraySetAllBitsOn();
	PrintBitArray(bitArray);


}
void _PrintBitArray_test(bit_array_t bit_array)
{
	
	PrintBitArray(bit_array);



}

void _BitArraySetAllBitsOff_Test()
{
	
	size_t bitArray= BitArraySetAllBitsOff();
	PrintBitArray(bitArray);



}
void _BitArraySetBitOn_Test (bit_array_t bit_Array, size_t idx)
{
	
	printf("%lu", BitArraySetBitOn(bit_Array, idx));


}
void _BitArraySetBitOff_Test (bit_array_t bit_Array, size_t idx)
{
	
	printf("%lu", BitArraySetBitOff(bit_Array, idx));


}
void _BitArraySetBit_Test (bit_array_t bit_Array, size_t idx, int value)
{

	printf("%lu",BitArraySetBit(bit_Array, idx, value));
	

}
void _BitArrayIsBitOn_Test(bit_array_t bit_Array, size_t idx)
{
	int isBitOn = BitArrayIsBitOn(bit_Array,idx );
	printf("%d\n", isBitOn);

}
void _BitArrayIsBitOff_Test(bit_array_t bit_Array, size_t idx)
{

	int isBitOff = BitArrayIsBitOff(bit_Array,idx );
	printf("%d\n", isBitOff);


}
void _BitArrayFlipBit_Test(bit_array_t bit_array, size_t idx)
{
	bit_array = BitArrayFlipBit(bit_array, idx);
	PrintBitArray(bit_array);




}
void _BitArrayRotateRight_Test(bit_array_t bit_Array, size_t shift)
{
	bit_Array=BitArrayRotateRight(bit_Array, shift);
	PrintBitArray(bit_Array);
}
void _BitArrayRotateLeft_Test(bit_array_t bit_Array, size_t shift)
{
	bit_Array=BitArrayRotateLeft(bit_Array, shift);
	PrintBitArray(bit_Array);
}
void _BitArrayMirror_Test(bit_array_t bit_array)
{
	bit_array=BitArrayMirror(bit_array);
	PrintBitArray(bit_array);
}
void _BitArrayCountBitsOn_Test(bit_array_t bit_array)
{
	printf("%d", BitArrayCountBitsOn(bit_array));
}
void _BitArrayCountBitsOff_Test(bit_array_t bit_array)
{
	unsigned int test=BitArrayCountBitsOff(bit_array);
	printf("%u", test);
}
void _BitArrayLUTCountBitsOn_Test(bit_array_t bit_array)
{
	printf("%lu", BitArrayLUTCountBitsOn(bit_array));
		
}
void _BitArrayLUTMirrorBits_Test(bit_array_t bit_array)
{
	bit_array_t test = BitArrayLUTMirrorBits(bit_array);
	PrintBitArray(test);
	
}

