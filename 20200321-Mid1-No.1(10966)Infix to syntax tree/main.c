#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "function.h"
#pragma warning (disable: 4996)

int main(void) {
	sym[0] = 'A';	sym[1] = 'B';	sym[2] = 'C';
	sym[3] = 'D';	sym[4] = '&';	sym[5] = '|';

	while (scanf("%s", expr) != EOF) {
		pos = strlen(expr) - 1;
		BTNode *root = EXPR();
		printPrefix(root);
		printf("\n");
		freeTree(root);
    }

	system("pause");
}
