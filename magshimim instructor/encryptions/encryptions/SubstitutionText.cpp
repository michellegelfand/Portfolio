#include <fstream>//ifstream
#include <string>//getline

#include "SubstitutionText.h"

const int BEFORE_ENC_IDX_CSVFILE = 0;
const int  AFTER_ENC_IDX_CSVFILE = 2;


SubstitutionText::SubstitutionText(std::string text, std::string dictionaryFileName)
	:PlainText(text), _dictionaryFileName(dictionaryFileName)
{
	encrypt();
}

SubstitutionText::~SubstitutionText()
{
}

std::string SubstitutionText::encrypt()
{
	if (_isEncrypted)
	{
		return _text;
	}

	std::ifstream dict;
	std::string curr_line_file;
	std::string encrypted_text = "";

	for (int i = 0; i < _text.length(); i++)
	{
		dict.open(_dictionaryFileName);
		if (_text[i] < 'a' || _text[i] > 'z')//chars not translated such as ' ', ',' '.' 
		{
			encrypted_text += _text[i];
		}
		else
		{
			while (std::getline(dict, curr_line_file))//search letter in dictionary file
			{
				if (curr_line_file[BEFORE_ENC_IDX_CSVFILE] == _text[i])
				{
					encrypted_text += curr_line_file[AFTER_ENC_IDX_CSVFILE];
					break; //exit while loop 
				}
			}
		}
		dict.close();
	}

	_text = encrypted_text;
	_isEncrypted = true;
	return encrypted_text;
}

std::string SubstitutionText::decrypt()
{
	if (!_isEncrypted)
	{
		return _text;
	}

	std::ifstream dict;
	std::string curr_line_file;
	std::string decrypted_text = "";

	for (int i = 0; i < _text.length(); i++)
	{
		dict.open(_dictionaryFileName);
		if (_text[i] < 'a' || _text[i] > 'z')
		{
			decrypted_text += _text[i];
			
		}
		else
		{
			while (std::getline(dict, curr_line_file))//search letter in dictionary file
			{
				if (curr_line_file[AFTER_ENC_IDX_CSVFILE] == _text[i])
				{
					decrypted_text += curr_line_file[BEFORE_ENC_IDX_CSVFILE];
					break; //exit while loop 
				}
			}
		}
		 
		dict.close();
	}

	_text = decrypted_text;
	_isEncrypted = true;
	return decrypted_text;
}

std::ostream& operator<<(std::ostream& os, const SubstitutionText& s)
{
	os << "Substitution text:\n";
	os << s.getText() << std::endl;

	return os;
}