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

	struct Int {	//�U�л��i�H��Int����int
		int val;	//store int in val, you this val//����N��S����

		Int();
		Int(int val);
		Int(const Int &);//copy constructor
		Int& operator=(const Int &);//Operator Overloading�A�ᤩ'='�s�N�q

		operator int&() {	//treat Int as int, conversion function
			return val;
		}
		operator int() const {	//treat Int as int, conversion function
			return val;
		}
		
	private:
		Memory_leak_count count_;//�U�л����κ޳o��
	};

	typedef Int data_t;//data_t�OInt���O��(�ڲq)

	class Vector {
	public:
		typedef std::size_t size_type;//size_type �Osize_t���O��(�ڲq)
		typedef Int value_type;//value_type�OInt���O��
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type* pointer;//value_type* �Opointer���O��
		typedef const value_type *const_pointer;
	private:
		pointer begin_;//begin of array
		pointer end_;//end of array
		pointer last_;//end of current element
	public:
		Vector();
		inline size_type capacity() const {//�p��ثearray�쩳���F�h�ְO����X��
			return end_ - begin_;
		}
		inline size_type size() const {//�p��ثearray���A��ڳQ�e�Ϊ��Ŷ��Ӽ�
			return last_ - begin_;
		}
		//ignore the keyword "inline"
		//operator[] makes Vector like a C-array, for example    //int a[2]{2,1};
		//�۷��
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

	void memory_leak_count_check();	//�U�л����κ޳o��
}

#endif