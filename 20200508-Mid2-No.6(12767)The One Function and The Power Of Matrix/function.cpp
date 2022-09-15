#pragma warning (disable: 4996)
#include "function.h"

Matrix::~Matrix() {
	for (int i = 0; i < n; i++)delete[] matrix[i];
	delete[] matrix;

	//Destructor��return����F��
}


Matrix::Matrix(int n) {
	this->n = n;
	matrix = new long long*[n];
	for (int i = 0; i < n; i++)matrix[i] = new long long[n];

	toZero();

	//Constructor��return����F��
}


Matrix::Matrix(const Matrix& ref) {//Copy constructor
	n = ref.n;

	matrix = new long long*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new long long[n];
		for (int j = 0; j < n; j++) matrix[i][j] = ref.matrix[i][j];
	}

	//Constructor��return����F��
}


Matrix& Matrix::operator=(const Matrix& ref) {//assignment operator
	//if (n != ref.n);//���|���o�ر��p�A�]���o��program�ҥΪ��Ҧ��x�}���On*n

	//n = ref.n;
	for (int i = 0; i < n; i++)for (int j = 0; j < n; j++)
		matrix[i][j] = ref.matrix[i][j];

	return *this;//Enables cascaded calls
}


long long& Matrix::operator()(const int& row, const int& column) const {
	return matrix[row][column];
}

//�ڭ̪�����U�Щһ���ret�x�}��@Identity
void Matrix::toIdentity() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == n - 1)matrix[i][j] = 1;
			else if (j == i + 1)matrix[i][j] = 1;
			else matrix[i][j] = 0;

	return;
}


Matrix Matrix::operator*(const Matrix& rhs) const {
	//���ઽ����ȼg�ithis�̭��A�]���ܦh�Ȧb���n���ɭԷ|���ƥΨ�
	Matrix temp = *this;//������Copy Constructor

	for (int i = 0; i < temp.n; i++) {
		for (int j = 0; j < temp.n; j++) {
			long long total = 0;
			for (int k = 0; k < temp.n; k++)
				total = (total + this->matrix[i][k] * rhs.matrix[k][j]) % mod;
			temp.matrix[i][j] = total;
		}
	}

	//*this = temp;//�]���O��const���禡�A�ҥH����ק�this�A���S���Y�A���ڴNreturn temp�^�h�A�M��A�qmain����浹assignment operator���B�z�]�i�H�C
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


Matrix constructMatrix(int n) {//�إ�ret�x�}�A�ڪ��@�k���|�Ψ�o�ӪF��A���Oê��partial judge��main�O�U�Фw�g�g�n�j�����F��...�ҥH�p�G�n��OJ���ܡA�ե��o��o�ӪF��implement
	Matrix temp(n);
	temp.toIdentity();

	return temp;
}