#include "function.h"
#include <iostream>
#define Max(a, b) ( ( a > b ) ? a : b )

Polynomial :: Polynomial() {//�Ĥ@��constructor�A�O�b��function.cpp��line62�ҥΨ쪺constructor�A�]�Omain��line11�Ψ쪺constructor�C
	for (int i = 0; i < 101; i++)coefficients[i] = 0;//��Ө禡�ۭ��A50����M50����ۭ��A�̦h�i��100����C
	greatestPower = 0;

	//constructor ����return����F��C
}

Polynomial :: ~Polynomial() {}

Polynomial :: Polynomial(const int greatest_power, const int coeff[51]) {//�ĤG��constructor�A�Omain function line15�Bline19�|�Ψ쪺constructor�C
	greatestPower = greatest_power;

	for (int i = 0; i < 101; i++)coefficients[i] = 0;//�O�I�_���A��Ҧ���l���Y�Ƴ]��0�C//��Ө禡�ۭ��A50����M50����ۭ��A�̦h�i��100����C
	for (int i = greatestPower; i >= 0; i--) coefficients[i] = coeff[i];

	//constructor ����return����F��C
}

Polynomial Polynomial :: add(const Polynomial from) const{
	Polynomial temp = *this;//����pass-by-value�ӳЫؤ@�Ӥ@�Ҥ@�˪�Polynomial object�C

	int bigger_degree = Max(temp.greatestPower, from.greatestPower);
	for (int i = bigger_degree; i >= 0; i--) 
		temp.coefficients[i] += from.coefficients[i];
	
	//�]�wtemp��greatestPower�A�]���i��@�[�@��N���w��degree���ˤp�F�C
	temp.greatestPower = bigger_degree;//���w�]��bigger_degree
	for (int i = bigger_degree; i >= 0; i--) {
		if (temp.coefficients[i]) {
			temp.greatestPower = i;
			break;
		}
	}

	return temp;
}

Polynomial Polynomial :: subtract(const Polynomial from) const {
	Polynomial temp = *this;

	int bigger_degree = Max(temp.greatestPower, from.greatestPower);
	for (int i = bigger_degree; i >= 0; i--)
		temp.coefficients[i] -= from.coefficients[i];

	temp.greatestPower = bigger_degree;
	for (int i = bigger_degree; i >= 0; i--) {
		if (temp.coefficients[i]) {
			temp.greatestPower = i;
			break;
		}
	}

	return temp;
}

Polynomial Polynomial :: multiplication(const Polynomial from) const {
	Polynomial temp;

	for (int i = 0; i <= from.greatestPower; i++) {
		for (int j = 0; j <= this->greatestPower; j++) 
			temp.coefficients[i + j] += this->coefficients[j] * from.coefficients[i];
	}

	temp.greatestPower = this->greatestPower + from.greatestPower;

	return temp;
}

void Polynomial :: output(void) const {
	for (int i = greatestPower; i; i--) std::cout << coefficients[i] << " ";
	std::cout << coefficients[0];

	return;
}