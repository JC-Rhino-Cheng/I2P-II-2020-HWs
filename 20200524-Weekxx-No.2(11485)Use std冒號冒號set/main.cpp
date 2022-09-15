#include <vector>
#include <set>
#include <iostream>
#include  <string>
#include <algorithm>
using namespace  std;

int getValue(const vector<int>&vec);
vector<int> readVector(void);
void OutputVector(const vector<int>&vec);

struct Cmp {
	bool operator()(const vector<int>&lhs,const vector<int>&rhs)const {
		return getValue(lhs) < getValue(rhs);
	}
};


int main() {
	set <vector<int>, Cmp>s;

	string cmd;
	while (cin >> cmd) {
		if (cmd == "insert") {
			vector<int> temp = readVector();

			for (const auto &i : s) {//因為如果找到刪除目標並且刪除之後，就會跳出for-loop，所以可以使用range-based，反正刪除過後就會跳出去，所以不用怕無法抓取到下一個iterator的問題。因此沒有這次作業的另一題: use std::map的煩惱
				if (getValue(i) == getValue(temp)) {
					cout << "exist\n";
					s.erase(i);
					reverse(temp.begin(), temp.end());//原來有這種超好用function!!!定義在#include <algorithm>裡面。!!!不能用cbegin!!!不然你就不能reverse了
					break;
				}
			}

			s.insert(temp);
		}
		else if (cmd == "range_out") {
			const auto min_bound = getValue(readVector());
			const auto MAX_bound = getValue(readVector());

			for (const auto &i : s) {
				if (getValue(i) >= min_bound && getValue(i) <= MAX_bound) OutputVector(i);
				if (getValue(i) > MAX_bound)break;
			}
		}
		else if (cmd == "output") {
			for (const auto &i : s) OutputVector(i);
		}
	}

	system("pause");
}


int getValue(const vector<int>&vec) {
	int val = 0;
	int size = vec.size();
	for (const auto &i : vec) {//range-based的for-loop會自動抓取「數值」!!ex: vec裡面依序是"5、3、1、2、9"，則這裡的i就會依序是5、3、1、2、9，而非0、1、2、3、4或者1、2、3、4、5。
		val += i * size;
		size--;
	}

	return val;
}

vector<int> readVector(void) {
	vector<int>temp;
	int num_in;
	while (cin >> num_in) {
		if (num_in == 0)break;
		else temp.push_back(num_in);
	}

	return temp;
}


void OutputVector(const vector<int>&vec) {
	for (const auto &i : vec) cout << i << ' ';

	cout << endl;

	return;
}