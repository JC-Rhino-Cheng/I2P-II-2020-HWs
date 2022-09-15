#include "function.h"
#pragma warning (disable: 4996)

namespace oj {
	void Vector::pop_back() {
		if (size() > 0)last_--;//把last_這個作為cursor的記號，往前一格
	}


	void Vector::push_back(value_type val) {
		if (size() == capacity()) {//如果目前的陣列長度已經完全滿了，在我要新增一個新的數字到陣列尾端之前，應該先把陣列長度弄好
			size_type new_capacity = ((capacity() + 1 > capacity() * 3) ? capacity() + 1 : capacity() * 3);
			reserve(new_capacity);
		}

		*last_ = val;
		last_++;//這行和上行的概念相同於: a[count++]=b;，只不過因為現在是用last_這個指標作為cursor，所以才寫成這樣
	}


	void Vector::reserve(size_type new_capacity) {
		size_type old_size = size();

		if (new_capacity > capacity()) {//只有在new_capacity確實是比現在的capacity來得大的時候，才需要做這件事情。其實如果只有正常地push或pop的話，是不用考慮這個的，但因為助教故意新增了一種指令就直接干涉要不要進行reserve，所以得要多加這個判斷式
			Int *new_begin = new Int[new_capacity];//不能寫成Int *new_begin = new Int[new_capacity](0);，因為Int是個Class。Class的初始化需要交給constructor處理。

			for (Int i = 0; i < size(); i++) //開始搬遷
				new_begin[i] = begin_[i];
			delete[] begin_;

			//設定新的last_和end_的指標位置，並且把現在的new_begin所儲存的指標取代掉原本的begin_
			end_ = new_begin + new_capacity;
			last_ = new_begin + old_size;
			begin_ = new_begin;
		}

	}


	Vector::~Vector() {
		delete[] begin_;//begin_是個指標，而且是用new弄出來的，所以這樣寫
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

也可寫作:
void oj::Vector::pop_back() {	}
void oj::Vector::push_back(value_type val) {	}
void oj::Vector::reserve(size_type new_capacity) {	}
oj::Vector::~Vector() {	}
*/