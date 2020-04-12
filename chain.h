#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <Common\Exception.h>
#include "nucleotide.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;

constexpr char firstDefinition = 'A';
constexpr char secondDefinition = 'T';
constexpr char thirdDefinition = 'C';
constexpr char fourthDefinition = 'G';

class chain final
{
private:
	string definitionSet{ firstDefinition, secondDefinition, thirdDefinition, fourthDefinition };
	string pathToOrginalFile;
	char specialChar;
	std::ifstream orginalFile;
	std::ofstream complementaryFile;

	inline void findComplementaryPart(char &_in);					//f. to find correct char according to complementary rules
	inline void checkChar(char& _in) throw(std::ios_base::failure);	//f. to check correctness of char (is it compatible with Definition set or at least with specialChar?)

public:
	chain(string _pathToFile) throw(std::ios_base::failure);
	virtual ~chain();
};

