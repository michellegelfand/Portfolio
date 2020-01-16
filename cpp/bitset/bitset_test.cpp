
#include <iostream>

#include "bitset.h"

using namespace ilrd;
using namespace std;

int main()
{
	Bitset<66> b1;
	Bitset<66>b2;
	b2.SetAll(1);
	b1[30] = b2[1];
	cout << b1.ToString() << endl;
	b2[0] = b1[0];
	cout << b2.ToString() << endl;
	b1 |= b2;
	cout << b1.ToString() << endl;
	Bitset<66>b3;
	b3 &= b2;
	cout << b3.ToString() << endl;
	b3.SetBit(1, 1);
	b2.SetBit(1,1);
	b2 &= b3;
	cout << b3.ToString() << endl;
	Bitset<66> test;
	test.SetAll(1);
	cout << (test[1]) << endl << (b1 == b2) << (b1 != b2) << endl;
	cout << !test[1] << endl;

	return 0;
}
