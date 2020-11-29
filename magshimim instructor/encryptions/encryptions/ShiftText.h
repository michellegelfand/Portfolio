#pragma once
#include "PlainText.h"
class ShiftText : public PlainText
{
//This class encrypts and decrypts text according to the Substitudion cipher method
//by taking all letters and shifting them to the next letter the number of times dictated by _key.
//https://en.wikipedia.org/wiki/Substitution_cipher

//NOTE: encrypts only small letters in the English alphabet.
public:
	//ctor dtor
	ShiftText(std::string text, int key);
	~ShiftText();

	//methods

	//encrypts the text, storing it in the object
	//as well as returns a copy of the encrypted text to the user.
	std::string encrypt();
	//decrypts the text, storing it in the object
	//as well as returns a copy of the decrypted text to the user.
	std::string decrypt();


	friend std::ostream& operator<<(std::ostream& os, const ShiftText& s);

private:
	int _key;
};

