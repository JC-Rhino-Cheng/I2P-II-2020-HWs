//這是一個只有10/15的code。但我懶得改了，就這樣吧

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

	if (flag_is_parent_valid) {//如果parent是valid，我要確定這個是否還是valid
		if (min < (root->value) && (root->value) < Max) {//如果這個確實valid
			root->flag_isValid = 1;
			Validation_checker(root->left, root->value, min, 1, 0);
			Validation_checker(root->right, Max, root->value, 1, 0);
		}
		else {//如果這個開始不valid
			root->flag_isValid = 0;
			root->value = now_invalid_num + 1;//你是從第一個invalid的root算起來，第now_invalid_num + 1個invalid的Node
			invalid_Max = max(invalid_Max, now_invalid_num + 1);
			int invalid_Max_backup = invalid_Max;

			Validation_checker(root->left, INT_MIN, INT_MIN, 0, now_invalid_num + 1);//這行和line88的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數
			int invalid_Max_backup_after_computing_lefttree = invalid_Max;

			invalid_Max = invalid_Max_backup;
			Validation_checker(root->right, INT_MAX, INT_MIN, 0, now_invalid_num + 1);//這行和line83的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數
			int invalid_Max_backup_after_computing_righttree = invalid_Max;

			int true_invalid_num_for_this_node = max(invalid_Max_backup_after_computing_lefttree, invalid_Max_backup_after_computing_righttree);

			root->value = true_invalid_num_for_this_node;
			invalid_Max = invalid_Max_backup - 1;

			/*
			其實這段原本沒有line83、86、88、90、92，line94也不是root->value = true_invalid_num_for_this_node;而是root->value=invalid_Max + 1 - (root->value);。
			但後來發現雖然符合由上數到下1、2、3、4的規則，但因為發現有些節點node會因為兩邊都是invalid，因為左邊算完之後沒有歸回到原樣就給右邊使用，所以導致錯誤取值(因為static invalid_Max只有一個)。
			所以就改成上面的code: 
			在左邊還沒用invalid_Max的時候就先備份。左邊計算時會沿用invalid_Max，計算後會有個左邊的結果數值，所以再備份左邊的。
			之後把invalid_Max給右邊的計算。右邊計算時會沿用invalid_Max，計算後會有個右邊的結果數值，所以再備份右邊的。
			root->value要取左右之中較大者。
			*/
		}
	}
	else {//如果parent已經invalid，那麼這個parent的所有徒子徒孫全部invalid。
		root->flag_isValid = 0;
		root->value = now_invalid_num + 1;
		invalid_Max = max(invalid_Max, now_invalid_num + 1);

		Validation_checker(root->left, INT_MIN, INT_MIN, 0, now_invalid_num + 1);//這行和下行的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數
		Validation_checker(root->right, INT_MAX, INT_MIN, 0, now_invalid_num + 1);//這行和上行的Max和min可以亂填任何一個int，因為在這之後的所有遞迴都不會用到這兩個數

		root->value = invalid_Max + 1 - (root->value);
	}

	return;
}