#include "header.h"

int main(int argc, char *argv []) {
	if (argc >= 4) {
		string pathToDirectory = argv[1];							//R"(C:\Users\meUser\Desktop\Files\)";
		string fileName = argv[2];									//"zadanie-weryfikacyjne.v3.0.pdf";
		string afterConversionFileName = argv[3];					// "orginal.txt"

		if (isPDF(pathToDirectory + fileName)) {					//if file is PDF then extract raw chain to other file
			convertPDF(pathToDirectory, fileName, afterConversionFileName);
		}

		chain DNA(pathToDirectory + afterConversionFileName);		//make complementary chain
	}

	return 0;
}