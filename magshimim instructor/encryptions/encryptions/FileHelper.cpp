#include "FileHelper.h"

FileHelper::FileHelper()
{
}

FileHelper::~FileHelper()
{
}

std::string FileHelper::readFileToString(std::string fileName)
{
	std::ifstream file;
	std::string fileContent;

	file.open(fileName);
	if (!file.is_open())
	{
		return "Error opening file\n";
	}
	else
	{
		std::string currLine;

		while (std::getline(file, currLine))
		{
			// adds '\n' and than adds the line
			fileContent += currLine + "\n";
		}

		file.close();
	}
	return fileContent;
}

void FileHelper::writeWordsToFile(std::string inputFileName, std::string outputFileName)
{
	std::ifstream iFile;
	std::ofstream oFile(outputFileName, std::ofstream::out);

	if (!oFile.is_open())
	{
		std::cout << "Error opening output file" << std::endl;
	}
	else
	{
		iFile.open(inputFileName);		
		if (!iFile.is_open())
		{
			oFile.close();
			std::cout << "Error opening input file" << std::endl;
		}
		else
		{
			std::string currWord;

			while (!iFile.eof())
			{
				iFile >> currWord;					// reads a word from input file
				oFile << currWord << std::endl;		// writes the word to output file each in seperate line
			}

			iFile.close();
			oFile.close();
		}
	}
}
