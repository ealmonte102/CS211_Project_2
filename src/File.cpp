// File.cpp
// Created by Evan Almonte
//
#include "File.hpp"
#include <string>

using std::string;

File::File( ) : name(""), extension("") { }

File::File(std::string extension) : name(""), extension(extension) {}

File::File(std::string name, std::string extension) : name(name), extension(extension) { }

File::~File( ) {}

string File::getName( ) const {
	return name;
}

string File::getExtension( ) const {
	return extension;
}
