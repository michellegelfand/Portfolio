#include "PlainText.h"

int PlainText::numOfTexts = 0; //static member init

PlainText::PlainText(std::string text)
	:_text(text), _isEncrypted(false)
{
	numOfTexts++;
}

PlainText::~PlainText()
{
	numOfTexts--;
}

bool PlainText::isEncrypted() const
{
	return _isEncrypted;
}

std::string PlainText::getText() const
{
	return _text;
}

std::ostream& operator<<(std::ostream& os, const PlainText& p)
{
	os << "plain text:\n";
	os << p.getText() << std::endl;

	return os;
}
