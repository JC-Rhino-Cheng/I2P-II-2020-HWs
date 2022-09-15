#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma warning (disable: 4996)

#define expr_length 256
#define num_of_sym 6
char sym[num_of_sym] = "ABCD&|";
char expr[expr_length];
int pos;

typedef enum _token {
	A, B, C, D, AND, OR
}TokenSet;

typedef struct _BTnode {
	TokenSet token;
	struct _BTnode *left;
	struct _BTnode *right;
}BTNode;

BTNode *EXPR(void);BTNode *FACTOR(void);BTNode *makeNode(char);//makeNode和FACTOR這兩function只有EXPR會用到，和main的關係有點遠，所以寫在一起
void printInfix(BTNode *);
void freeTree(BTNode *);

int main() {
	scanf("%s", expr);

	pos = strlen(expr) - 1;
	BTNode *root = EXPR();
	printInfix(root);
	freeTree(root);

	system("pause");
}


BTNode *EXPR(void) {
	BTNode *right_expr = FACTOR();
	if (pos < 0 || expr[pos] == '(')return right_expr;

	BTNode *head = makeNode(expr[pos--]);
	head->right = right_expr;
	head->left = EXPR();

	return head;
}


BTNode *FACTOR(void) {
	char c = expr[pos--];
	if (c == ')') {
		BTNode *head_of_factorised_expr = EXPR();
		pos--;
		return head_of_factorised_expr;
	}
	else return makeNode(c);
}


BTNode *makeNode(char c) {
	BTNode *temp = (BTNode *) malloc ( sizeof(BTNode) );

	switch (c) {
		case 'A': {temp->token = A; break; }
		case 'B': {temp->token = B; break; }
		case 'C': {temp->token = C; break; }
		case 'D': {temp->token = D; break; }
		case '&': {temp->token = AND; break; }
		case '|': {temp->token = OR; break; }
	}

	temp->left = temp->right = NULL;

	return temp;
}


void printInfix(BTNode *root) {
	if (root == NULL)return;

	printInfix(root->left);
	printf("%c", sym[root->token]);
	if (root->right != NULL) {
		if (root->right->token == AND || root->right->token == OR) {
			printf("(");
			printInfix(root->right);
			printf(")");
		}
		else printInfix(root->right);
	}
}


void freeTree(BTNode *root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);

		free(root);
	}
}