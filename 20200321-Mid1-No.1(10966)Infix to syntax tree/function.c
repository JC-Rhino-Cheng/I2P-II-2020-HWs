#include "function.h"
#include <string.h>
#pragma warning (disable: 4996)

extern int pos;

BTNode* makeNode(char c) {
	BTNode * root = (BTNode *) malloc ( sizeof(BTNode) );
	
	for (int i = 0; i < NUMSYM; i++) if (sym[i] == c) { root->data = i; break; }
	root->left = NULL; root->right = NULL;

	return root;
}


BTNode* EXPR() {
	BTNode *right_expr = FACTOR();//因為EXPR = FACTOR | EXPR OP FACTOR，所以不管怎樣，我一定會先抓到FACTOR。這個FACTOR我一律先當成是"EXPR OP FACTOR(即:EXPR的第二種可能寫法)"的「右」邊(所以取名: right_expr)那項FACTOR，而我之後再去判斷，如果這個FACTOR的前面已經沒有operand(即:實際上是EXPR的第一種可能寫法)，或者這個FACTOR其實是EXPR去factorised，就return
	if (pos < 0 || expr[pos] == '(')return right_expr;//pos<0判斷的是這個FACTOR的前面已經沒有operand(即:實際上是EXPR的第一種可能寫法)。expr[pos]判斷的是這個FACTOR其實是EXPR去factorised

	BTNode *head = makeNode(expr[pos--]);//剩下需要把EXPR =  "EXPR OP" FACTOR實作出來。
	head->right = right_expr;
	head->left = EXPR();
	
	return head;
}


BTNode* FACTOR() {
	char c = expr[pos--];
	if (c == ')') {
		BTNode *head_of_factorised_expr = EXPR();
		pos--;
		return head_of_factorised_expr;
	}
	else return makeNode(c);
}


/* print a tree by pre-order. */
void printPrefix(BTNode *root) {
	if (root != NULL) {
		printf("%c", sym[root->data]);
		printPrefix(root->left);
		printPrefix(root->right);
	}
}


/* clean a tree.*/
void freeTree(BTNode *root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}
