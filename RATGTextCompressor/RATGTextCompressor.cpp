#include <iostream>
#include <fstream>
#include <string>
#include <vector>

uint16_t FindOffset(std::vector<std::string>& vList, const std::string& testStr)
{
	for (size_t i = 0; i < vList.size(); ++i)
	{
		if (vList[i].compare(testStr) == 0)
		{
			return static_cast<uint16_t>(i);
		}
	}
	return (uint16_t)-1;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout	<< "Please provide a text file to handle and an output dir." << std::endl 
					<< "Example usage: RATGTextCompressor.exe dialog_input.txt src" << std::endl 
					<< "Format of txt input (one per line):" << std::endl 
					<< "DialogID,Text for them to say! In the game!" << std::endl;
		return 1;
	}


	std::vector<std::string> TokenLib;

	std::string strOutHeader = argv[2];
	strOutHeader.append("//dialog_data.h");
	std::string strOutSrc = argv[2];
	strOutSrc.append("//dialog_data.c");

	std::ifstream input(argv[1]);
	std::ofstream outputHeader(strOutHeader, std::ios::out);
	std::ofstream output(strOutSrc, std::ios::out);

	outputHeader << "#pragma once" << std::endl;
	outputHeader << "#include \"wasm4.h\""<< std::endl << std::endl;

	output << "#include \"dialog_data.h\"" << std::endl << std::endl;

	std::string line;
	while (std::getline(input, line))
	{
		size_t firstCommaAt = line.find(',');
		if (firstCommaAt != -1)
		{
			std::string sTextID = line.substr(0, firstCommaAt);
			std::string sTextContent = line.substr(firstCommaAt + 1);

			output << "// " << sTextID << " = \"" << sTextContent << "\"" << std::endl;
			output << "const uint16_t DLGTEXT_" << sTextID << "[] = {";

			sTextContent.append(" ");

			size_t lastTokenStart = 0;
			size_t nextSpaceAt = sTextContent.find(' ');
			while (nextSpaceAt != -1)
			{
				std::string sNextToken = sTextContent.substr(lastTokenStart, nextSpaceAt - lastTokenStart);

				uint16_t nextTokenID = FindOffset(TokenLib, sNextToken);
				if (nextTokenID == (uint16_t)-1)
				{
					nextTokenID = static_cast<uint16_t>(TokenLib.size());
					TokenLib.push_back(sNextToken);
				}

				output << nextTokenID;
				output << ", ";

				lastTokenStart = nextSpaceAt + 1;
				nextSpaceAt = sTextContent.find(' ', lastTokenStart);
			}
			output << "(uint16_t)-1 };" << std::endl << std::endl;

			outputHeader << "extern const uint16_t DLGTEXT_" << sTextID << "[];" << std::endl;
		}
	}

	outputHeader << std::endl << "extern const char* DLG_IDLOOKUP[];" << std::endl;

	output << "const char* DLG_IDLOOKUP[] = { ";
	for (const std::string& nextToken : TokenLib)
	{
		output << "\"" << nextToken << "\", ";
	}
	output << "};";
}