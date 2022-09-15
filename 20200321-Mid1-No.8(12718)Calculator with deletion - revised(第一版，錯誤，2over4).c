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

void size_Calculation(TreeNode *);
void value_Calculation(TreeNode *);

TreeNode *find_goal_node(TreeNode *, int);
long long Query_value(TreeNode *, int);
void Delete_part_of_Tree(TreeNode *root, TreeNode **true_root, TreeNode *fake_root_pos, int, int);


int main() {
	int N; scanf("%d", &N);
	char expr[length_expr]; scanf("%s", expr);

	TreeNode fake_root;
	TreeNode *true_root = TreeConstruction(expr, &fake_root);
	size_Calculation(true_root);

	while (N--) {
		char operator[2]; scanf("%s", operator);
		if (operator[0] == 'D') {
			int A, B; scanf("%d%d", &A, &B);

			Delete_part_of_Tree(true_root, &true_root, &fake_root, A, B);
			size_Calculation(true_root);
		}
		else if (operator[0] == 'Q') {
			int A; scanf("%d", &A);

			value_Calculation(true_root);

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

	return root;
}


TreeNode *makeNode(char c, TreeNode *parent) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));

	if (isdigit(c)) {
		temp->type = NUM;
		temp->value = c - '0';
		/*temp->size�bTreeConstruction���槹��A�A�浹size_and_value_Calculation�禡���B�z*/
		temp->leftchild = temp->rightchild = NULL;
		temp->parent = parent;
	}
	else {
		temp->type = (c == '+') ? ADD : (c == '-') ? SUB : MUL;
		/*temp->value�bTreeConstruction���槹��A�A�浹size_and_value_Calculation�禡���B�z*/
		/*temp->size�bTreeConstruction���槹��A�A�浹size_and_value_Calculation�禡���B�z*/
		temp->leftchild = temp->rightchild = NULL;
		temp->parent = parent;
	}

	return temp;
}


void size_Calculation(TreeNode *root) {
	if (root == NULL)return;

	size_Calculation(root->leftchild);
	size_Calculation(root->rightchild);

	if (root->type == NUM) root->size = 1;
	else root->size = (root->leftchild->size) + (root->rightchild->size) + 1;

	return;
}


void value_Calculation(TreeNode *root) {
	if (root == NULL)return;

	value_Calculation(root->leftchild);
	value_Calculation(root->rightchild);

	if (root->type == NUM);//�w�g�O�Ʀr�F�A�N�O�����ܡC
	else {
		if (root->type == ADD)root->value = (root->leftchild->value + root->rightchild->value) % MOD;
		else if (root->type == SUB)root->value = (root->leftchild->value - root->rightchild->value) % MOD;
		else if (root->type == MUL)root->value = (root->leftchild->value * root->rightchild->value) % MOD;
	}

	return;
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

	TreeNode *root_of_subTree_to_be_deleted = root;
	root = root_backup;
	TreeNode *orphan = find_goal_node(root, r + 1);

	if (root_of_subTree_to_be_deleted->parent == fake_root) {//����Aorphan�N�|���ӥN���A�����s���u���u����root
		*true_root_pos = orphan;
		free(root_of_subTree_to_be_deleted);
	}
	else {
		orphan->parent = root_of_subTree_to_be_deleted->parent;

		if (root_of_subTree_to_be_deleted->parent->leftchild == root_of_subTree_to_be_deleted)
			root_of_subTree_to_be_deleted->parent->leftchild = orphan;
		else root_of_subTree_to_be_deleted->parent->rightchild = orphan;
	}

	return;
}

//�U�д���
/*
�P�ǭ̦n�A
����12718�o���D�ءA�ڭ̵o�{���ǦP�Ƿ|�@�P�����ðݡA
��O�ڭ̨M�w�b�Q�װϴ��ѦP�Ǵ��ܡA���U�P�ǧ󦭤F�Ѱ��D�C

1. ���� modulo 10007 ������
���ǦP�Ƿ|�d�b�Ĥ@�B�ĤG�����L�A�ӲĤT�����L�����p�A
���N�O modulo 10007 �ϥΪ��ɾ��A�n�L�ĤT���|�ݭn�P�Ǧb�C���B��ɴN�� modulo 10007�A
�]���p�G����̫�~ modulo 10007�A�N�|�]���b�B��L�{��overflow�A�ɭP��X���~�C

2. ���� Delete ���� tree����k
�ڭ̵o�{�j�����P�ǹ�o�D�����k�O�Τ@�ӫܤj�� node array�Ӧs���C��node�A
�æbdelete tree �ɹ�node array �̨C�ӭȰ� update�A
�ӳo�˪��@�k�]�N�|�y���ĥ|��TLE�C
�o�䴣�Ѩ䤤�@�ؤ���n���@�k�A
�N�O�P�ǥi�H�ϥ�struct����size�Ӧs����node���U���h��node�A
�åγo�ӭȨӧ��ݭn�䪺node�A�A����pointer���V���a��A
�ӳo�ذ��k�N�i�H�q�L�ĥ|���C

PS. �]���e�ⵧ������²��A�ҥH�Ʊ�P�ǯ����sample input & output�ۤv�ˬd���D�A
�u�n�򥻷������T�A�e�ⵧ�N�@�w�|�q�L�C

�����ҥ[�o�I

Best Regards,
TA
*/

/*
������e��:
https://hackmd.io/iX8v0fuRSwmacUKhEtBb_Q�C
*/

/*
�D�U�U�ЫH:
�U�Цn�A
�o�O�ڪ�code http://codepad.org/uh9kc3Fn�A
�ĤG��WA�A�ĥ|��TLE�C
�ڤw�g��bug�s���F�j��8�p�ɦ��F...�h�B����TLE�A�ڧ䤣��WA���b���A�i�H�ЧU�д��ܶ�?

�٦�TLE�ٯ����OQQ?

�t�~���٦��Ӥp�ðݡA�N�O���p����O�o��: 

15
-*-13-5*33+7+57
Q 1
Q 6

�Ĥ@�ӫ��O"Q 1"��X�������N�ܩ_�ǤF�A�����u���O"-11"���A�аݧU�ЬO���O�]���h�Ҽ{�F�P�Ǫ�����A
�Ϧө��������ӴN���ӭt���o��X�����C
*/

/*
�U�Ц^��: 
�P�ǧA�n�A
�A�ثe��CODE�bOJ�W�O�L���F���A
�Ӱ��D�X�bsize_calculation function�A
���ګ�ĳ�A�i�H�b��tree���ɭԴN�@���size�A���Υt�~�A��C
		/*
		�]�N�O���A�ڱo��������ryona���g�k...�]�N�O��delete��part_of_Tree����A���n�A�λ��j�h���ʾ�size�F�C
		�bTreeConstruction���ɭԴN������size�A�C��delete_part_of_tree�ɥu�n���s��"���Q�v�T��"��node��size�Y�i�C
		��M�Avalue�������]�i�H��ӬݬݤW����檺���k�A�N�i�H����TLE�F�C
		�ҥH�ڧ�ĤG���t�~�x�s�A�o�ӲĤ@���N��b�o�̤��ʤF�A�H�K������M����C
		/*
�t�~�A�A���ðݥi�H�Ѧ�
https://reurl.cc/3D3WrL(����Ƨ����I��)

�z�פW�ӻ��Ĥ@����ĤG���|�@�_�L�A�ҥH�A�i�H�A�βĤ@���������Ҭݬ�
�����ҥ[�o

Best Regards,
TA
*/