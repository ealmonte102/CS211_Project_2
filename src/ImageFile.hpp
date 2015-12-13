#ifndef IMAGEFILE_HPP
#define IMAGEFILE_HPP

#include "File.hpp"
#include "SafeMatrix.hpp"
#include <string>

class ImageFile : public File {
public:
	ImageFile( );

	ImageFile(std::string fileName, int height, int width, int colorDepth);

	ImageFile (std::string fileName, SafeMatrix<int> pixelMatrix, int colorDepth);

	int getColorDepth( ) const;

	int getDimensionHeight( ) const;

	int getDimensionWidth( ) const;

	int getSize( ) const override;
private:
	SafeMatrix<int> pixelMatrix;
	int colorDepth;
	static const std::string extension;
};

#endif //IMAGEFILE_HPP
