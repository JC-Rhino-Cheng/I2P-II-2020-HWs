#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable: 4996)

typedef struct _node {
	char content;
	struct _node *previous;
	struct _node *next;
}Node;

void print_and_then_delete(Node **head);

int main() {
	int T; scanf("%d", &T);

	while (T--) {
		Node *head, *tail;
		head = (Node *)malloc(sizeof(Node));
		tail = (Node *)malloc(sizeof(Node));
		head->previous = NULL; head->next = tail;
		tail->previous = head; tail->next = NULL;

		Node *cursorNode = head;//我設定: 若有輸入字元，就一律在"cursorNode的右方"插入。

		int length; scanf("%d", &length);

		while (length--) {
			char input;
			while (isspace(input = getchar())) continue;

			switch (input) {
			case 'R': {
				if (cursorNode->next->next != NULL)cursorNode = cursorNode->next;
				break;
			}

			case 'L': {
				if (cursorNode->previous != NULL)cursorNode = cursorNode->previous;
				break;
			}

			case 'B': {
				if (cursorNode->previous != NULL) {
					cursorNode->previous->next = cursorNode->next;
					cursorNode->next->previous = cursorNode->previous;

					Node* temp_address_for_deleting_the_Node = cursorNode;
					cursorNode = cursorNode->previous;
					free(temp_address_for_deleting_the_Node);
				}
				break;
			}

			default: {
				Node *Insert_Node;
				Insert_Node = (Node*)malloc(sizeof(Node));
				Insert_Node->content = input;

				Insert_Node->next = cursorNode->next;
				Insert_Node->previous = cursorNode;
				Insert_Node->next->previous = Insert_Node;
				Insert_Node->previous->next = Insert_Node;

				cursorNode = Insert_Node;
				break;
			}
			}
		}

		print_and_then_delete(&head);
		puts("");
	}

	system("pause");
}


void print_and_then_delete(Node **head) {
	Node *temp = *head;
	Node *previous_of_temp = NULL;

	while (temp->next != NULL) {
		if (temp != *head) printf("%c", temp->content);

		previous_of_temp = temp;
		temp = temp->next;
		free(previous_of_temp);
	}free(temp);

	return;
}

//採用的Linked List辦法是https://reurl.cc/yZEjAy的辦法2