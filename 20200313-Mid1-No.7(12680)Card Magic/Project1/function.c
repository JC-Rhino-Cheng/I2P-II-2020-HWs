#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "function.h"
#define max(a, b) ( ( a > b ) ? a : b )
#define min(a, b) ( ( a < b ) ? a : b )
#pragma warning (disable: 4996)

Node *createNode(int);

Node *createNode(int N) {
	Node *temp = (Node *) malloc ( sizeof(Node) );
	temp->size = N;
	temp->data = (int *) malloc ( sizeof(int)*N );
	temp->next = NULL;

	return temp;
}


Node *ReadOneList(void) {
	int N; scanf("%d:", &N);

	Node *temp = createNode(N);
	for (int i = 0; i < N; i++) scanf("%d", &temp->data[i]);

	return temp;
}


void Merge(Node *temp, int from_idx, int to_idx) {
	if (from_idx == to_idx)return;

	int bigger_idx = max(from_idx, to_idx); Node *bigger_idx_node_prev = NULL;
	int smaller_idx = min(from_idx, to_idx); Node *smaller_idx_node_prev = NULL;

	for (int i = 0; i < bigger_idx; i++) {
		if (smaller_idx - 1 == i) { smaller_idx_node_prev = temp; }
		else if (bigger_idx - 1 == i) { bigger_idx_node_prev = temp; }

		temp = temp->next;
	}

	Node *from_node_prev = (from_idx == bigger_idx) ? bigger_idx_node_prev : smaller_idx_node_prev;
	Node *to_node_prev = (to_idx == bigger_idx) ? bigger_idx_node_prev : smaller_idx_node_prev;
	Node *from = from_node_prev->next;
	Node *to = to_node_prev->next;


	int from_len = from_node_prev->next->size;
	int to_len = to_node_prev->next->size;
	int new_len = from_len + to_len;

	Node *New = createNode(new_len);
	for (int i = 0; i < to_len; i++) {
		New->data[i] = to_node_prev->next->data[i];
	}
	for (int i = 0; i < from_len; i++) {
		New->data[i + to_len] = from_node_prev->next->data[i];
	}

	
	//開始變更連結
	//注意三種不同狀況
	if (from_node_prev == to) {
		to_node_prev->next = New;
		New->next = from->next;
	}
	else if (to_node_prev == from) {
		from_node_prev->next = New;
		New->next = to->next;
	}
	else {
		to_node_prev->next = New;
		New->next = to->next;
		from_node_prev->next = from->next;
	}

	free(from->data);
	free(from);
	free(to->data);
	free(to);

	return;
}


void Cut(Node *temp, int node_idx, int length_remaining) {
	Node *goal_node_prev = NULL; Node *goal_node = NULL;
	for (int i = 0; i < node_idx; i++) {
		if (i == node_idx - 1)goal_node_prev = temp;

		temp = temp->next;
	}
	goal_node = goal_node_prev->next;

	int former_length = length_remaining;
	int latter_length = goal_node_prev->next->size - former_length;

	Node *latter = createNode(latter_length);
	Node *former = createNode(former_length);

	for (int i = 0; i < former_length; i++) {
		former->data[i] = goal_node_prev->next->data[i];
	}
	for (int i = 0; i < latter_length; i++) {
		latter->data[i] = goal_node_prev->next->data[i + former_length];
	}

	latter->next = goal_node_prev->next->next;
	former->next = latter;
	goal_node_prev->next = former;

	free(goal_node->data);
	free(goal_node);

	return;
}

void PrintList(Node *temp) {
	while (temp != NULL) {
		if (temp->size != -1) {
			for (int i = 0; i < temp->size; i++) {
				if (i != temp->size - 1)printf("%d ", temp->data[i]);
				else printf("%d\n", temp->data[i]);
			}
		}
		temp = temp->next;
	}
}