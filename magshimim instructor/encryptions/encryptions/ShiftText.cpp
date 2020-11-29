#include "ShiftText.h"

const int NUM_LETTERS_ALPHABET = 26;

ShiftText::ShiftText(std::string text, int key)
	:PlainText(text), _key(key)
{
	encrypt();
}

ShiftText::~ShiftText()
{
}

std::string ShiftText::encrypt()
{
	//if text not encrypted then encrypts, then returns it

	if (!_isEncrypted)// (_isEncrypted is protected member of base class)
	{	//encrypt			
		for (char &c : _text)
		{
			if (c >= 'a' && c <= 'z')
			{
				c = (c - 'a' + _key) % NUM_LETTERS_ALPHABET + 'a';
			}
		}

		_isEncrypted = true;
	}

	return _text;

}

std::string ShiftText::decrypt()
{
	if (_isEncrypted)
	{
		_key = NUM_LETTERS_ALPHABET - _key;
		_isEncrypted = false;
		encrypt();
		_key = NUM_LETTERS_ALPHABET - _key;
	}

	_isEncrypted = false; //because encrypt reset it to true
	return _text;
}


std::ostream& operator<<(std::ostream& os, const ShiftText& s)
{
	os << "Shift text:\n";
	os << s.getText() << std::endl;

	return os;
}