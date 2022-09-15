#include <iostream>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

int main(){
	int n; cin >> n;

	BigInt hi, kaminari, kedamono;
	cin >> hi;
	kaminari = kedamono = hi;//初始化健康狀況//hi代表炭治郎、kaminari代表善逸、kedamono代表野豬

	solution(hi, kaminari, kedamono, n);//出任務

	cout << hi << endl;
	cout << kaminari << endl;
	cout << kedamono << endl;

	system("pause");
}
