#ifndef FUNCTION_H
#define FUNCTION_H
#include<cstddef>
#include<iosfwd>
#pragma warning (disable: 4996)

namespace oj{
	class Memory_leak_count {//check whether the process has memory leak
		friend void memory_leak_count_check();
		static unsigned count_;
	public:
		Memory_leak_count();
		~Memory_leak_count();
	};

	struct Int {	//助教說可以把Int視為int
		int val;	//store int in val, you this val//什麼意思沒看懂

		Int();
		Int(int val);
		Int(const Int &);//copy constructor
		Int& operator=(const Int &);//Operator Overloading，賦予'='新意義

		operator int&() {	//treat Int as int, conversion function
			return val;
		}
		operator int() const {	//treat Int as int, conversion function
			return val;
		}
		
	private:
		Memory_leak_count count_;//助教說不用管這個
	};

	typedef Int data_t;//data_t是Int的別稱(我猜)

	class Vector {
	public:
		typedef std::size_t size_type;//size_type 是size_t的別稱(我猜)
		typedef Int value_type;//value_type是Int的別稱
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type* pointer;//value_type* 是pointer的別稱
		typedef const value_type *const_pointer;
	private:
		pointer begin_;//begin of array
		pointer end_;//end of array
		pointer last_;//end of current element
	public:
		Vector();
		inline size_type capacity() const {//計算目前array到底挖了多少記憶體出來
			return end_ - begin_;
		}
		inline size_type size() const {//計算目前array中，實際被占用的空間個數
			return last_ - begin_;
		}
		//ignore the keyword "inline"
		//operator[] makes Vector like a C-array, for example    //int a[2]{2,1};
		//相當於
		//Vector vec;
		//vec.push_back(2);
		//vec.push_back(1);

		//vec[0] is equal to a[0]
		//vec[1] is equal to a[1]
		inline reference operator[](const size_type pos) {
			return begin_[pos];
		}
		inline const_reference operator[](const size_type pos) const {
			return begin_[pos];
		}
		
		void pop_back();
		void push_back(value_type val);
		
		void reserve(size_type new_capacity);
		
		~Vector();
	};

	std::ostream& operator<<(std::ostream &os, const Vector &vec);	//for cout

	void memory_leak_count_check();	//助教說不用管這個
}

#endif