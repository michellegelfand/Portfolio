#pragma once

#include <iostream>

class PlainText
{	
public:
	//ctor dtor
	PlainText(std::string text);
	~PlainText();

	friend std::ostream& operator<<(std::ostream& os, const PlainText& p);

	//getters
	bool isEncrypted() const;
	std::string getText() const;
	static int numOfTexts;
protected:
	std::string _text;
	bool _isEncrypted;
};