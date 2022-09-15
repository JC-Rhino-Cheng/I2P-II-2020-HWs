#include <stdlib.h>
#include <string.h>
#include "function.h"
#pragma warning (disable: 4996)

extern Node* head;

Node* createList(int n) {
	Node *fake_head = (Node *) malloc( sizeof(Node) );//我採用類似 reurl.cc/yZEjAy中，Implement3的方式。這個head就是dummy，之後會刪掉，然後把在這個head後面的真正的head，和tail連結在一起，形成一個環。
	fake_head->number = 0;

	Node* temp_previous = fake_head;//這個"temp_previous"名字，會在下面的for迴圈的temp用到。

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
	int count = 1;//step是儲存到底幾步才殺人。而count是用來計算到底有沒有到達step。結論: step會在程式裡面固定不變，而count會一直變動。
	int flag_is_clockwise = 1;//儲存到底是順時鐘?還是逆時鐘?1為順時鐘。0為逆時鐘。

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