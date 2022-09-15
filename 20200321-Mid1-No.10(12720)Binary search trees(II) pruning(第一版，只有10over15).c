//�o�O�@�ӥu��10/15��code�C�����i�o��F�A�N�o�˧a

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
	struct _BSTnode *left, *right;
}BSTNode;

BSTNode *root;
BSTNode *ptr[MAX_num];

void TreeConstruction(int);


void Validation_checker(BSTNode *root, int Max, int min, int flag_is_parent_valid, int now_invalid_num);

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
	Validation_checker(root, INT_MAX, INT_MIN, 1, 0);

	for (int i = 1; i <= N; i++) {
		if (i != N)printf("%d ", (ptr[i]->flag_isValid) ? ptr[i]->value : -(ptr[i]->value));
		else printf("%d\n", (ptr[i]->flag_isValid) ? ptr[i]->value : -(ptr[i]->value));
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


void Validation_checker(BSTNode *root, int Max, int min, int flag_is_parent_valid, int now_invalid_num) {
	static int invalid_Max = 0;
	if (root == NULL) return;

	if (flag_is_parent_valid) {//�p�Gparent�Ovalid�A�ڭn�T�w�o�ӬO�_�٬Ovalid
		if (min < (root->value) && (root->value) < Max) {//�p�G�o�ӽT��valid
			root->flag_isValid = 1;
			Validation_checker(root->left, root->value, min, 1, 0);
			Validation_checker(root->right, Max, root->value, 1, 0);
		}
		else {//�p�G�o�Ӷ}�l��valid
			root->flag_isValid = 0;
			root->value = now_invalid_num + 1;//�A�O�q�Ĥ@��invalid��root��_�ӡA��now_invalid_num + 1��invalid��Node
			invalid_Max = max(invalid_Max, now_invalid_num + 1);
			int invalid_Max_backup = invalid_Max;

			Validation_checker(root->left, INT_MIN, INT_MIN, 0, now_invalid_num + 1);//�o��Mline88��Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�
			int invalid_Max_backup_after_computing_lefttree = invalid_Max;

			invalid_Max = invalid_Max_backup;
			Validation_checker(root->right, INT_MAX, INT_MIN, 0, now_invalid_num + 1);//�o��Mline83��Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�
			int invalid_Max_backup_after_computing_righttree = invalid_Max;

			int true_invalid_num_for_this_node = max(invalid_Max_backup_after_computing_lefttree, invalid_Max_backup_after_computing_righttree);

			root->value = true_invalid_num_for_this_node;
			invalid_Max = invalid_Max_backup - 1;

			/*
			���o�q�쥻�S��line83�B86�B88�B90�B92�Aline94�]���Oroot->value = true_invalid_num_for_this_node;�ӬOroot->value=invalid_Max + 1 - (root->value);�C
			����ӵo�{���M�ŦX�ѤW�ƨ�U1�B2�B3�B4���W�h�A���]���o�{���Ǹ`�Inode�|�]�����䳣�Oinvalid�A�]������⧹����S���k�^���˴N���k��ϥΡA�ҥH�ɭP���~����(�]��static invalid_Max�u���@��)�C
			�ҥH�N�令�W����code: 
			�b�����٨S��invalid_Max���ɭԴN���ƥ��C����p��ɷ|�u��invalid_Max�A�p���|���ӥ��䪺���G�ƭȡA�ҥH�A�ƥ����䪺�C
			�����invalid_Max���k�䪺�p��C�k��p��ɷ|�u��invalid_Max�A�p���|���ӥk�䪺���G�ƭȡA�ҥH�A�ƥ��k�䪺�C
			root->value�n�����k�������j�̡C
			*/
		}
	}
	else {//�p�Gparent�w�ginvalid�A����o��parent���Ҧ��{�l�{�]����invalid�C
		root->flag_isValid = 0;
		root->value = now_invalid_num + 1;
		invalid_Max = max(invalid_Max, now_invalid_num + 1);

		Validation_checker(root->left, INT_MIN, INT_MIN, 0, now_invalid_num + 1);//�o��M�U�檺Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�
		Validation_checker(root->right, INT_MAX, INT_MIN, 0, now_invalid_num + 1);//�o��M�W�檺Max�Mmin�i�H�ö����@��int�A�]���b�o���᪺�Ҧ����j�����|�Ψ�o��Ӽ�

		root->value = invalid_Max + 1 - (root->value);
	}

	return;
}