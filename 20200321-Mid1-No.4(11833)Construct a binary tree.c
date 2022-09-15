#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996)

typedef struct _BTnode {
	int datum;
	struct _BTNode *left;
	struct _BTNode *right;
}BTNode;

BTNode *makeNode(int);
BTNode *TreeConstruction(int *, int *, int *, int, int);
void Output_PostOrder(BTNode *);
void TreeDestruction(BTNode *);

int main() {
	int N; scanf("%d", &N);

	int *InOrder = (int *)malloc(sizeof(int)*N);
	int *PreOrder = (int *)malloc(sizeof(int)*N);
	int *InOrder_index = (int *)malloc(sizeof(int)*N);

	for (int i = 0; i < N; i++) {
		scanf("%d", InOrder + i);
		InOrder_index[InOrder[i]] = i;//function�Ψ�inverse function�������Cex: InOrder[3]=5�A���f(3)=5(3����m�O5)�C����g(5)=3(5�b3����m)�C
	}
	for (int i = 0; i < N; i++) scanf("%d", PreOrder + i);

	BTNode *root = TreeConstruction(InOrder, PreOrder, InOrder_index, 0, N - 1);

	Output_PostOrder(root);
	puts("");
	TreeDestruction(root);

	system("pause");
}


BTNode *makeNode(int datum) {
	BTNode *temp = (BTNode *)malloc(sizeof(BTNode));
	temp->datum = datum;
	temp->left = temp->right = NULL;

	return temp;
}


BTNode *TreeConstruction(int *InOrder, int *PreOrder, int *InOrder_index, int NEW_inorder_start, int NEW_inorder_end) {
	if (NEW_inorder_start > NEW_inorder_end)return NULL;//���line49�Mline53�u�n�O�d��@�Y�i�A�]���\��O�@�˪��A���O�b���w�g�Oleaf��node�����j�������B�z�C(Note1)

	static int pre_now_index = 0;
	BTNode *root = makeNode(PreOrder[pre_now_index++]);
	if (NEW_inorder_start == NEW_inorder_end)return root;//���line49�Mline53�u�n�O�d��@�Y�i�A�]���\��O�@�˪��A���O�b���w�g�Oleaf��node�����j�������B�z�C(Note1)

	int Idx_of_Now_root_in_InOrder = InOrder_index[root->datum];
	root->left = TreeConstruction(InOrder, PreOrder, InOrder_index, NEW_inorder_start, Idx_of_Now_root_in_InOrder - 1);
	root->right = TreeConstruction(InOrder, PreOrder, InOrder_index, Idx_of_Now_root_in_InOrder + 1, NEW_inorder_end);

	return root;
}


void Output_PostOrder(BTNode *root) {
	if (root == NULL)return;

	Output_PostOrder(root->left);
	Output_PostOrder(root->right);

	printf("%d ", root->datum);

}


void TreeDestruction(BTNode *root) {
	if (root != NULL) {
		TreeDestruction(root->left);
		TreeDestruction(root->right);

		free(root);
	}
}


//�q�d�Ҵ���A������X����B�J�A�ҥH�i�H�ΥH�U������A�N�i�H�ܲM������TreeConstruction function�p��B�@
/*
7
3 7 8 6 11 2 5
2 7 3 6 8 11 5
*/

//�U�д���: 
/*
�٦P�ǭ̦n�A
����11833�A�ڭ̵o�{�j�h�ƦP�ǳ����ۦP�����D�A�]���b�Q�װϳo�䴣�Ѥ@�ǷQ�k���P�ǭ̰Ѧ�
�p�G�A�]�P�˹J��F�̫�@�� TLE ��l AC �����D�A�i�H�ѦҥH�U���Q�k
���p�G�P���٨S���}�l�o�D�D�ءA�]��ĳ�i�H�b��@��A�V�U��
�h�d���ۤv�@�ǫ�Ҫ��Ŷ��A�]����i�ۤv���

�����A�D�ش��ѤF inorder �P preorder�A���P�ǥH�o��զr��ӫؾ�
�P�ǭ����ӯ�ܪ��[�a�Q����X preorder �Ĥ@���A�b inorder �r�ꤤ���o�ӼƦr�A�H������X���l��P�k�l��
�� TLE ������]�b�o�ӳ���
�b�u�b inorder �r�ꤤ���o�ӼƦr�v�o�ӨB�J���A�P�ǭ̷|�H�j��b inorder �r�ꤤ�M��������Ʀr
�C���b���� n ���r�ꤤ�M��A�۷��C�����ӶO�N�� O(n) ���ɶ������צb�d��W
���L�A���d��o��ƦӨ��A�ڭ̳̲z�Q�����A�A���ӬO�b�ݨ�o�ӼƦr�ɡA��ߧY�o���o�ӼƦr����m
�]���A���F�[�t�d�䪺�L�{�A�P�ǭ̥i�H�Q�Q�ݦ��S�������k��N�ɶ����C�� O(1)
�H������������Ҧ��A�b�o�� inorder �����Y�ӼƦr���P�ɡA�N�]��ߧY��o�쥦�b inorder ������m�A�Ӥ��Τ����ˬd inorder ����

����L�Q�k���ܤ]�w��b�U��@�_�Q��
�w���U��P�Ǵ������Q��

Best Regards,
TAs
*/

//Note1
/*
���line49�Mline53���\���٬O�����t�����A�򥻤Wline49����j�A�]�t�Fline53���\��A�ҥH�i�H:
(1)line49�Bline53���g�C
(2)�u�gline49�A�Ӥ��gline53�C

����: �u�gline53�A�Ӥ��gline49�C

����O?
Ans: �򥻤W�u�n�gline53�N�i�Hcover���X�G99%���D�A���O!!
���p�L������O
10
7 8 4 1 5 6 2 0 9 3
7 3 9 0 2 6 5 1 4 8
�b�u���u����root�N�u���@����child�A�N�|�X���D�C
�p�G���O�u���u����root�u���@����child�A�u�gline53�O�S���D���C
*/

/*
�p�G����O:
9
5 3 4 2 7 8 9 10 6
7 3 5 4 2 8 6 9 10
�O?
�N�|�X���D�C

��ԣ? �]��line55��inverse function�A�|�ɭPline19~21�binverse���ɭԶW�X�d��C
��²��@�I�N�O�ڳ]�p�����ꤣ�X�k�A�]���D�ئ���
For all x being the number on the binary tree, 0 ? x ? N-1.
����OJ�|AC���ڪ�����o�X���C
*/