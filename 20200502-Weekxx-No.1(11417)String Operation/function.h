#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
using namespace std;

class Char{
	friend class Str;
	private:
		Char(char text) :next(NULL), text(text) {}//�u�|�Ψ�o��constructor�A�ҥH�N����default constructor�F

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
		Str() :head(NULL), tail(NULL) {}//default constructor�A���|�Ψ�
		Str(char*); // ��linked list���覡�Ы�Str�C�C��node�̭����u�x�s�@��char
		Str(const Str &); // copy constructor

		~Str() {
			if (head) delete head;//�]��head�OChar�A�ҥH�|�I�sChar-class��destructor�C�S�AChar-class��destructor�|�H���j���覡�q�̫᭱���e��Ҧ�node�R��
		}

		Str& strInsert(const Str &);

		Str& strSwap(Str &s) {//�ǻ��i�Ӫ��Opass-by-reference!!!
			Str *tmp = new Str(*this);//this�O�@��object�����СA�ҥH*this�O�@��object�C�ҥH�o�̬O��copy constructor
			this->~Str();

			*this = s;//�o!!!���|!!!�Ψ�copy constructor�C�Ш�Operator Overloading����35���C
			s = *tmp;//��tmp���Щҫ���object�A�ƻs��s reference��alias��object�C�ҥH�o!!!���|!!!�O�@��copy constructor�C//�`�N�Atemp���Щ|�������A�ӥB�O�ڭ̤��A�ݭn��object������

			tmp->head = NULL;
			delete tmp;
			return *this;//���Fcascaded�Ӧ^��reference
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
