#include "function.h"
#include <stdio.h>
#pragma warning (disable: 4996)


void constructTree(Node** head) {
	if (*head == NULL) {
		*head = (Node *)malloc(sizeof(Node));
		char c = getchar();

		(*head)->data = c;
		(*head)->left = (*head)->right = NULL;

		if ((*head)->left == NULL && ((*head)->data == '&' || (*head)->data == '|'))
			constructTree(&(*head)->left);
		if ((*head)->right == NULL && ((*head)->data == '&' || (*head)->data == '|'))
			constructTree(&(*head)->right);
	}
}


void freeTree(Node *root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

void printInfix(Node *root) {
	if (root == NULL)return;

	printInfix(root->left);
	printf("%c", root->data);
	if (root->right != NULL) {
		if (root->right->data == '&' || root->right->data == '|') {
			printf("(");
			printInfix(root->right);
			printf(")");
		}
		else printInfix(root->right);
	}
}