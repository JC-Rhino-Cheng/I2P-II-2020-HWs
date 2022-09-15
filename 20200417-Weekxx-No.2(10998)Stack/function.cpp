#include "function.h"
#include <iostream>
#pragma warning (disable: 4996)

List_stack :: List_stack() { this->head = this->tail = NULL; }//Constructor先把head和tail設為NULL
List_stack :: ~List_stack() {}//Destructor啥都不用幹


void List_stack :: push(const int &n) {
	ListNode *temp = new ListNode(n);//注意: 記得如果是動態記憶體，要這樣宣告

	if (this->tail != NULL) {//如果這個stack已經有東西了，不是完全空的
		temp->prevPtr = this->tail;//line13和line14是把現在的temp和即將失去tail身分的目前的tail串接起來
		this->tail->nextPtr = temp;
		this->tail = temp;//把tail改成temp
	}
	else {//如果這個stack完全沒有東西
		this->head = this->tail = temp;
	}
	
	return;
}


void List_stack :: pop() {
	if (this->tail == NULL)return;//如果這個Stack根本沒東西

	if (this->tail->prevPtr != NULL) {//如果這個Stack的東西不只一個
		this->tail = this->tail->prevPtr;
		delete this->tail->nextPtr;
		this->tail->nextPtr = NULL;
	}
	else {//如果這個Stack的東西只有一個
		delete this->tail;

		this->head = this->tail = NULL;
	}

	return;
}


void List_stack :: print() {
	ListNode* temp = this->tail;

	while (temp != NULL) {
		if (temp->prevPtr != NULL) std::cout << temp->data << " ";
		else std::cout << temp->data; 
		temp = temp->prevPtr;
	}

	return;
}