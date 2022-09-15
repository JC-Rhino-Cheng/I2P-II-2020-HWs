#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable: 4996)

#define num_alphabet 4
typedef enum token {
	A, B, C, D, AND, OR
}TokenSet;

typedef struct _BTnode {
	TokenSet datum;
	struct _BTnode *left;
	struct _BTnode *right;
}BTNode;


BTNode *makeTree(void);
BTNode *makeNode(TokenSet);
int solve(BTNode *, int);
void freeTree(BTNode *);


int main() {
	BTNode *root = makeTree();

	for (int i = 0; i < (1 << num_alphabet); i++) {
		printf("%d %d %d %d ", (i >> 3) & 1, (i >> 2) & 1, (i >> 1) & 1, (i >> 0) & 1);
		printf("%d\n", solve(root, i));
	}

	freeTree(root);

	system("pause");
}


BTNode *makeTree(void) {
	char c = getchar();	TokenSet token;

	BTNode *node = NULL;
	if (isalpha(c)) {
		token = c - 'A';
		node = makeNode(token);
	}
	else {
		if (c == '&')token = AND;
		else token = OR;

		node = makeNode(token);
		node->left = makeTree();
		node->right = makeTree();
	}

	return node;
}


BTNode *makeNode(TokenSet token_Num) {
	BTNode *temp = (BTNode *)malloc(sizeof(BTNode));
	temp->datum = token_Num;
	temp->left = temp->right = NULL;

	return temp;
}


int solve(BTNode *root, int num) {
	if (root->datum == OR)
		return solve(root->left, num) | solve(root->right, num);
	else if (root->datum == AND)
		return solve(root->left, num) & solve(root->right, num);
	else return (num >> (num_alphabet - 1 - root->datum)) & 1;
}


void freeTree(BTNode *root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}