#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>;
#pragma warning (disable: 4996)
#define MAX_num 1+(int)1e5//因為最多1e5個，但是1-based
#define max(a, b) ( ( a > b ) ? a : b )

typedef struct _BSTnode {
	int flag_isValid;
	int value;
	int depth;
	struct _BSTnode *left, *right;
}BSTNode;

BSTNode *root;
BSTNode *ptr[MAX_num];

void TreeConstruction(int);
void Validation_checker(BSTNode *root, int Max, int min, int flag_is_parent_valid);
int getDepth(BSTNode *root);

int main() {
	int N; scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		int num_in; scanf("%d", &num_in);

		BSTNode *temp = (BSTNode *)malloc(sizeof(BSTNode));
		temp->value = num_in;
		temp->left = temp->right = NULL;

		ptr[i] = temp;
	}

	TreeConstruction(N);
	Validation_checker(root, INT_MAX, INT_MIN, 1);
	getDepth(root);

	for (int i = 1; i <= N; i++) {
		if (i != N)printf("%d ", (ptr[i]->flag_isValid) ? ptr[i]->value : -(ptr[i]->depth));
		else printf("%d\n", (ptr[i]->flag_isValid) ? ptr[i]->value : -(ptr[i]->depth));
	}

	system("pause");
}


void TreeConstruction(int N) {
	for (int i = 1; i <= N;) {
		char c;
		int get_index = 0;

		if (isspace(c = getchar()))continue;
		if (c == '0') { root = ptr[i++]; continue; }
		while (isdigit(c)) {
			get_index *= 10; get_index += c - '0';

			c = getchar();
		}

		if (c == 'L') { ptr[get_index]->left = ptr[i++]; }
		else if (c == 'R') { ptr[get_index]->right = ptr[i++]; }
	}
}


void Validation_checker(BSTNode *root, int Max, int min, int flag_is_parent_valid) {
	if (root == NULL) return;

	if (flag_is_parent_valid) {//如果parent是valid，我要確定這個是否還是valid
		if (min < (root->value) && (root->value) < Max) {//如果這個確實valid
			root->flag_isValid = 1;
			Validation_checker(root->left, root->value, min, 1, 0);
			Validation_checker(root->right, Max, root->value, 1, 0);
		}
		else {//如果這個開始不valid
			root->flag_isValid = 0;

			Validation_checker(root->left, INT_MIN, INT_MIN, 0);//這行和line88的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數
			Validation_checker(root->right, INT_MAX, INT_MIN, 0);//這行和line83的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數
		}
	}
	else {//如果parent已經invalid，那麼這個parent的所有徒子徒孫全部invalid。
		root->flag_isValid = 0;

		Validation_checker(root->left, INT_MIN, INT_MIN, 0);//這行和下行的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數
		Validation_checker(root->right, INT_MAX, INT_MIN, 0);//這行和上行的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數
	}

	return;
}


int getDepth(BSTNode *root) {
	if (root == NULL)return 0;

	if (root->left == NULL && root->right == NULL)return root->depth = 1;
	else return root->depth = max(getDepth(root->left), getDepth(root->right)) + 1;

}