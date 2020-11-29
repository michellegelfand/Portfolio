#include "CaesarText.h"

const int Caesar_KEY = 3;

CaesarText::CaesarText(std::string text)
	:ShiftText(text, Caesar_KEY)
{
	//initial encryption happens in ShiftText ctor
}

std::ostream& operator<<(std::ostream& os, const CaesarText& c)
{
	os << "Caesar text:\n";
	os << c.getText() << std::endl;

	return os;
}