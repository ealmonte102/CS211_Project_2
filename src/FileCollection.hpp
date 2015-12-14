#ifndef FILECOLLECTION_HPP
#define FILECOLLECTION_HPP

#include "File.hpp"

#include <vector>

class FileCollection {
public:
	FileCollection ( );
	void mainMenu ( );
private:
	enum findFlag {
		NOT_FOUND = -1
	};
	void createImageFile ( );
	void createTextFile ( );
	void deleteFile (std::string name, std::string extension);
	int findFile (std::string name, std::string extension) const;
	void printAllFiles ( ) const;
	void printFiles (std::string extension) const;
	void readFromFile ( );
	void writeToFile ( ) const;
	
	std::vector<File*> fileList;
};

#endif //FILECOLLECTION_HPP

