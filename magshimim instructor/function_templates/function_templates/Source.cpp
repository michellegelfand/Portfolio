#include "functions.h"
#include <iostream>

class testObj
{
public:
	testObj(int a) :a(a) {}
	bool operator>(const testObj& other) {
		return (a > other.a);
	}
	bool operator==(const testObj& other)
	{
		return (a == other.a);
	}
	friend std::ostream& operator<<(std::ostream& os, testObj a)
	{
		os << a.a;
		return os;
	}
	int a; //field is public for convenience sake of testing
};

int main() {

	//check compare
	std::cout << "correct print is 1 -1 0" << std::endl;
	std::cout << compare<double>(1.0, 2.5) << std::endl;
	std::cout << compare<double>(4.5, 2.4) << std::endl;
	std::cout << compare<double>(4.4, 4.4) << std::endl;


	//check bubbleSort
	std::cout << "correct print is sorted array" << std::endl;

	const int arr_size = 5;
	double doubleArr[arr_size] = { 1000.0, 2.0, 3.4, 17.0, 50.0 };
	bubbleSort<double>(doubleArr, arr_size);
	for (int i = 0; i < arr_size; i++) {
		std::cout << doubleArr[i] << " ";
	}
	std::cout << std::endl;

	//check printArray
	std::cout << "correct print is sorted array" << std::endl;
	printArray<double>(doubleArr, arr_size);
	std::cout << std::endl;

	char testChar[6] = { 'n', 'a', 'c', 'c', 'h', 'z' };
	bubbleSort<char>(testChar, 6);
	printArray(testChar, 6);
	
	testObj arr[4] = { testObj(4),testObj(1),testObj(17),testObj(-2) };
	bubbleSort<testObj>(arr, 4);
	printArray(arr, 4);
	system("pause");
	return 1;
}