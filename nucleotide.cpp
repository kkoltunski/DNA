#include "nucleotide.h"

constexpr char firstDefinition = 'A';
constexpr char secondDefinition = 'T';
constexpr char thirdDefinition = 'C';
constexpr char fourthDefinition = 'G';

nucleotide* nucleotide::factory(char _representation) throw(std::bad_alloc) {						//this is encapsuled factory which return address of choosen object based on delivered char
	try {
		switch (_representation) {
		case firstDefinition:
			return new adenine();
		case secondDefinition:
			return new thymine();
		case thirdDefinition:
			return new cytosine();
		case fourthDefinition:
			return new guanine();
		default:
			return new special();
		}
	}
	catch (std::bad_alloc& _exception) {
		std::cout << _exception.what() << "\nFail come from : " << __FUNCTION__ << std::endl;
		terminate();
	}
}