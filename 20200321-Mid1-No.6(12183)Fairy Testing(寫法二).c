#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable: 4996)

typedef enum _token {
	NUM, AND, OR
}Token;

typedef struct _BTnode {
	int datum;
	Token type;
	struct _BTnode *left;
	struct _BTnode *right;
	struct _BTnode *parent;
}BTNode;

BTNode *TreeConstruction(BTNode **, BTNode *); BTNode *makeNode(int, BTNode *);
void flipping(BTNode *);
void TreeDestruction(BTNode *);

int N, M;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		BTNode **ID = (BTNode **) malloc ( sizeof(BTNode)*N );
		BTNode *root = TreeConstruction(ID, NULL);

		while (M--) {
			int idx; scanf("%d", &idx);
			flipping(ID[idx]);

			printf("%d\n", root->datum);
		}

		free(ID);
		TreeDestruction(root);
	}

	system("pause");
}


BTNode *TreeConstruction(BTNode **ID, BTNode *parent) {
	int num_in;
	char c; while (isspace(c = getchar()))continue;

	BTNode *root = NULL;
	if (c == '[') {//當num為-1，設定為OR。當為-10，設定為AND。其餘正數index的datum一律設定為0
		scanf("%d]", &num_in);
		root = makeNode(num_in, parent);

		ID[num_in] = root;
	}
	else {
		if (c == '&') root = makeNode(-10, parent);//AND設定為-10
		else if (c == '|') root = makeNode(-1, parent);//OR設定為-1

		root->left = TreeConstruction(ID, root);
		root->right = TreeConstruction(ID, root);
	}

	return root;
}


BTNode *makeNode(int idx, BTNode *parent) {//當num為-1，設定為OR。當為-10，設定為AND。其餘正數index的datum一律設定為0
	BTNode *temp = (BTNode *)malloc(sizeof(BTNode));

	if (idx== -1) { temp->type = OR; temp->datum = 0; }
	else if (idx== -10) { temp->type = AND; temp->datum = 0; }
	else { temp->type = NUM; temp->datum = 0; }

	temp->parent = parent;
	temp->left = temp->right = NULL;

	return temp;
}


void flipping(BTNode *root) {
	int flag_keep_flipping = 1;

	while (flag_keep_flipping && root != NULL) {
		if (root->type == NUM) { root->datum = !(root->datum); root = root->parent; }
		else if (root->type == AND) {
			int original_datum = root->datum;

			root->datum = root->left->datum&root->right->datum;
			if (original_datum == root->datum)flag_keep_flipping = 0;
			root = root->parent;
		}
		else if (root->type == OR) {
			int original_datum = root->datum;

			root->datum = root->left->datum | root->right->datum;
			if (original_datum == root->datum)flag_keep_flipping = 0;
			root = root->parent;
		}
	}

	return;
}


void TreeDestruction(BTNode *root) {
	if (root != NULL) {
		TreeDestruction(root->left);
		TreeDestruction(root->right);

		free(root);
	}
}