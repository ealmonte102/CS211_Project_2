#ifndef SAFE_MATRIX_HPP
#define SAFE_MATRIX_HPP

#include "SafeArray.hpp"
#include <iosfwd>

using std::ostream;

template <class T>

class SafeMatrix {
public:
	SafeMatrix (int rows, int cols);
	
	//Used to test various components in the SafeMatrix class.
	void driver ( );
	
	int width ( ) const;

	//Returns the number of rows in the matrix.
	int length ( ) const;
	
	//Returns a SafeArray located at the index specified. Boundaries are checked.
	SafeArray<T>& operator[](int index);
	
	friend ostream& operator<<(ostream& output, const SafeMatrix& aSafeMatrix) {
		for (int i = 0; i < aSafeMatrix.rowSize; ++i) {
			output << aSafeMatrix.myRows[i] << "\n";
		}
		return output;
	}
private:
	int rowSize;

	//SafeArray of SafeArrays.
	SafeArray<SafeArray<T>> myRows;
};

template <class T>
SafeMatrix<T>::SafeMatrix(int rows, int cols) : rowSize(rows), myRows(SafeArray<SafeArray<T>>(rowSize)) {
	for (int i = 0; i < rowSize; ++i) {
		myRows[i] = SafeArray<T>(cols);
	}
}

//Used to test various components.(operator>>, operator<<, operator[]).
template <class T>
void SafeMatrix<T>::driver ( ) {
	cout << "=====Testing the >> operator=====\n";
	for (int i = 0; i < rowSize; ++i) {
		for (int j = 0; j < myRows[0].length ( ); ++j) {
			cin >> (*this)[i][j];
		}
	}

	cout << "=====Testing the << operator=====\n";
		cout << *this;

	cout << "=====Testing the [] operator=====\n";
	cout << "SafeMatrix[0]: " << (*this)[0] << "\n";
}

template <class T>
int SafeMatrix<T>::width ( ) const {
	if(rowSize == 0) {
		return 0;
	}
	return myRows[0].length ( );
}

template <class T>
int SafeMatrix<T>::length( ) const {
	return rowSize;
}

template <class T>
SafeArray<T>& SafeMatrix<T>::operator[](int index)
{
	return myRows[index];
}

#endif //SAFE_MATRIX_HPP

