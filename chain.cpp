#include "chain.h"

chain::chain(string _pathToOrginalFile) : pathToOrginalFile{ _pathToOrginalFile }, specialChar{'\0'} {
	try {
		string complementaryFilePath = (pathToOrginalFile.erase(pathToOrginalFile.rfind("\\"), string::npos));			//extract raw path
		string exceptionMSG = { "One or more files are not opened.\nFail come from :" };
		char charToChange;

		std::ifstream orginalFile(_pathToOrginalFile, std::ios_base::in | std::ios_base::binary);						//open streams
		std::ofstream complementaryFile(complementaryFilePath + "\\complementary.txt", std::ios_base::out | std::ios_base::binary | std::ios_base::app);

		if (orginalFile.is_open() && complementaryFile.is_open()) {
			orginalFile.seekg(0, std::ios::beg);
			complementaryFile.seekp(0, std::ios::beg);

			for (; orginalFile.peek() != EOF;) {																		//make char complementary till end of orginall file
				orginalFile.read((char*)&charToChange, sizeof(charToChange));
				checkChar(charToChange);
				findComplementaryPart(charToChange);
				complementaryFile.write((char*)&charToChange, sizeof(charToChange));
			}
		}
		else throw(std::ios_base::failure{ exceptionMSG + __FUNCTION__ });
	}
	catch (std::ios_base::failure& exception) {
		cout << exception.what();
		terminate();
	}
}

chain::~chain() {

}

void chain::findComplementaryPart(char& _in) {
	nucleotide* nucleotide{ nucleotide::factory(_in) };
	nucleotide->complementaryRule(_in);
	delete nucleotide;
}

void chain::checkChar(char& _in) throw(std::ios_base::failure) {
	try {
		int comparissionCounter{ 0 };
		string exceptionMSG = { "Replication process fail. More than one special char appear.\nFail come from :" };

		for (int i = 0; i < definitionSet.size(); ++i, ++comparissionCounter)											//check all set ingridients with actual char
			if (_in == definitionSet[i]) break;																			//if char is equal to any ingridient then it is not necessary to check rest set

		if ((comparissionCounter == definitionSet.size()) && (_in != definitionSet[comparissionCounter])) {				//if actual char do not match to definitionSet ingridients then it is special char
			if (specialChar == 0) {
				definitionSet.push_back(_in);
				specialChar = _in;
			}																											//if special char is already assign and diffrent special char appear then throw() exception
			else throw(std::ios_base::failure{ exceptionMSG + __FUNCTION__ });
		}
	}
	catch (std::ios_base::failure& exception) {
		cout << exception.what();
		terminate();
	}
}
