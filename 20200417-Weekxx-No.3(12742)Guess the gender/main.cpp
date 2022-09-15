#include <iostream>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

int main() {
	ios::sync_with_stdio(false);// iostreamÀu¤Æ
	cin.tie(nullptr);

	int n, m; 	cin >> n >> m;
	Graph G(n);
	while (m--) {
		int x, y; cin >> x >> y;
		G.addEdge(x, y);
		G.addEdge(y, x);
	}

	if (G.solver()) cout << "Possible" << endl;
	else cout << "Not Possible" << endl;
	
	system("pause");
}
