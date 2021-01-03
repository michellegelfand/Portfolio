#pragma once

#include <iostream>

/*
* returns -1 if param1 > param2
* 0 if they are equal 
* and 1 if param2 > param1
* 
* if T is an object it must overload the > and == operators
*/
template<typename T>
int compare(T param1, T param2)
{
	if (param1 > param2)
	{
		return -1;
	}
	else if (param1 == param2)
	{
		return 0;
	}
	else
	{
		return  1;
	}
}


template <typename T>
void bubbleSort(T* list, int size)
{
	int runCount = 0;
	bool swapped_this_run = false;
	do
	{
		swapped_this_run = false;
		for (int i = 1; i < size - runCount; i++)
		{
			if (list[i - 1] > list[i])
			{
				T temp = list[i - 1];
				list[i - 1] = list[i];
				list[i] = temp;
				swapped_this_run = true;
			}
		}
		runCount++;
	} while (swapped_this_run);
}

/*
* prints array elements on seperate lines
* requires T overloads << operator
*/
template<typename T>
void printArray(T* list, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << list[i] << std::endl;
	}
}