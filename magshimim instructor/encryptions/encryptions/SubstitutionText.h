#pragma once
#include "PlainText.h"


//This cipher swaps letters according to a key given in a "dictionary" file.
//It can be tested on the file "conversation.txt", using the file "dictionary.csv" for the cipher key


//NOTE: ciphers small English letters only
class SubstitutionText :public PlainText
{
public:
	SubstitutionText(std::string text, std::string dictionaryFileName);
	~SubstitutionText();

	std::string encrypt();
	std::string decrypt();

	friend std::ostream& operator<<(std::ostream& os, const SubstitutionText& s);

private:
	std::string _dictionaryFileName;
};

