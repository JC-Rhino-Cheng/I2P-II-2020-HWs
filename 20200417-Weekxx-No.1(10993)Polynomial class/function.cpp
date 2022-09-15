#include "function.h"
#include <iostream>
#define Max(a, b) ( ( a > b ) ? a : b )

Polynomial :: Polynomial() {//第一個constructor，是在本function.cpp的line62所用到的constructor，也是main的line11用到的constructor。
	for (int i = 0; i < 101; i++)coefficients[i] = 0;//兩個函式相乘，50次方和50次方相乘，最多可能100次方。
	greatestPower = 0;

	//constructor 不能return任何東西。
}

Polynomial :: ~Polynomial() {}

Polynomial :: Polynomial(const int greatest_power, const int coeff[51]) {//第二個constructor，是main function line15、line19會用到的constructor。
	greatestPower = greatest_power;

	for (int i = 0; i < 101; i++)coefficients[i] = 0;//保險起見，把所有原始的係數設為0。//兩個函式相乘，50次方和50次方相乘，最多可能100次方。
	for (int i = greatestPower; i >= 0; i--) coefficients[i] = coeff[i];

	//constructor 不能return任何東西。
}

Polynomial Polynomial :: add(const Polynomial from) const{
	Polynomial temp = *this;//先用pass-by-value來創建一個一模一樣的Polynomial object。

	int bigger_degree = Max(temp.greatestPower, from.greatestPower);
	for (int i = bigger_degree; i >= 0; i--) 
		temp.coefficients[i] += from.coefficients[i];
	
	//設定temp的greatestPower，因為可能一加一減就把原定的degree給弄小了。
	temp.greatestPower = bigger_degree;//先預設為bigger_degree
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