#include <iostream>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

int main() {
	int n, m; cin >> n >> m;
	if (n >= m) cout << 1 << endl;
	else {
		//Matrix base = constructMatrix(n);//�U�мg�k�A���ڥu�����ΧU�Ъ�ret�x�}�������A�èS���ĥΥL�̨�L���F��A�ҥH�u�n�ݧU�д���pdf��P1~10�BP14�Y�i
		Matrix base = Matrix(n);//�ڪ��g�k�o�˧Y�i�C
		base = base.power(m - n);//�ίx�}�����k������A��n�F
		int ans = 0;
		for (int i = 0; i < n; i++) ans = (ans + base(n - 1, i)) % mod;
		cout << ans << endl;
	}

	system("pause");
}
