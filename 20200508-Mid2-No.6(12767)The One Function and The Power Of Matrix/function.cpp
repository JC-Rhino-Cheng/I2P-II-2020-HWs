#pragma warning (disable: 4996)
#include "function.h"

Matrix::~Matrix() {
	for (int i = 0; i < n; i++)delete[] matrix[i];
	delete[] matrix;

	//Destructor不return任何東西
}


Matrix::Matrix(int n) {
	this->n = n;
	matrix = new long long*[n];
	for (int i = 0; i < n; i++)matrix[i] = new long long[n];

	toZero();

	//Constructor不return任何東西
}


Matrix::Matrix(const Matrix& ref) {//Copy constructor
	n = ref.n;

	matrix = new long long*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new long long[n];
		for (int j = 0; j < n; j++) matrix[i][j] = ref.matrix[i][j];
	}

	//Constructor不return任何東西
}


Matrix& Matrix::operator=(const Matrix& ref) {//assignment operator
	//if (n != ref.n);//不會有這種情況，因為這個program所用的所有矩陣都是n*n

	//n = ref.n;
	for (int i = 0; i < n; i++)for (int j = 0; j < n; j++)
		matrix[i][j] = ref.matrix[i][j];

	return *this;//Enables cascaded calls
}


long long& Matrix::operator()(const int& row, const int& column) const {
	return matrix[row][column];
}

//我們直接把助教所說的ret矩陣當作Identity
void Matrix::toIdentity() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == n - 1)matrix[i][j] = 1;
			else if (j == i + 1)matrix[i][j] = 1;
			else matrix[i][j] = 0;

	return;
}


Matrix Matrix::operator*(const Matrix& rhs) const {
	//不能直接把值寫進this裡面，因為很多值在內積的時候會重複用到
	Matrix temp = *this;//直接用Copy Constructor

	for (int i = 0; i < temp.n; i++) {
		for (int j = 0; j < temp.n; j++) {
			long long total = 0;
			for (int k = 0; k < temp.n; k++)
				total = (total + this->matrix[i][k] * rhs.matrix[k][j]) % mod;
			temp.matrix[i][j] = total;
		}
	}

	//*this = temp;//因為是個const的函式，所以不能修改this，但沒關係，那我就return temp回去，然後再從main那邊交給assignment operator做處理也可以。
	return temp;
}


Matrix Matrix::power(int k) const {
	Matrix temp(n);
	if (k == 1) {
		temp.toIdentity();
		return temp;
	}

	temp = power(k / 2);
	if (k % 2 == 1)return temp * power(1) * temp;
	else return temp * temp;
}


Matrix constructMatrix(int n) {//建立ret矩陣，我的作法不會用到這個東西，但是礙於partial judge的main是助教已經寫好綁死的東西...所以如果要丟OJ的話，勢必得把這個東西implement
	Matrix temp(n);
	temp.toIdentity();

	return temp;
}