#include <iostream>

#include "Fraction.h"

using namespace std;

void fraction_test();
void printResult(const Fraction& res);

int main()
{
	bool exception_thrown = 0;
	int fraction1vals[2];
	int fraction2vals[2];

	char calc_action;

	try
	{
		while (!exception_thrown)
		{
			cout << "Please enter fraction number 1 -> A/B\nA: ";
			cin >> fraction1vals[0];
			cout << "\nB: ";
			cin >> fraction1vals[1];

			Fraction f1(fraction1vals[0], fraction1vals[1]);

			cout << "your fraction is " << f1.getNumerator() << "\\" << f1.getDenominator() << "\n";
			cout << "---------------------------------------------\n";
			cout << "enter calc action: \n";
			cin >> calc_action;

			cout << "---------------------------------------------\n";
			cout << "Please enter fraction number 2 -> A/B\nA: ";
			cin >> fraction2vals[0];
			cout << "\nB: ";
			cin >> fraction2vals[1];

			Fraction f2(fraction2vals[0], fraction2vals[1]);
			cout << "your fraction is " << f2.getNumerator() << "\\" << f2.getDenominator() << "\n";
			cout << "---------------------------------------------\n";

			cout << "\nCalculate " << f1.getNumerator()<<"\\"<<f1.getDenominator()<<calc_action<< f2.getNumerator() << "\\" << f2.getDenominator() << endl;
			Fraction* res;

			switch (calc_action)
			{
			case '+':
				res = &Fraction(f1 + f2);
				printResult(*res);
				break;
			case '-':
				res = &Fraction(f1 - f2);
				printResult(*res);
				break;
			case '*':
				res = &Fraction(f1 * f2);
				printResult(*res);
				break;
			case '/':
				res = &Fraction(f1 / f2);
				printResult(*res);
				break;
			default:
				cout << "invalid calc action\n";
				throw FailedOperationException();
				break;
			}


		}
	}
	catch (const std::exception &e)
	{
		exception_thrown = 1;
		cout << e.what();
	}
	return 0;
} 

void printResult(const Fraction& res)
{
	cout << "Result: " << res.getNumerator() << "\\" << res.getDenominator() << " or " << (float)res.getNumerator() / (float)res.getDenominator() << endl;
}

void fraction_test()
{
	Fraction a(2, 3);
	Fraction b = !a;
	cout << b.getNumerator() << " \\ " << b.getDenominator();

	Fraction c = a + b;
	cout << "\n" << c.getNumerator() << " \\ " << c.getDenominator();
	Fraction d = c - b;
	cout << "\n" << d.getNumerator() << " \\ " << d.getDenominator();

	Fraction e = a * b;
	cout << "\n" << e.getNumerator() << " \\ " << e.getDenominator();
	Fraction f = a / b;
	cout << "\n" << f.getNumerator() << " \\ " << f.getDenominator();
}