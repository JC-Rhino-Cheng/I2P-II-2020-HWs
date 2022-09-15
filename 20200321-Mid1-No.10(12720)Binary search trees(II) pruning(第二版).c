#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>;
#pragma warning (disable: 4996)
#define MAX_num 1+(int)1e5//�]���̦h1e5�ӡA���O1-based
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

	if (flag_is_parent_valid) {//�p�Gparent�Ovalid�A�ڭn�T�w�o�ӬO�_�٬Ovalid
		if (min < (root->value) && (root->value) < Max) {//�p�G�o�ӽT��valid
			root->flag_isValid = 1;
			Validation_checker(root->left, root->value, min, 1, 0);
			Validation_checker(root->right, Max, root->value, 1, 0);
		}
		else {//�p�G�o�Ӷ}�l��valid
			root->flag_isValid = 0;

			Validation_checker(root->left, INT_MIN, INT_MIN, 0);//�o��Mline88��Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�
			Validation_checker(root->right, INT_MAX, INT_MIN, 0);//�o��Mline83��Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�
		}
	}
	else {//�p�Gparent�w�ginvalid�A����o��parent���Ҧ��{�l�{�]����invalid�C
		root->flag_isValid = 0;

		Validation_checker(root->left, INT_MIN, INT_MIN, 0);//�o��M�U�檺Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�
		Validation_checker(root->right, INT_MAX, INT_MIN, 0);//�o��M�W�檺Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�
	}

	return;
}


int getDepth(BSTNode *root) {
	if (root == NULL)return 0;

	if (root->left == NULL && root->right == NULL)return root->depth = 1;
	else return root->depth = max(getDepth(root->left), getDepth(root->right)) + 1;

}