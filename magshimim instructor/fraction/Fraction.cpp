#include "Fraction.h"


Fraction Fraction::operator+(const Fraction& other)
{
	Fraction result(*this);
	int new_denominator = result._denominator * other.getDenominator();
	int new_numerator = getNumerator() * other.getDenominator() + other.getNumerator() * getDenominator();
	result.setNumerator(new_numerator);
	result.setDenominator(new_denominator);

	return result;
}
Fraction Fraction::operator-(const Fraction& other)
{
	Fraction result(*this);
	int new_denominator = result._denominator * other.getDenominator();
	int new_numerator = getNumerator() * other.getDenominator() - other.getNumerator() * getDenominator();
	result.setNumerator(new_numerator);
	result.setDenominator(new_denominator);

	return result;
}
Fraction Fraction::operator*(const Fraction& other)
{
	return Fraction(getNumerator() * other.getNumerator(), getDenominator() * other.getDenominator());
}
Fraction Fraction::operator/(const Fraction& other)
{
	if (!other.getNumerator())
	{
		throw FailedOperationException();
	}
	return Fraction(getNumerator() * other.getDenominator(), getDenominator() * other.getNumerator());
}
Fraction operator!(const Fraction& other)
{

	if (!other.getNumerator())
	{
		throw FailedOperationException();
	}

	return Fraction(other.getDenominator(), other.getNumerator());
}

Fraction::Fraction(int numerator, int denominator)
	:_numerator(numerator), _denominator(denominator)
{
	if (0 == denominator)
	{
		throw DenominatorIsZeroException();
	}
}

void Fraction::setNumerator(int numerator)
{
	_numerator = numerator;
}

void Fraction::setDenominator(int denominator)
{
	if (0 == denominator)
	{
		throw DenominatorIsZeroException();
	}
	_denominator = denominator;

}

int Fraction::getNumerator() const
{
	return _numerator;
}

int Fraction::getDenominator() const
{
	return _denominator;
}
