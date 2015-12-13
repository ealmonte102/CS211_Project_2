#ifndef FILE_HPP
#define FILE_HPP
#include <string>

class File {
public:
	File ( );
	
	File (std::string extension);

	File (std::string name, std::string extension);
	
	virtual ~File ( );
	
	std::string getName ( ) const;
	
	std::string getExtension ( ) const;
	
	virtual int getSize ( ) const = 0;
private:
	std::string name;
	std::string extension;
};

#endif //FILE_HPP
