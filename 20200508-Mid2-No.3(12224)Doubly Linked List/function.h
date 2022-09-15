#ifndef function_h
#define function_h

#include <iostream>
#pragma warning (disable: 4996)

class ListNode{
private:
	int data;
	ListNode *next;
	ListNode *prev;
public:
	ListNode() :data(0), next(nullptr), prev(nullptr) {}//default constructor
	ListNode(int a) :data(a), next(nullptr), prev(nullptr) {}//constructor

	friend class List;
};


class List{
private:
	ListNode* head;
	ListNode* tail;
	ListNode* middle;
	int       cnt;   //�p��linked list������
	int       pos;   //middle��pos

	void reset() {
		head = nullptr;
		tail = nullptr;
		middle = nullptr;
		cnt = 0;
		pos = 0;
    }

	//�ڷ|�R�W��ListDestruction���F��A�U�ЩR�W��clean
	void clean() {
		ListNode* temp;
		while (head != nullptr) {
			temp = head;
			head = head->next;
			delete temp;
        }
    }

public:
    // constructor and destructor
	List() {
		reset();
    }
	~List() {
		clean();
    }

	void InsertHead(int data);
	int  RemoveHead();
	void InsertTail(int data);
	int  RemoveTail();
	void Swap();
	int  getSize();
	int  getMiddle();

};

#endif /* function_h */
