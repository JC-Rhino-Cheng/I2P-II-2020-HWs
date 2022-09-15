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
		if (cmd == "IH") {//在head處插入一個node
			cin >> data;
			L.InsertHead(data);
        }
		else if (cmd == "IT") {//在tail處插入一個node
			cin >> data;
			L.InsertTail(data);
        }
		else if (cmd == "RH") {//把head數值印出，隨後刪除這個node
            try {
				cout << L.RemoveHead() << endl;
            } 
			catch (const out_of_range &e) {
				cout << endl;
            }
        } 
		else if (cmd == "RT") {//把tail數值印出，隨後刪除這個node
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
