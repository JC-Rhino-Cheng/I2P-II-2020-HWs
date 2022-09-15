#include <iostream>
#include <stdio.h>
#include <string>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

int main(){
	int greatestPower1, greatestPower2;
	int coefficient1[51], coefficient2[51];
	Polynomial ans;

	cin >> greatestPower1;
	for (int i = greatestPower1; i >= 0; i--) 	cin >> coefficient1[i];
	Polynomial a(greatestPower1, coefficient1);

    cin>>greatestPower2;
	for (int i = greatestPower2; i >= 0; i--) 	cin >> coefficient2[i];
	Polynomial b(greatestPower2, coefficient2);

	ans = a.add(b);
	ans.output();
	cout << endl;

	ans = a.subtract(b);
	ans.output();
	cout << endl;

	ans = a.multiplication(b);
	ans.output();
	cout << endl;

	system("pause");
} // end main
