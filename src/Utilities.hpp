#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <string>

namespace Project2_Utilities {
	void clearScreen ( );

	//Converts a string to it's lowercase equivalent.
	std::string upperConvert (std::string data);

	//Return's true if the user enters 'y' or 'Y' and false if 'N' or 'n'.
	bool getYesOrNo ( );

	int getValidInt ( );
}
#endif
