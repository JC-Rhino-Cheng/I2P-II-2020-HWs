#include <iostream>
#include <string.h>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

void BSTManipulator(BST& bstobj1, BST& bstobj2, char cmd) {
	int n;
	if (cmd == 'I') {
		cin >> n;
		bstobj1.insert(n);
		bstobj2.insert(n);
    }
	else if (cmd == 'S') {
		cin >> n;
		if (bstobj1.search(n))  cout << "yes" << endl;
		else cout << "no" << endl;

		if (bstobj2.search(n)) cout << "yes" << endl;
		else cout << "no" << endl;

    }
	else if (cmd == 'H'){
		cout << bstobj1.height() << endl;
		cout << bstobj2.height() << endl;
    }
	else if (cmd == 'P') {
		bstobj1.print();
		cout << endl;
		bstobj2.print();
		cout << endl;
    }
}


int main() {
	Array_BST Array_bst;
	List_BST List_bst;
	char cmd;

	while (cin >> cmd) BSTManipulator(Array_bst, List_bst, cmd);

	system("pause");
}
