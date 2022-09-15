#include <stdlib.h>
#include <string.h>
#include "function.h"
#pragma warning (disable: 4996)

extern Node* head;

Node* createList(int n) {
	Node *fake_head = (Node *) malloc( sizeof(Node) );//�ڱĥ����� reurl.cc/yZEjAy���AImplement3���覡�C�o��head�N�Odummy�A����|�R���A�M���b�o��head�᭱���u����head�A�Mtail�s���b�@�_�A�Φ��@�����C
	fake_head->number = 0;

	Node* temp_previous = fake_head;//�o��"temp_previous"�W�r�A�|�b�U����for�j�骺temp�Ψ�C

	for (int i = 1; i <= n; i++) {
		Node *temp = (Node *) malloc( sizeof(Node) );

		temp->number = i;
		temp->prev = temp_previous;
		temp_previous->next = temp;

		temp_previous = temp;
	}

	temp_previous->next = fake_head->next;
	fake_head->next->prev = temp_previous;

	return fake_head->next;
}


void freeList() {
	return;
}


int solveJosephus(int step) {
	Node * currentNode = head;
	int count = 1;//step�O�x�s�쩳�X�B�~���H�C��count�O�Ψӭp��쩳���S����Fstep�C����: step�|�b�{���̭��T�w���ܡA��count�|�@���ܰʡC
	int flag_is_clockwise = 1;//�x�s�쩳�O������?�٬O�f����?1���������C0���f�����C

	while (currentNode->next != currentNode) {
		if (count != step) {
			if (flag_is_clockwise) {
				count++;
				currentNode = currentNode->next;
			}
			else {
				count++;
				currentNode = currentNode->prev;
			}
		}
		else {
			count = 1;

			currentNode->prev->next = currentNode->next;
			currentNode->next->prev = currentNode->prev;

			Node *temp_for_deleting = currentNode;
			if (flag_is_clockwise) currentNode = currentNode->prev;
			else currentNode = currentNode->next;
			free(temp_for_deleting);

			flag_is_clockwise = !flag_is_clockwise;
		}
	}

	int index_of_survivor = currentNode->number;
	free(currentNode);
	return index_of_survivor;
}