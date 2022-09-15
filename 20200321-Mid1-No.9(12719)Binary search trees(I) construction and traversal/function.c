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

	if (now_index == n) {//因為已經把所有的數字都建好樹(因為共有n個數，而preOrder編號0~n-1共n個數，但有在line14對now_index++，所以多加1，成n)了
		//因為我是static，所以下一次測資進行時不會被初始化，要自己來
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


//助教提示: 
/*
同學們好，
關於12719，我們也注意到大多數同學有同樣的 TLE 問題，因此也在此提供一些思路

大多數同學遇到的狀況是，
在取出 preorder 中第一個數字 a 時，會以迴圈向後跑，直到找到第一個比 a 大的數字
以這個數字為切割點，將字串拆成左子樹與右子樹，進而向下繼續進行兩個遞迴

這個想法之所以會造成 TLE，是因為事實上這個迴圈是不必要的
想法本身是建立於，將這個遞迴函式看待為「建立一棵樹」
但如果我們以「建立一個 node」的概念來看，很多事情是能省略的

建立一棵樹時，我們要替他考慮他的左右子樹長什麼樣（因此才需要這個迴圈）
建立一個 node 時，我們只要考慮他本身存不存在
那麼什麼樣的狀況下一個 node 不存在呢？
就是他超出範圍的時候了

也就是說，在超出範圍時，說明當前的 node 並不屬於當前的位置，
因此必須結束 function，將當前位置設為 NULL，再來看看當前的 node 是不是屬於遞迴上一層的位置
而如果在範圍內，則可以直接將 node 放進預料中的位置，並向下遞迴它的 subtree

所以重點在於，
以這個模式去思考，就會發現，只要 function 裡關於要回傳 node 還是 NULL 的條件有設好
那麼就不會需要這個多餘的迴圈抓位置
而是在遞迴的過程中，自動就會替正確的 node 配上正確的位置了

如果同學對於以上的解釋依然抱有疑惑，不清楚為什麼這樣就能建出樹，可以參照附檔的範例
有其他想法的話也歡迎在下方一起討論
祝各位同學順利解題

Best Regards,
TAs
*/