#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "function.h"
#define max(a, b) ( ( a > b ) ? a : b )
#define min(a, b) ( ( a < b ) ? a : b )
#pragma warning (disable: 4996)

Node *ReadOneList(void) {
	int N; scanf("%d:", &N);
	int *data = (int *) malloc ( sizeof(int)*N );
	for (int i = 0; i < N; i++)scanf("%d", &data[i]);

	Node *temp = (Node *) malloc ( sizeof(Node) );
	temp->size = N;
	temp->data = data;
	temp->next = NULL;

	return temp;
}



void Merge(Node *temp, int from_idx, int to_idx) {
	int bigger_idx = max(from_idx, to_idx); Node *bigger_idx_node_prev = NULL;
	int smaller_idx = min(from_idx, to_idx); Node *smaller_idx_node_prev = NULL;

	for (int i = 0; i < bigger_idx; i++) {
		if (smaller_idx - 1 == i) { smaller_idx_node_prev = temp;}
		else if (bigger_idx - 1 == i) { bigger_idx_node_prev = temp; }

		temp = temp->next;
	}

	Node *from_node_prev = (from_idx == bigger_idx) ? bigger_idx_node_prev : smaller_idx_node_prev;
	Node *to_node_prev = (to_idx==bigger_idx)? bigger_idx_node_prev : smaller_idx_node_prev;

	int new_size = from_node_prev->next->size + to_node_prev->next->size;
	int *new_data = (int *) malloc ( sizeof(int)*new_size );
	memcpy(new_data, to_node_prev->next->data, sizeof(to_node_prev->next->data));
	memcpy(new_data + to_node_prev->next->size, from_node_prev->next->data, sizeof(from_node_prev->next->data));

	free(to_node_prev->next->data);
	to_node_prev->next->data = new_data;

	free(from_node_prev->next->data);
	from_node_prev->next = from_node_prev->next->next;
	free(from_node_prev->next);

	return;
}


void Cut(Node *temp, int node_idx, int length_remaining) {
	Node *goal_node = NULL;
	for (int i = 0; i <= node_idx; i++) {
		if (i == node_idx)goal_node = temp;

		temp = temp->next;
	}

	int former_length = length_remaining;
	int latter_length = goal_node->size - former_length;

	int *former_data = (int *) malloc ( sizeof(int) *former_length );
	int *latter_data = (int *) malloc ( sizeof(int)*latter_length );
	memcpy(former_data, goal_node->data, sizeof(goal_node->data));
	memcpy(latter_data, (goal_node->data) + former_length, sizeof(int)*latter_length);

	free(goal_node->data);
	goal_node->size = former_length;
	goal_node->data = former_data;

	Node *New = (Node *) malloc ( sizeof(Node) );
	New->size = latter_length;
	New->data = latter_data;
	New->next = goal_node->next;
	goal_node->next = New;

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
		temp = temp->size;
	}
}

//錯誤檢討:
//1.除了有prev以外，也要有本尊的。又因為分為x和y，所以總共需要Node *共2x2=4個。
//2.在我week02時，因為是採用直接合併法，所以只free掉一個Node，所牽涉到的Node的連結沒有那麼多，所以沒有注意到新版(正確版function.h)的line63~line77的三種狀況。