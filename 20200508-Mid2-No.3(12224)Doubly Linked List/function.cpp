//�O�o���C++11�A�_�hnullptr�|�ɭPCompile Error
#include "function.h"

void List::InsertHead(int data) {
	int original_len = getSize();
	
	if (original_len == 0) head = middle = tail = new ListNode(data);
	else {
		ListNode *temp = new ListNode(data);

		temp->next = head;
		head->prev = temp;
		head = temp;

		//���@middle
		if (original_len % 2 == 0)middle = middle->prev;
	}

	//�O�o���@pos�Mcount��ӭ��n���Ʀr
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

		//���@middle
		if (list_len % 2 == 1)middle = middle->next;
	}

	//�O�o���@pos�Mcount��ӭ��n���Ʀr
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

		//���@middle
		if (original_len % 2 == 1)middle = middle->next;	
	}

	//�O�o���@pos�Mcount��ӭ��n���Ʀr
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
		

		//���@middle
		if (list_len % 2 == 0)middle = middle->prev;
	}

	//�O�o���@pos�Mcount��ӭ��n���Ʀr
	cnt--;
	pos = (cnt) ? cnt / 2 + 1 : 0;
	
	return original_tail_val;
}


void List::Swap() {
	int list_len = getSize();

	if (list_len == 0 || list_len == 1)return;
	//�p�G�쥻���׬O1�A���]���Φ�Ӧ�h�⦣�}�áA�]���⦣�}�ë᪺���G�M���⦣�}�ìۦP
	//�p�G�쥻���׬O0�A���N�S���F��i�H��Ӧ�h�⦣�}��

	ListNode *former_head = head, *former_tail = tail;//������@middle�ɷ|�Ψ�

	head->prev = tail;
	tail->next = head;
	head = middle;
	tail = head->prev;
	head->prev = nullptr;
	tail->next = nullptr;

	//�H�U�A�O�o�]�n���@middle����m�A�_�h�p�G�@�s��S�BS�BS...���O�U�h�A�|RE
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