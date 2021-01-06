#pragma once

#include "DenominatorIsZeroException.h"
#include "FailedOperationException.h"
class Fraction
{
public:
	Fraction(int numerator, int denominator);
	~Fraction() = default;

	int getNumerator() const;
	int getDenominator() const;

	void setNumerator(int numerator);
	void setDenominator(int denominator);

	Fraction operator+(const Fraction&);
	Fraction operator-(const Fraction&);
	Fraction operator*(const Fraction&);
	Fraction operator/(const Fraction&);
	friend Fraction operator!(const Fraction&);
private:
	int _numerator;
	int _denominator;
};

