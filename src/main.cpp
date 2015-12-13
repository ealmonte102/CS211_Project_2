// main.cpp
// Created by Evan Almonte
//  
#include "File.hpp"
#include "ImageFile.hpp"
#include "TextFile.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;


void outputProperties (vector<File*>& files);
vector<File*> filterFiles (vector<File*> files, std::string extension);
void filterFilesRec (vector<File*>& sourceVector, vector<File*>& destVector, std::string extension);

int main() {
	vector<File*> vecOfFiles;
	vecOfFiles.push_back (new ImageFile ("Evan's First File", 10, 10, 16));
	vecOfFiles.push_back (new TextFile ("Evan's Second File"));
	vecOfFiles.push_back (new ImageFile ("Evan's Third File", 20, 10, 32));
	
	cout << "Testing outputProperties():\n";
	outputProperties (vecOfFiles);

	cout << "\n\nTesting filterFiles():\n";
	vector<File*> testingFilter = filterFiles (vecOfFiles, "txt");
	outputProperties (testingFilter);
	return 0;
}

void outputProperties(vector<File*>& files) {
	if(files.size() != 0) {
		File* lastElement = files.back ( );
		files.pop_back ( );
		outputProperties (files);
		files.push_back (lastElement);
		cout << lastElement->getName ( ) << "\n";
		cout << lastElement->getExtension ( ) << "\n";
		cout << lastElement->getSize ( ) << "\n";
	}
}

vector<File*> filterFiles(vector<File*> files, std::string extension) {
	vector<File*> filesToReturn;
	filterFilesRec (files, filesToReturn, extension);
	return filesToReturn;
}

void filterFilesRec(vector<File*>& sourceVector, vector<File*>& destVector, std::string extension) {
	if (sourceVector.size ( ) == 0) { return; }
	File* fileAtEnd = sourceVector.back ( );
	sourceVector.pop_back ( );
	filterFilesRec (sourceVector, destVector, extension);
	if(fileAtEnd->getExtension() == extension) {
		destVector.push_back (fileAtEnd);
	}
}
