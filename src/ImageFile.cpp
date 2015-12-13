// ImageFile.cpp
// Created by Evan Almonte
//
#include "ImageFile.hpp"

const std::string ImageFile::extension = "gif";

ImageFile::ImageFile( ) : File(extension), pixelMatrix(SafeMatrix<int>(0, 0)), colorDepth(0) { }

ImageFile::ImageFile(std::string fileName, int height, int width, int cD) :
	File(fileName, extension), pixelMatrix(SafeMatrix<int>(height, width)), colorDepth(cD) { }

ImageFile::ImageFile(std::string fileName, SafeMatrix<int> pixelMatrix, int colorDepth) :
	File(fileName, extension), pixelMatrix(pixelMatrix), colorDepth(colorDepth) {}

int ImageFile::getColorDepth( ) const {
	return colorDepth;
}

int ImageFile::getDimensionHeight( ) const {
	return pixelMatrix.length();
}

int ImageFile::getDimensionWidth( ) const {
	return pixelMatrix.width();
}

int ImageFile::getSize( ) const {
	return static_cast<double>(pixelMatrix.length() * pixelMatrix.width() * colorDepth) / 8;
}
