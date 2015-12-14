// FileCollection.cpp
// Created by Evan Almonte
//
#include "FileCollection.hpp"
#include <iostream>
#include <string>
#include "ImageFile.hpp"
#include "TextFile.hpp"

using std::cout;
using std::cin;
using std::string;

FileCollection::FileCollection( ) {}

void FileCollection::mainMenu( ) {
	cout << "Main Menu\n";
	cout << "1) Read from file\n";
	cout << "2) Create an Image file\n";
	cout << "3) Create a Text file\n";
	cout << "4) Print all files\n";
	cout << "5) Print Image files\n";
	cout << "6) Print Text files\n";
	cout << "7) Delete a file\n";
	cout << "8) Terminate\n";
	int userInput;
	cin >> userInput;
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
			getline(cin, fileName, ' ');
			cout << "Enter the file's extension: ";
			getline (cin, fileName, ' ');
			deleteFile (fileName, fileType);

		}	break;
		case 8:
			cout << "Program will now quit.\n";
			return;
		default:
			cout << "Invalid option please try again!\n";
	}
	cout << "Press enter to continue . . .";
	cin.get ( );
	mainMenu ( );
}

void FileCollection::createImageFile( ) {
	int height, width, colorDepth;
	string fileName;
	cout << "Please enter the file's name: ";
	getline (cin, fileName, ' ');
	cout << "Please enter the height of the image: ";
	cin >> height;
	cin.ignore ( );
	cout << "Please enter the width of the image: ";
	cin >> width;
	cin.ignore ( );
	cout << "Please enter the color depth of the image: ";
	cin >> colorDepth;
	cin.ignore ( );
	fileList.push_back (new ImageFile (fileName, height, width, colorDepth));
}

void FileCollection::createTextFile( ) {
	string fileName;
	cout << "Please enter the file's name: ";
	getline (cin, fileName, ' ');
	fileList.push_back (new TextFile (fileName));
}

int FileCollection::findFile(std::string name, std::string extension) const {
	for (int i = 0; i < fileList.size ( ); i++) {
		if (name == fileList[i]->getName ( ) && extension == fileList[i]->getExtension ( )) {
			return i;
		}
	}
	return NOT_FOUND;
}
