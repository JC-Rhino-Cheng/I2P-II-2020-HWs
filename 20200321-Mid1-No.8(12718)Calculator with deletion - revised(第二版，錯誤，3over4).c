#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable: 4996)

#define length_expr (int)3e5
#define MOD 10007

typedef enum datum_type {
	NUM, ADD, SUB, MUL
}DatumType;

typedef struct _treenode {
	DatumType type;
	long long value;
	int size;
	struct _treenode *leftchild, *rightchild, *parent;
}TreeNode;


TreeNode *TreeConstruction(char *, TreeNode *); TreeNode *makeNode(char, TreeNode *);

TreeNode *find_goal_node(TreeNode *, int);
long long Query_value(TreeNode *, int);
void Delete_part_of_Tree(TreeNode *root, TreeNode **true_root, TreeNode *fake_root_pos, int, int);
void Value_ReCalculate(TreeNode *, TreeNode *);


int main() {
	int N; scanf("%d", &N);
	char expr[length_expr]; scanf("%s", expr);

	TreeNode fake_root;
	TreeNode *true_root = TreeConstruction(expr, &fake_root);

	while (N--) {
		char operator[2]; scanf("%s", operator);
		if (operator[0] == 'D') {
			int A, B; scanf("%d%d", &A, &B);

			Delete_part_of_Tree(true_root, &true_root, &fake_root, A, B);
		}
		else if (operator[0] == 'Q') {
			int A; scanf("%d", &A);

			long long Ans = Query_value(true_root, A);
			Ans = ((Ans%MOD) + MOD) % MOD;
			printf("%lld\n", Ans);
		}
	}

	system("pause");
}


TreeNode *TreeConstruction(char *expr, TreeNode *parent) {
	static int pos = 0;
	char c = expr[pos++];

	TreeNode *root = makeNode(c, parent);
	if (root->type != NUM)root->leftchild = TreeConstruction(expr, root);
	if (root->type != NUM)root->rightchild = TreeConstruction(expr, root);

	//�}�l�p��size�Mvalue
	if (root->type == NUM) {
		root->size = 1;
		/*root->size�����S�O�p��A�]���w�g�bmakeNode�ɴN��J�i�ӤF�A�ӥB�U�~����*/
	}
	else {
		root->size = (root->leftchild->size) + (root->rightchild->size) + 1;

		switch (root->type) {
		case ADD:
			root->value = ((root->leftchild->value) + (root->rightchild->value)) % MOD;
			break;
		case SUB:
			root->value = ((root->leftchild->value) - (root->rightchild->value)) % MOD;
			break;
		case MUL:
			root->value = ((root->leftchild->value) * (root->rightchild->value)) % MOD;
			break;
		}
	}

	return root;
}


TreeNode *makeNode(char c, TreeNode *parent) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));

	if (isdigit(c)) {
		temp->type = NUM;
		temp->value = c - '0';
		/*temp->size�^��TreeConstruction�禡���B�z*/
		temp->leftchild = temp->rightchild = NULL;
		temp->parent = parent;
	}
	else {
		temp->type = (c == '+') ? ADD : (c == '-') ? SUB : MUL;
		/*temp->value�^��TreeConstruction�禡���B�z*/
		/*temp->size�^��TreeConstruction�禡���B�z*/
		temp->leftchild = temp->rightchild = NULL;
		temp->parent = parent;
	}

	return temp;
}


TreeNode *find_goal_node(TreeNode *root, int goal_idx) {
	int now_idx = 1; int temp;

	while (1) {//���Node��̺�T�̺�Ӫ����ءC(�MDelete_part_of_Tree�ۤ�_��)
		if (now_idx == goal_idx)return root;

		temp = root->leftchild->size;
		if (now_idx < goal_idx&&goal_idx <= now_idx + temp) {//now_idx<goal_idx<=now_idx+temp   �ƾǸ����۷��: �A�{�b�b�o�A�A���F�o�@�B����A�|�W�V�A���ؼСC
			now_idx++;
			root = root->leftchild;

			continue;
		}

		now_idx += temp;
		temp = root->rightchild->size;
		if (now_idx < goal_idx&&goal_idx <= now_idx + temp) {
			now_idx++;
			root = root->rightchild;
		}
	}
}


long long Query_value(TreeNode *root, int goal_idx) {
	TreeNode *GoalNode = find_goal_node(root, goal_idx);
	return GoalNode->value;
}


void Delete_part_of_Tree(TreeNode *root, TreeNode **true_root_pos, TreeNode* fake_root, int l, int r) {//������find_goal_node�禡�C��find_goal_node�[��i�o�{�A�b���઺�ɭԳ��O�g��"�j�`�I"�h����C�ҥH�bDelete_part_of_Tree�̭��A�ڭ̭n���@�ӽd��n�h�R����²��A�@�˥����j�`�I�A���C���L�A�]���u�n���j�`�I�N�n�A�ҥH���Χ�칳find_goal_node�����ӡC
	TreeNode *root_backup = root;//�ƥΡC�]���bwhile���ɭԴN�|�@��linked list����root�A�ӧڭn�I�sfind_goal_node�ɤS�o�n���u���u���u����root�A�G�ƥ�
	int now_index = 1; int temp;

	while (1) {
		if (l <= now_index && now_index <= r)break;

		temp = root->leftchild->size;
		if (now_index < l &&now_index + temp >= r) {
			now_index++;
			root = root->leftchild;

			continue;
		}

		now_index += temp;
		temp = root->rightchild->size;
		if (now_index < l &&now_index + temp >= r) {
			now_index++;
			root = root->rightchild;
		}
	}


	//�W�����ؼЫ�A�{�b�}�l�걵���s��Tree
	TreeNode *root_of_subTree_to_be_deleted = root;
	TreeNode *temp_node = root_of_subTree_to_be_deleted->parent;
	root = root_backup;
	TreeNode *orphan = find_goal_node(root, r + 1);

	if (root_of_subTree_to_be_deleted->parent == fake_root) {//�p�G�n�R����subTree�]�t�F�즳��root�A����Aorphan�N�|���ӥN���A�����s���u���u����root
		*true_root_pos = orphan;
		free(root_of_subTree_to_be_deleted);

		//�b�o�ر��p�U�A���έ��s�p��size�Mvalue�C
	}
	else {
		orphan->parent = root_of_subTree_to_be_deleted->parent;

		if (root_of_subTree_to_be_deleted->parent->leftchild == root_of_subTree_to_be_deleted)
			root_of_subTree_to_be_deleted->parent->leftchild = orphan;
		else root_of_subTree_to_be_deleted->parent->rightchild = orphan;


		//�b�o�ر��p�U�A�~�ݭn���s�p��size�Mvalue�p�H�U�Ҽg�C�䤤�Awhile�O���s�p��size�A��Value_ReCalculate�O���s�p��value�C
		while (temp_node != fake_root) {
			temp_node->size -= (r - l) + 1;
			temp_node = temp_node->parent;

			Value_ReCalculate(orphan->parent, fake_root);
		}
	}
	return;
}


void Value_ReCalculate(TreeNode *temp_now, TreeNode *fake_root) {
	if (temp_now == fake_root)return;

	switch (temp_now->type) {
	case ADD: {
		temp_now->value = ((temp_now->leftchild->value) + (temp_now->rightchild->value)) % MOD;
		break;
	}
	case SUB: {
		temp_now->value = ((temp_now->leftchild->value) - (temp_now->rightchild->value)) % MOD;
		break;
	}
	case MUL: {
		temp_now->value = ((temp_now->leftchild->value) * (temp_now->rightchild->value)) % MOD;
		break;
	}
	}

	Value_ReCalculate(temp_now->parent, fake_root);
}
/*
�U�Ц^��:
���ګ�ĳ�A�i�H�b��tree���ɭԴN�@���size�A���Υt�~�A��C
		/*
		�]�N�O���A�ڱo��������ryona���g�k...�]�N�O��delete��part_of_Tree����A���n�A�λ��j�h���ʾ�size�F�C
		�bTreeConstruction���ɭԴN������size�A�C��delete_part_of_tree�ɥu�n���s��"���Q�v�T��"��node��size�Y�i�C
		��M�Avalue�������]�i�H��ӬݬݤW����檺���k�A�N�i�H����TLE�F�C
		/*

�z�פW�ӻ��Ĥ@����ĤG���|�@�_�L�A�ҥH�A�i�H�A�βĤ@���������Ҭݬ�
�����ҥ[�o
*/

//�ܦ��AOJ���3/4�A�ĤG��WA�C�w�g�S��TLE�F�C
/*
����:
4
*-*44*11*-43+63
D 1 12
Q 1
D 1 2
Q 1
�N�W��h�B�F�C

�p�G�L�w�g���@���O�R���F�u���u����root�A�Ӳz����fake_root�]�n��ۧ�ʡA�i�O�ڧѤF��A
�ҥH�b�ĤG���L�S�屼�u���u����root���ɭԡAfake_root�ҳy�������G���n��WA�F�ARE���ܦ��i��C

�]����function parameter�S���]�pTreeNode** �hŪ�Jfake_root������(�Y: &fake_root)�A�ɭPfake_root�S����k��ʡA
�ڤS�i�o���s�]�pfunction�F�A�ӳ·СA�o�@�v�ʥ����A�N�i�o��F�C���D���~�b���N�n�C


�o��code��N��b: 
(1)�p�G������root�g�bglobal�A���O�ܦn��?�A�ۤv�ݬݫ᭱�@��function�A���|�I�s��root�A�������򤣪����]�w�bglobal?
(2)���쩳fake_root�N�O����F��Cfake_root���Ӫ�?���N�O���F�t�XTreeConstruction�ݭn����parent�ѼƩҥH�h�d�X�Ӫ��F���?
�A�h�Τ@��fake_root�i�H�O�i�H�A���O�N�|������B�z�����ܦh�C
�A�o�}���p�G���Q��line 34 �@�}�l�ؾ𪺮ɭԡA
TreeNode *parent���C�@�C�ӡC��C��C���C���C��C�J�CNULL�C���C�O�C�ܡC�n�C��?�A�o�}���A�o�ˤ��N�ѨM�F��?
�A�o����
�s��debug��ѡA�@�ѥα�8�p�ɡA���}��

*/