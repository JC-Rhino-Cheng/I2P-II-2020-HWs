//記得選擇C++11，否則nullptr會導致Compile Error
#include "function.h"

void List::InsertHead(int data) {
	int original_len = getSize();
	
	if (original_len == 0) head = middle = tail = new ListNode(data);
	else {
		ListNode *temp = new ListNode(data);

		temp->next = head;
		head->prev = temp;
		head = temp;

		//維護middle
		if (original_len % 2 == 0)middle = middle->prev;
	}

	//記得維護pos和count兩個重要的數字
	cnt++;
	pos = (cnt) ? cnt / 2 + 1 : 0;
}


int  List::RemoveHead() {
	int list_len = getSize();
	if (list_len == 0)throw std::out_of_range("");

	int original_head_val = head->data;
	if (list_len == 1) {
		delete head;
		head = middle = tail = nullptr;
	}
	else {
		ListNode *to_be_deleted = head;

		head = head->next;
		head->prev = nullptr;

		//維護middle
		if (list_len % 2 == 1)middle = middle->next;
	}

	//記得維護pos和count兩個重要的數字
	cnt--;
	pos = (cnt) ? cnt / 2 + 1 : 0;
	
	return original_head_val;
}


void List::InsertTail(int data) {
	int original_len = getSize();

	if (original_len == 0) head = middle = tail = new ListNode(data);
	else {
		ListNode *temp = new ListNode(data);

		tail->next = temp;
		temp->prev = tail;
		tail = temp;

		//維護middle
		if (original_len % 2 == 1)middle = middle->next;	
	}

	//記得維護pos和count兩個重要的數字
	cnt++;
	pos = (cnt) ? cnt / 2 + 1 : 0;
}


int  List::RemoveTail() {
	int list_len = getSize();
	if (list_len == 0)throw std::out_of_range("");

	int original_tail_val = tail->data;
	if (list_len == 1) {
		delete tail;
		head = middle = tail = nullptr;
	}
	else {
		ListNode *to_be_deleted = tail;

		tail = tail->prev;
		tail->next = nullptr;
		

		//維護middle
		if (list_len % 2 == 0)middle = middle->prev;
	}

	//記得維護pos和count兩個重要的數字
	cnt--;
	pos = (cnt) ? cnt / 2 + 1 : 0;
	
	return original_tail_val;
}


void List::Swap() {
	int list_len = getSize();

	if (list_len == 0 || list_len == 1)return;
	//如果原本長度是1，那也不用串來串去手忙腳亂，因為手忙腳亂後的結果和不手忙腳亂相同
	//如果原本長度是0，那就沒有東西可以串來串去手忙腳亂

	ListNode *former_head = head, *former_tail = tail;//之後維護middle時會用到

	head->prev = tail;
	tail->next = head;
	head = middle;
	tail = head->prev;
	head->prev = nullptr;
	tail->next = nullptr;

	//以下，記得也要維護middle的位置，否則如果一連串S、S、S...指令下去，會RE
	if (list_len % 2 == 1)middle = former_tail;
	else middle = former_head;

	return;
}


int  List::getSize() {
	return cnt;
}


int  List::getMiddle() {
	return pos;
}