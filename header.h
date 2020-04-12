#include <iostream>
#include <string>
#include <fstream>
#include "nucleotide.h"
#include "chain.h"

/*PDF PARSER - LIBRARY*/
#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/ElementReader.h>
#include <PDF/Element.h>
#include <PDF/Font.h>
#include <Filters/FilterReader.h>
#include <PDF/Image/Image2RGB.h>
#include <PDF/TextExtractor.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using namespace pdftron;
using namespace PDF;
using namespace SDF;
using namespace Common;
using namespace Filters;

constexpr int beginingPageOfChain = 2;
constexpr int lastPageOfChain = 34;

TextExtractor::Line skipLayer(TextExtractor &_page) {
	TextExtractor::Line line;

	line = _page.GetFirstLine();
	line = line.GetNextLine();
	line = line.GetNextLine();

	return line;
}

bool convertPDF(string _pathToDirectory, string _fileName, string _afterConversionFileName) throw(){		//f. to extract raw chain from PDF
	PDFNet::Initialize();
	int pageCounter = beginingPageOfChain;
	int pageCount = lastPageOfChain;
	int returnVal = 0;

	try {
		std::ofstream resultFile(_pathToDirectory + _afterConversionFileName, std::ios_base::out | std::ios_base::binary);
		PDFDoc sourceChain(_pathToDirectory + _fileName);
		Page actualPage;
		TextExtractor rawPage;
		TextExtractor::Line rawLine;
		TextExtractor::Word rawWord;
		UString rawTxt;

		sourceChain.InitSecurityHandler();

		while (pageCounter <= pageCount) {											//get page -> get line -> get word -> save to new file 
			actualPage = sourceChain.GetPage(pageCounter);
			rawPage.Begin(actualPage);
			rawLine = skipLayer(rawPage);											

			for (; rawLine.IsValid(); rawLine = rawLine.GetNextLine()) {
				for (rawWord = rawLine.GetFirstWord(); rawWord.IsValid(); rawWord = rawWord.GetNextWord()) {
					rawTxt.Assign(rawWord.GetString(), rawWord.GetStringLen());
					resultFile << rawTxt;
				}
			}
			++pageCounter;
		}
	}
	catch (Exception& e) {
		cout << e << endl;
		returnVal = 1;
	}
	catch (...) {
		cout << "Unknown Exception" << endl;
		returnVal = 1;
	}

	return returnVal;
}

bool checkSignature(string _fileName) {												//f. to check file signature
	std::ifstream fileToCheck(_fileName, std::ios_base::in | std::ios_base::binary);
	string PDFsignature{ "%PDF-" };
	int signatureSize = PDFsignature.size();
	char readedSignature[6]{""};

	if (fileToCheck.is_open()) {
		fileToCheck.seekg(0, std::ios_base::beg);
		fileToCheck.read(readedSignature, signatureSize);
	}

	return (readedSignature != PDFsignature ? false : true);
}

bool isPDF(string _fileName) {														//f. to check if file is pdf
	bool result = false;
	string extension{".pdf"}, help;

	for (char singleChar : _fileName)
		help += std::tolower(singleChar);

	if (help.rfind(extension) == (help.size() - extension.size()))					//if extension is .pdf then...
		result = checkSignature(help);												//check if file has correct format signature

	return result;
}

