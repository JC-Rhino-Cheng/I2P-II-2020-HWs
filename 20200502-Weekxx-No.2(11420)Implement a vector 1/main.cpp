/*
begin_ (是個Int*)用來標示vector的頭，同時也作為用來動態規劃記憶體的標的
last_ (是個Int*)用來標示vector中最後一筆資料"後面一個"位置，基本上就是作為cursor判斷push和pop的位置
end_ (是個Int*)用來標示vector的尾
size() 和 capacity() 分別是利用 (last_-begin_) 和 (end_-begin_) 去求 vector 的 size 和 capacity
value_type 是 Int 的別稱, size_type 是 size_t 的別稱
*/


#include<iostream>
#include<string>
#include"function.h"
#ifdef ONLINE_JUDGE
#include"NTHUOJLock"
#endif
#pragma warning (disable: 4996)

namespace oj {
	Int::Int() :val(0) {}	//default constructor，把Int的val預設為0。
	Int::Int(const int val_) : val(val_) {}
	Int::Int(const Int &rhs) : val(rhs.val) {}	//copy constructor。從rhs.val把值複製出來。

	Int& Int::operator=(const Int &rhs) {//Operator Overloading，賦予'='新意義
		val=rhs.val;
		return *this;//開啟cascaded的功能
	}

	Vector::Vector() :begin_(NULL), end_(NULL), last_(NULL) {}

	std::ostream& operator<<(std::ostream &os, const Vector &vec) {//Operator Overloading，賦予'<<'新意義，但我看不懂
		for (std::size_t i(0); i != vec.size(); ++i) os << vec[i] << ' ';
		return os;
	}
}

int main() {
	using namespace std;
	{
		oj::Vector v;
		string command;

		for (oj::data_t n; cin >> command;) {//data_t是Int的別稱(我猜)
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
	oj::memory_leak_count_check();	//助教說不用管這個
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