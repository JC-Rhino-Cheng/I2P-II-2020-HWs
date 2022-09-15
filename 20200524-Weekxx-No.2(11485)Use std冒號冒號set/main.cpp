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

			for (const auto &i : s) {//�]���p�G���R���ؼШåB�R������A�N�|���Xfor-loop�A�ҥH�i�H�ϥ�range-based�A�ϥ��R���L��N�|���X�h�A�ҥH���ΩȵL�k�����U�@��iterator�����D�C�]���S���o���@�~���t�@�D: use std::map���дo
				if (getValue(i) == getValue(temp)) {
					cout << "exist\n";
					s.erase(i);
					reverse(temp.begin(), temp.end());//��Ӧ��o�ضW�n��function!!!�w�q�b#include <algorithm>�̭��C!!!�����cbegin!!!���M�A�N����reverse�F
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
	for (const auto &i : vec) {//range-based��for-loop�|�۰ʧ���u�ƭȡv!!ex: vec�̭��̧ǬO"5�B3�B1�B2�B9"�A�h�o�̪�i�N�|�̧ǬO5�B3�B1�B2�B9�A�ӫD0�B1�B2�B3�B4�Ϊ�1�B2�B3�B4�B5�C
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