#include "function.h"
#pragma warning (disable: 4996)

namespace oj {
	void Vector::pop_back() {
		if (size() > 0)last_--;//��last_�o�ӧ@��cursor���O���A���e�@��
	}


	void Vector::push_back(value_type val) {
		if (size() == capacity()) {//�p�G�ثe���}�C���פw�g�������F�A�b�ڭn�s�W�@�ӷs���Ʀr��}�C���ݤ��e�A���ӥ���}�C���ק˦n
			size_type new_capacity = ((capacity() + 1 > capacity() * 3) ? capacity() + 1 : capacity() * 3);
			reserve(new_capacity);
		}

		*last_ = val;
		last_++;//�o��M�W�檺�����ۦP��: a[count++]=b;�A�u���L�]���{�b�O��last_�o�ӫ��Ч@��cursor�A�ҥH�~�g���o��
	}


	void Vector::reserve(size_type new_capacity) {
		size_type old_size = size();

		if (new_capacity > capacity()) {//�u���bnew_capacity�T��O��{�b��capacity�ӱo�j���ɭԡA�~�ݭn���o��Ʊ��C���p�G�u�����`�apush��pop���ܡA�O���ΦҼ{�o�Ӫ��A���]���U�ЬG�N�s�W�F�@�ث��O�N�����z�A�n���n�i��reserve�A�ҥH�o�n�h�[�o�ӧP�_��
			Int *new_begin = new Int[new_capacity];//����g��Int *new_begin = new Int[new_capacity](0);�A�]��Int�O��Class�CClass����l�ƻݭn�浹constructor�B�z�C

			for (Int i = 0; i < size(); i++) //�}�l�h�E
				new_begin[i] = begin_[i];
			delete[] begin_;

			//�]�w�s��last_�Mend_�����Ц�m�A�åB��{�b��new_begin���x�s�����Ш��N���쥻��begin_
			end_ = new_begin + new_capacity;
			last_ = new_begin + old_size;
			begin_ = new_begin;
		}

	}


	Vector::~Vector() {
		delete[] begin_;//begin_�O�ӫ��СA�ӥB�O��new�˥X�Ӫ��A�ҥH�o�˼g
	}
}
/*
Note:

namespace oj {
	void Vector::pop_back() {	}
	void Vector::push_back(value_type val) {	}
	void Vector::reserve(size_type new_capacity) {	}
	Vector::~Vector() {	}
}

�]�i�g�@:
void oj::Vector::pop_back() {	}
void oj::Vector::push_back(value_type val) {	}
void oj::Vector::reserve(size_type new_capacity) {	}
oj::Vector::~Vector() {	}
*/