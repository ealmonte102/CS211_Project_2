// FileCollection.cpp
// Created by Evan Almonte
//
#include "FileCollection.hpp"
#include "ImageFile.hpp"
#include "TextFile.hpp"
#include "Utilities.hpp"
#include <fstream>
#include <iostream>
#include <string>

using Project2_Utilities::upperConvert;
using std::cout;
using std::cin;
using std::ifstream;
using std::string;

namespace FileCollectionUtils {
	void outputProperties (const vector<File*>& files);
	void outputPropertiesRec (vector<File*>& files);
	vector<File*> filterFiles (const vector<File*>& files, std::string extension);
	void filterFilesRec (vector<File*>& sourceVector, vector<File*>& destVector, std::string extension);
}

FileCollection::FileCollection( ) {}

void FileCollection::mainMenu( ) {
	Project2_Utilities::clearScreen ( );
	cout << "***********************\n";
	cout << "       Main Menu\n";
	cout << "***********************\n";
	cout << "1) Read from file\n";
	cout << "2) Create an Image file\n";
	cout << "3) Create a Text file\n";
	cout << "4) Print All files\n";
	cout << "5) Print Image files\n";
	cout << "6) Print Text files\n";
	cout << "7) Delete a file\n";
	cout << "8) Terminate\n";
	int userInput;
	userInput = Project2_Utilities::getValidInt();
	switch(userInput) {
		case 1:
			readFromFile ( );
			break;
		case 2:
			createImageFile ( );
			break;
		case 3:
			createTextFile ( );
			break;
		case 4:
			printAllFiles ( );
			break;
		case 5:
			printFiles ("gif");
			break;
		case 6:
			printFiles ("txt");
			break;
		case 7: 
		{
			string fileName, fileType;
			cout << "Enter the file's name: ";
			getline(cin, fileName);
			cout << "Enter the file's extension: ";
			getline (cin, fileType);
			deleteFile (fileName, fileType);

		}	break;
		case 8:	
			cout << "Program will now quit.\n";
			writeToFile ( );
			return;
		default:
			cout << "Invalid option please try again!\n";
	}
	cout << "Press enter to continue . . .\n";
	cin.get ( );
	mainMenu ( );
}

void FileCollection::createImageFile( ) {
	Project2_Utilities::clearScreen ( );
	int height, width, colorDepth;
	cout << "***********************\n";
	cout << "   Create Image File\n";
	cout << "***********************\n";
	string fileName;
	cout << "Please enter the file's name: ";
	getline (cin, fileName);
	cout << "Please enter the height of the image: ";
	height = Project2_Utilities::getValidInt( );
	cout << "Please enter the width of the image: ";
	width = Project2_Utilities::getValidInt ( );
	cout << "Please enter the color depth of the image: ";
	colorDepth = Project2_Utilities::getValidInt ( );
	fileList.push_back (new ImageFile (fileName, height, width, colorDepth));
}

void FileCollection::createTextFile( ) {
	Project2_Utilities::clearScreen ( );
	cout << "***********************\n";
	cout << "    Create Text File\n";
	cout << "***********************\n";
	string fileName;
	cout << "Please enter the file's name: ";
	getline (cin, fileName);
	fileList.push_back (new TextFile (fileName));
}

void FileCollection::deleteFile(std::string name, std::string extension) {
	Project2_Utilities::clearScreen ( );
	int location = findFile (name, extension);
	if(location == NOT_FOUND) {
		cout << "Could not find the file specified.\n";	
		return;
	}
	delete fileList[location];
	fileList.erase (fileList.begin() + location);
	cout << "***********************\n";
	cout << " File Has Been Deleted\n";
	cout << "***********************\n";
}

int FileCollection::findFile(std::string name, std::string extension) const {
	name = upperConvert (name);
	extension = upperConvert (extension);
	for (int i = 0; i < fileList.size ( ); i++) {
		if (name == upperConvert(fileList[i]->getName ( ))
			&& extension == upperConvert(fileList[i]->getExtension ( ))) {
			return i;
		}
	}
	return NOT_FOUND;
}

void FileCollection::printAllFiles( ) const {
	Project2_Utilities::clearScreen ( );
	cout << "***********************\n";
	cout << "       File List\n";
	cout << "***********************\n";
	FileCollectionUtils::outputProperties (fileList);
}

void FileCollection::printFiles(std::string extension) const {
	Project2_Utilities::clearScreen ( );
	cout << "***********************\n";
	cout << "      " + extension + " File List    \n";
	cout << "***********************\n";
	vector<File*> filesFound = FileCollectionUtils::filterFiles (fileList, extension);
	FileCollectionUtils::outputProperties (filesFound);
}

void FileCollection::readFromFile( ) {
	Project2_Utilities::clearScreen ( );
	cout << "***********************\n";
	cout << "   Reading From File   \n";
	cout << "***********************\n";
	int filesRead = 0;
	ifstream inputFile ("file.txt");
	if(inputFile.is_open()) {
		string inputLine;
		while(getline(inputFile, inputLine)) {
			if(inputLine == "txt") {
				string fileName;
				int fileSize;
				inputFile >> fileName >> fileSize;
				inputFile.ignore ( );
				fileList.push_back (new TextFile (fileName, SafeArray<int> (fileSize)));
				filesRead++;
			} else if (inputLine == "gif") {
				string fileName;
				int height, width, colorDepth;
				inputFile >> fileName >> height;
				inputFile.get ( );
				inputFile.get ( );
				inputFile.get ( );
				inputFile >> width >> colorDepth;
				fileList.push_back (new ImageFile (fileName, height, width, colorDepth));
				inputFile.ignore ( );
				filesRead++;
			}
		}
	} else {
		cout << "Could not find file.txt\n";
	}
	cout << filesRead << " file" << (filesRead != 1 ? "s" : "");
	cout << " read\n";
}

void FileCollection::writeToFile( ) const {
	ofstream outputFile ("file.txt");
	int numOfFiles = fileList.size ( );
	for (int i = 0; i < numOfFiles; ++i) {
		File* currentFile = fileList[i];
		outputFile << currentFile->getExtension ( ) << "\n" 
			<< currentFile->getName() << "\n";
		
		if(currentFile->getExtension() == "gif") {
			ImageFile* anImageFile = dynamic_cast<ImageFile*>(currentFile);
			outputFile << anImageFile->getDimensionHeight ( ) << " x "
				<< anImageFile->getDimensionWidth ( ) << "\n"
				<< anImageFile->getColorDepth() << "\n";
		} else {
			outputFile << currentFile->getSizeInBits ( ) << "\n";
		}

		if(i != numOfFiles - 1) {
			outputFile << "\n";
		}
	}
	outputFile.close ( );
}

namespace FileCollectionUtils {
	void outputProperties (const vector<File*>& files) {
		vector<File*> tempFiles(files);
		outputPropertiesRec (tempFiles);
	}

	void outputPropertiesRec(vector<File*>& files) {
		if (files.size ( ) != 0) {
			File* lastElement = files.back ( );
			files.pop_back ( );
			outputProperties (files);
			cout << "Type: " + lastElement->getExtension ( ) + "\n";
			cout << "Name: " + lastElement->getName ( ) + "\n";
			if(lastElement->getExtension() == "gif") {
				ImageFile* anImageFile = dynamic_cast<ImageFile*>(lastElement);
				cout << "Dimension: " << anImageFile->getDimensionHeight ( ) << " x " 
				 << anImageFile->getDimensionWidth ( ) << "\n";
			}
			cout << "Size: " << lastElement->getSize ( ) << " bytes\n\n";
		}
	}

	vector<File*> filterFiles (const vector<File*>& files, std::string extension) {
		vector<File*> tempFiles(files), filesToReturn;
		filterFilesRec (tempFiles, filesToReturn, extension);
		return filesToReturn;
	}

	void filterFilesRec (vector<File*>& sourceVector, vector<File*>& destVector, std::string extension) {
		if (sourceVector.size ( ) == 0) { return; }
		File* fileAtEnd = sourceVector.back ( );
		sourceVector.pop_back ( );
		filterFilesRec (sourceVector, destVector, extension);
		if (fileAtEnd->getExtension ( ) == extension) {
			destVector.push_back (fileAtEnd);
		}
	}

}
