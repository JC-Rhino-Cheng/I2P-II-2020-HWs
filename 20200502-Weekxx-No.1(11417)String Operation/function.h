#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
using namespace std;

class Char{
	friend class Str;
	private:
		Char(char text) :next(NULL), text(text) {}//只會用到這個constructor，所以就不管default constructor了

		~Char() {
			if (next) delete next;
		}

		void print(void) {
			cout << text;
			if (next) next->print();
		}

		char text;
		Char *next;
};

class Str{
	public:
		Str() :head(NULL), tail(NULL) {}//default constructor，不會用到
		Str(char*); // 用linked list的方式創建Str。每個node裡面都只儲存一個char
		Str(const Str &); // copy constructor

		~Str() {
			if (head) delete head;//因為head是Char，所以會呼叫Char-class的destructor。又，Char-class的destructor會以遞迴的方式從最後面往前把所有node刪除
		}

		Str& strInsert(const Str &);

		Str& strSwap(Str &s) {//傳遞進來的是pass-by-reference!!!
			Str *tmp = new Str(*this);//this是一個object的指標，所以*this是一個object。所以這裡是用copy constructor
			this->~Str();

			*this = s;//這!!!不會!!!用到copy constructor。請見Operator Overloading的第35頁。
			s = *tmp;//把tmp指標所指的object，複製給s reference所alias的object。所以這!!!不會!!!是一個copy constructor。//注意，temp指標尚未消失，而且是我們不再需要的object的指標

			tmp->head = NULL;
			delete tmp;
			return *this;//為了cascaded而回傳reference
		}

		void strPrint() {
			if (head) head->print();
			cout << endl;
		}

	private:
		Char *head;
		Char *tail;
};

#endif
