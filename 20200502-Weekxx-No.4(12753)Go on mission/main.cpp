#include <iostream>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

int main(){
	int n; cin >> n;

	BigInt hi, kaminari, kedamono;
	cin >> hi;
	kaminari = kedamono = hi;//��l�ư��d���p//hi�N���v���Bkaminari�N���h�Bkedamono�N����

	solution(hi, kaminari, kedamono, n);//�X����

	cout << hi << endl;
	cout << kaminari << endl;
	cout << kedamono << endl;

	system("pause");
}
