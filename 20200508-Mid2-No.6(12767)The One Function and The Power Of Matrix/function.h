#ifndef FUNCTION_H
#define FUNCTION_H
#pragma warning (disable: 4996)
#include <iostream>
using namespace std;
const int mod = 1000000009;

class Matrix {
private:
	int n;
	long long **matrix;
public:
		Matrix() {//Default Constructor，不會用到
		n = 0;
		matrix = nullptr;
	}

	~Matrix();// TODO: Destructor

	Matrix(int n);// TODO: Customised Constructor

	Matrix(const Matrix& ref);// TODO: Copy contructor

	
	Matrix& operator=(const Matrix& ref);// TODO: copy assignment

	// TODO: Overload operator()
	// This operator can help you access the data easily
	// 1. cout << m(1, 2) << endl;相當於cout << m.matrix[1][2] << endl;
	// 2. m(1, 2) = 100;相當於m.matrix[1][2] = 100
	long long& operator()(const int& row, const int& column) const;

	void toIdentity();//Identity的第一個字母是哀鳳的哀，不是欸樓

	void toZero() {
		for (int i = 0; i < n; i++) 	for (int j = 0; j < n; j++) matrix[i][j] = 0;
	}

	// TODO: Overload operator * (乘以的意思，不是指標)，記得矩陣的乘法是內積!
	Matrix operator*(const Matrix& rhs) const;

	Matrix power(int k) const;

	friend ostream& operator<<(ostream& output, const Matrix& matrix) {
		for (int i = 0; i < matrix.n; i++) {
			for (int j = 0; j < matrix.n; j++) output << matrix(i, j) << ' ';
			output << endl;
		}
		return output;
	}
};

// TODO: Construct a matrix
Matrix constructMatrix(int n);

#endif
