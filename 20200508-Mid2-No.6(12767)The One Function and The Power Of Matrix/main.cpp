#include <iostream>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

int main() {
	int n, m; cin >> n >> m;
	if (n >= m) cout << 1 << endl;
	else {
		//Matrix base = constructMatrix(n);//助教寫法，但我只有取用助教的ret矩陣的概念，並沒有採用他們其他的東西，所以只要看助教提示pdf的P1~10、P14即可
		Matrix base = Matrix(n);//我的寫法這樣即可。
		base = base.power(m - n);//用矩陣的乘法轉轉轉，轉好了
		int ans = 0;
		for (int i = 0; i < n; i++) ans = (ans + base(n - 1, i)) % mod;
		cout << ans << endl;
	}

	system("pause");
}
