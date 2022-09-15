#include "function.h"
#include <iostream>
#pragma warning (disable: 4996)

List_stack :: List_stack() { this->head = this->tail = NULL; }//Constructor����head�Mtail�]��NULL
List_stack :: ~List_stack() {}//Destructorԣ�����ηF


void List_stack :: push(const int &n) {
	ListNode *temp = new ListNode(n);//�`�N: �O�o�p�G�O�ʺA�O����A�n�o�˫ŧi

	if (this->tail != NULL) {//�p�G�o��stack�w�g���F��F�A���O�����Ū�
		temp->prevPtr = this->tail;//line13�Mline14�O��{�b��temp�M�Y�N���htail�������ثe��tail�걵�_��
		this->tail->nextPtr = temp;
		this->tail = temp;//��tail�令temp
	}
	else {//�p�G�o��stack�����S���F��
		this->head = this->tail = temp;
	}
	
	return;
}


void List_stack :: pop() {
	if (this->tail == NULL)return;//�p�G�o��Stack�ڥ��S�F��

	if (this->tail->prevPtr != NULL) {//�p�G�o��Stack���F�褣�u�@��
		this->tail = this->tail->prevPtr;
		delete this->tail->nextPtr;
		this->tail->nextPtr = NULL;
	}
	else {//�p�G�o��Stack���F��u���@��
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