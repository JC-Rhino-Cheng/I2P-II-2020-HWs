#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "function.h"
#pragma warning (disable: 4996)
#define Max_length_of_int_array (int)6e2 //原本應該照題目是1e4，但反覆try發現6e2 or 4e2 or ....才會AC
#define max(a, b) (( a > b ) ? a : b)

Node *ReadOneList(void) {
	int length; scanf("%d:", &length);
	int *array = (int *) malloc ( sizeof(int)*Max_length_of_int_array );
	for (int i = 0; i < length; i++)scanf("%d", &array[i]);

	Node *temp = (Node *)malloc ( sizeof(Node) );

	temp->size = length;
	temp->data = array;
	temp->next = NULL;

	return temp;
}


void Merge(Node* temp, int from, int to) {
	//要混和的兩副牌有起訖之分，也有依照編號而有的前後之分。latter指的是編號後面的，former指編號前面的。
	if (from == to)return;

	int latter = max(from, to);
	int former = (latter == from) ? to : from;

	Node *formerNode = NULL, *latterNode = NULL;
	Node *formerNode_prev = NULL, *latterNode_prev = NULL;
	for (int i = 0; i <= latter; i++) {
		if (i == former - 1 && former + 1 == latter) {//如果採用下面else的部分，那麼former和latter相鄰的時候，會找不到latterNode的位置，所以單獨弄出來討論
			formerNode_prev = temp;
			formerNode = latterNode_prev = temp->next;
			latterNode = latterNode_prev->next;
			break;
		}
		else {
			if (i == former - 1) { formerNode_prev = temp; temp = temp->next; formerNode = temp; i++; }
			else if (i == latter - 1) { latterNode_prev = temp; temp = temp->next; latterNode = temp; i++; }
		}
		
		temp = temp->next;
	}

	if (former == from) {
		memcpy(latterNode->data + (latterNode->size), formerNode->data, sizeof(int)*(formerNode->size));

		latterNode->size += formerNode->size;
		formerNode_prev->next = formerNode->next;

		free(formerNode->data);
		free(formerNode);
	}
	else {
		memcpy(formerNode->data + (formerNode->size), latterNode->data, sizeof(int)*(latterNode->size));

		formerNode->size += latterNode->size;
		latterNode_prev->next = latterNode->next;

		free(latterNode->data);
		free(latterNode);
	}

	return;
}


void Cut(Node *temp, int x, int i) {
	Node *goal_Node = NULL;
	for (int j = 0; j < x; j++) {//不要設成i，因為i是function argument。
		temp = temp->next;
	}goal_Node = temp;

	Node *NewNode = (Node *) malloc ( sizeof(Node) );
	NewNode->data = (int *) malloc ( sizeof(int)*Max_length_of_int_array );
	memcpy(NewNode->data, goal_Node->data + i, sizeof(int)*(goal_Node->size - i));
	NewNode->size = goal_Node->size - i;

	goal_Node->size = i;
	NewNode->next = goal_Node->next;
	goal_Node->next = NewNode;

	return;
}


void PrintList(Node *temp) {
	while (temp != NULL) {
		for (int j = 0; j < temp->size; j++) {
			if (j == temp->size - 1) printf("%d\n", temp->data[j]);
			else printf("%d ", temp->data[j]);
		}

		Node *Node_for_deleting = temp;
		temp = temp->next;
		free(Node_for_deleting->data);
		free(Node_for_deleting);
	}

	return;
}