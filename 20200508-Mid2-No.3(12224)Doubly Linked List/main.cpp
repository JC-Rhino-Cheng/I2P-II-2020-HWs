#include <iostream>
#include <string>
#include <stdexcept>
#include "function.h"
#pragma warning (disable: 4996)
using namespace std;

int main() {
	List L;
	string cmd;
	int data, cnt = 0, pos = 0;

	while (cin >> cmd) {
		if (cmd == "IH") {//�bhead�B���J�@��node
			cin >> data;
			L.InsertHead(data);
        }
		else if (cmd == "IT") {//�btail�B���J�@��node
			cin >> data;
			L.InsertTail(data);
        }
		else if (cmd == "RH") {//��head�ƭȦL�X�A�H��R���o��node
            try {
				cout << L.RemoveHead() << endl;
            } 
			catch (const out_of_range &e) {
				cout << endl;
            }
        } 
		else if (cmd == "RT") {//��tail�ƭȦL�X�A�H��R���o��node
            try {
				cout << L.RemoveTail() << endl;
            } 
			catch (const out_of_range &e) {
				cout << endl;
            }
        } 
		else if (cmd == "S") L.Swap();
    }

	system("pause");
}
