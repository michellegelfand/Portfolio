#pragma once
#include "ShiftText.h"

/*The Caesar cipher type of a letter substitution cipher 
* in which each letter is replaced with the third letter ahead of it in the alphabet
* https://en.wikipedia.org/wiki/Caesar_cipher
* 
* NOTE: encrypts only small letters in the English alphabet
*/
class CaesarText : public ShiftText
{
public:
	CaesarText(std::string text);
	~CaesarText() = default;

	friend std::ostream& operator<<(std::ostream& os, const CaesarText& c);
};

