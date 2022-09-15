#include <stdlib.h>
#include <limits.h>
#include "function.h"
#pragma warning (disable: 4996)


Node *buildBST(int n, int *preOrder) {
	static int max_limit = INT_MAX, min_limit = INT_MIN, now_index = 0;

	if (preOrder[now_index] == -1 || preOrder[now_index] > max_limit || preOrder[now_index] < min_limit)return NULL;

	Node *root = (Node *) malloc ( sizeof(Node) );
	root->key = preOrder[now_index];
	preOrder[now_index++] = -1;

	if (now_index == n) {//�]���w�g��Ҧ����Ʀr���ئn��(�]���@��n�ӼơA��preOrder�s��0~n-1�@n�ӼơA�����bline14��now_index++�A�ҥH�h�[1�A��n)�F
		//�]���ڬOstatic�A�ҥH�U�@������i��ɤ��|�Q��l�ơA�n�ۤv��
		max_limit = INT_MAX; min_limit = INT_MIN; now_index = 0;
		root->ltree = root->rtree = NULL;

		return root;
	}

	int temp_for_max_limit = max_limit;
	max_limit = root->key;
	root->ltree = buildBST(n, preOrder);
	max_limit = temp_for_max_limit;

	int temp_for_min_limit = min_limit;
	min_limit = root->key;
	root->rtree = buildBST(n, preOrder);
	min_limit = temp_for_min_limit;

	return root;
}


void printInOrder(Node *ptr) {
	if (ptr == NULL) return;

	printInOrder(ptr->ltree);

	printf("%d ", ptr->key);

	printInOrder(ptr->rtree);
}


void printPostOrder(Node *ptr) {
	if (ptr == NULL)return;

	printPostOrder(ptr->ltree);
	printPostOrder(ptr->rtree);

	printf("%d ", ptr->key);
}


void freeTree(Node *ptr) {
	if (ptr != NULL) {
		freeTree(ptr->ltree);
		freeTree(ptr->rtree);

		free(ptr);
	}
}


//�U�д���: 
/*
�P�ǭ̦n�A
����12719�A�ڭ̤]�`�N��j�h�ƦP�Ǧ��P�˪� TLE ���D�A�]���]�b�����Ѥ@�ǫ��

�j�h�ƦP�ǹJ�쪺���p�O�A
�b���X preorder ���Ĥ@�ӼƦr a �ɡA�|�H�j��V��]�A������Ĥ@�Ӥ� a �j���Ʀr
�H�o�ӼƦr�������I�A�N�r�����l��P�k�l��A�i�ӦV�U�~��i���ӻ��j

�o�ӷQ�k���ҥH�|�y�� TLE�A�O�]���ƹ�W�o�Ӱj��O�����n��
�Q�k�����O�إߩ�A�N�o�ӻ��j�禡�ݫݬ��u�إߤ@�ʾ�v
���p�G�ڭ̥H�u�إߤ@�� node�v�������ӬݡA�ܦh�Ʊ��O��ٲ���

�إߤ@�ʾ�ɡA�ڭ̭n���L�Ҽ{�L�����k�l�������ˡ]�]���~�ݭn�o�Ӱj��^
�إߤ@�� node �ɡA�ڭ̥u�n�Ҽ{�L�����s���s�b
���򤰻�˪����p�U�@�� node ���s�b�O�H
�N�O�L�W�X�d�򪺮ɭԤF

�]�N�O���A�b�W�X�d��ɡA������e�� node �ä��ݩ��e����m�A
�]���������� function�A�N��e��m�]�� NULL�A�A�Ӭݬݷ�e�� node �O���O�ݩ󻼰j�W�@�h����m
�Ӧp�G�b�d�򤺡A�h�i�H�����N node ��i�w�Ƥ�����m�A�æV�U���j���� subtree

�ҥH���I�b��A
�H�o�ӼҦ��h��ҡA�N�|�o�{�A�u�n function ������n�^�� node �٬O NULL �����󦳳]�n
����N���|�ݭn�o�Ӧh�l���j����m
�ӬO�b���j���L�{���A�۰ʴN�|�����T�� node �t�W���T����m�F

�p�G�P�ǹ��H�W�������̵M�꦳�ôb�A���M��������o�˴N��إX��A�i�H�ѷӪ��ɪ��d��
����L�Q�k���ܤ]�w��b�U��@�_�Q��
���U��P�Ƕ��Q���D

Best Regards,
TAs
*/