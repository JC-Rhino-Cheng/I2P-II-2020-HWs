#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#pragma warning (disable: 4996)


int main(void) {
	int n;
	scanf("%d", &n);

	while (n--) {
		getchar();
		Node *root = NULL;
		constructTree(&root);// construct syntax tree
		printInfix(root);// you have to implement this function
		printf("\n");
		freeTree(root);
    }

	system("pause");
}
