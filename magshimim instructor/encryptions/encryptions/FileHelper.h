#pragma once

#include <string>
#include <iostream>
#include <fstream>

class FileHelper
{
public:

//ctor dtor
	FileHelper();
	~FileHelper();

//static methods
	static std::string readFileToString(std::string fileName);
	static void writeWordsToFile(std::string inputFileName, std::string outputFileName);

};

