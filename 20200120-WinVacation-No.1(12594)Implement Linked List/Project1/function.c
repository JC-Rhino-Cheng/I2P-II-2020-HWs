#include <stdlib.h>
#include "function.h"
#pragma warning (disable: 4996)
#define max(a,b) ((a>b)?a:b)

Node* createList(int *a, int size) {
	Node *head = NULL;
	Node *previous = NULL;
	for (int i = 0; i < size; i++) {
		Node *temp = (Node *) malloc ( sizeof(Node) );
		temp->data = a[i];

		if (i == 0) {
			head = temp;
			previous = temp;
		}
		else {
			previous->next = temp;
			previous = temp;
		}
	}previous->next = NULL;

	return head;
}


Node* copyList(Node* head) {
	if (head == NULL)return NULL;

	Node *original_head = head, *new_head = NULL;
	Node *original_temp = head, *new_temp = NULL;
	Node *original_previous = NULL, *new_previous = NULL;

	for (int i = 0; original_temp->next != NULL; i++) {
		new_temp = (Node *) malloc ( sizeof(Node) );
		new_temp->data = original_temp->data;

		if (i == 0) {
			new_previous = new_temp;
			new_head = new_temp;
		}
		else {
			new_previous->next = new_temp;
			new_previous = new_temp;
		}
		original_temp = original_temp->next;
	}

	new_temp = (Node *) malloc ( sizeof(Node) );
	new_temp->data = original_temp->data;
	new_previous->next = new_temp;
	new_temp->next = NULL;

	return new_head;
}


void push_front(Node** head, int val) {
	Node *temp = (Node *) malloc ( sizeof(Node) );
	temp->data = val;
	temp->next = *head;

	*head = temp;
	return;
}


void deleteElementByIdx(Node** head, int idx) {
	if (idx < 0)return;

	Node *temp = *head;
	Node *temp_previous = NULL;
	for (int i = 0; temp != NULL; i++) {
		if (i == idx) {
			if (idx == 0) {
				temp_previous = head;
				*head = temp->next;
				free(temp_previous);
				return;
			}
			else {
				temp_previous->next = temp->next;
				free(temp);
				return;
			}
		}
		else {
			temp_previous = temp;
			temp = temp->next;
		}
	}
	return;
}


void SwapElementByIdx(Node** head, int idx1, int idx2) {
	if (idx1 < 0 || idx2 < 0) return;

	int idx_big = max(idx1, idx2);
	int idx_small = (idx_big == idx1) ? idx2 : idx1;

	Node *temp = *head;
	Node *small = NULL, *big = NULL;

	for (int i = 0; temp != NULL; i++) {
		if (i == idx_small) small = temp;
		else if (i == idx_big) {
			big = temp;

			int temp_of_exchanging_num = small->data;
			small->data = big->data;
			big->data = temp_of_exchanging_num;
			break;
		}
		temp = temp->next;
	}
	return;
}