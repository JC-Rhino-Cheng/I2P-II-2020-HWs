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
		InOrder_index[InOrder[i]] = i;//function及其inverse function的概念。ex: InOrder[3]=5，表示f(3)=5(3號位置是5)。那麼g(5)=3(5在3號位置)。
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
	if (NEW_inorder_start > NEW_inorder_end)return NULL;//其實line49和line53只要保留其一即可，因為功能是一樣的，都是在為已經是leaf的node做遞迴結束的處理。(Note1)

	static int pre_now_index = 0;
	BTNode *root = makeNode(PreOrder[pre_now_index++]);
	if (NEW_inorder_start == NEW_inorder_end)return root;//其實line49和line53只要保留其一即可，因為功能是一樣的，都是在為已經是leaf的node做遞迴結束的處理。(Note1)

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


//從範例測資，很難找出思路步驟，所以可以用以下的測資，就可以很清楚明白TreeConstruction function如何運作
/*
7
3 7 8 6 11 2 5
2 7 3 6 8 11 5
*/

//助教提示: 
/*
嗨同學們好，
關於11833，我們發現大多數同學都有相同的問題，因此在討論區這邊提供一些想法讓同學們參考
如果你也同樣遇到了最後一筆 TLE 其餘 AC 的問題，可以參考以下的想法
但如果同學還沒有開始這道題目，也建議可以在實作後再向下看
多留給自己一些思考的空間，也更能精進自己喔～

首先，題目提供了 inorder 與 preorder，讓同學以這兩組字串來建樹
同學們應該能很直觀地想到取出 preorder 第一項，在 inorder 字串中找到這個數字，以此拆分出左子樹與右子樹
而 TLE 的關鍵也在這個部分
在「在 inorder 字串中找到這個數字」這個步驟中，同學們會以迴圈在 inorder 字串中尋找對應的數字
每次在長度 n 的字串中尋找，相當於每次都耗費將近 O(n) 的時間複雜度在查找上
不過，對於查找這件事而言，我們最理想的狀態，應該是在看到這個數字時，能立即得知這個數字的位置
因此，為了加速查找的過程，同學們可以想想看有沒有什麼方法能將時間壓低至 O(1)
以類似於對應表的模式，在得知 inorder 中的某個數字的同時，就也能立即能得到它在 inorder 中的位置，而不用反覆檢查 inorder 的值

有其他想法的話也歡迎在下方一起討論
預祝各位同學期中順利～

Best Regards,
TAs
*/

//Note1
/*
其實line49和line53的功能還是略有差異的，基本上line49比較大，包含了line53的功能，所以可以:
(1)line49、line53都寫。
(2)只寫line49，而不寫line53。

不行: 只寫line53，而不寫line49。

為何呢?
Ans: 基本上只要寫line53就可以cover掉幾乎99%問題，但是!!
假如他的測資是
10
7 8 4 1 5 6 2 0 9 3
7 3 9 0 2 6 5 1 4 8
在真正真正的root就只有一側有child，就會出問題。
如果不是真正真正的root只有一側有child，只寫line53是沒問題的。
*/

/*
如果測資是:
9
5 3 4 2 7 8 9 10 6
7 3 5 4 2 8 6 9 10
呢?
就會出問題。

為啥? 因為line55的inverse function，會導致line19~21在inverse的時候超出範圍。
講簡單一點就是我設計的測資不合法，因為題目有說
For all x being the number on the binary tree, 0 ? x ? N-1.
難怪OJ會AC但我的測資卻出錯。
*/