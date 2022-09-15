/*
begin_ (�O��Int*)�ΨӼХ�vector���Y�A�P�ɤ]�@���ΨӰʺA�W���O���骺�Ъ�
last_ (�O��Int*)�ΨӼХ�vector���̫�@�����"�᭱�@��"��m�A�򥻤W�N�O�@��cursor�P�_push�Mpop����m
end_ (�O��Int*)�ΨӼХ�vector����
size() �M capacity() ���O�O�Q�� (last_-begin_) �M (end_-begin_) �h�D vector �� size �M capacity
value_type �O Int ���O��, size_type �O size_t ���O��
*/


#include<iostream>
#include<string>
#include"function.h"
#ifdef ONLINE_JUDGE
#include"NTHUOJLock"
#endif
#pragma warning (disable: 4996)

namespace oj {
	Int::Int() :val(0) {}	//default constructor�A��Int��val�w�]��0�C
	Int::Int(const int val_) : val(val_) {}
	Int::Int(const Int &rhs) : val(rhs.val) {}	//copy constructor�C�qrhs.val��Ƚƻs�X�ӡC

	Int& Int::operator=(const Int &rhs) {//Operator Overloading�A�ᤩ'='�s�N�q
		val=rhs.val;
		return *this;//�}��cascaded���\��
	}

	Vector::Vector() :begin_(NULL), end_(NULL), last_(NULL) {}

	std::ostream& operator<<(std::ostream &os, const Vector &vec) {//Operator Overloading�A�ᤩ'<<'�s�N�q�A���ڬݤ���
		for (std::size_t i(0); i != vec.size(); ++i) os << vec[i] << ' ';
		return os;
	}
}

int main() {
	using namespace std;
	{
		oj::Vector v;
		string command;

		for (oj::data_t n; cin >> command;) {//data_t�OInt���O��(�ڲq)
			if (command == "pop_back") {
				v.pop_back();
				cout << v << endl;
			}
			else if (command == "push_back") {
				cin >> n;
				v.push_back(n);
				cout << v << endl;
			}
			else if (command == "capacity")
				cout << v.capacity() << endl;
			else if (command == "size")
				cout << v.size() << endl;
			else if (command == "reserve") {
				cin >> n;
				v.reserve(n);
				cout << v << endl;
			}
		}
		cout << v << endl;

		system("pause");
	}
	oj::memory_leak_count_check();	//�U�л����κ޳o��
#ifdef ONLINE_JUDGE
	nthuoj_unlock();
#endif
}

namespace oj{
	Memory_leak_count::Memory_leak_count() {
		++count_;	//memory request + 1
	}

	Memory_leak_count::~Memory_leak_count() {
		--count_;	//memory request - 1
	}

	unsigned Memory_leak_count::count_(0);

	void memory_leak_count_check() {
		if (Memory_leak_count::count_ != 0)//memory leak if count_ is not equal to 0
			std::cout << "memory leak" << std::endl;
	}
}