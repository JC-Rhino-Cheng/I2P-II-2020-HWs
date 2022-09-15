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
		/*temp->size在TreeConstruction執行完後，再交給size_and_value_Calculation函式做處理*/
		temp->leftchild = temp->rightchild = NULL;
		temp->parent = parent;
	}
	else {
		temp->type = (c == '+') ? ADD : (c == '-') ? SUB : MUL;
		/*temp->value在TreeConstruction執行完後，再交給size_and_value_Calculation函式做處理*/
		/*temp->size在TreeConstruction執行完後，再交給size_and_value_Calculation函式做處理*/
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

	if (root->type == NUM);//已經是數字了，就保持不變。
	else {
		if (root->type == ADD)root->value = (root->leftchild->value + root->rightchild->value) % MOD;
		else if (root->type == SUB)root->value = (root->leftchild->value - root->rightchild->value) % MOD;
		else if (root->type == MUL)root->value = (root->leftchild->value * root->rightchild->value) % MOD;
	}

	return;
}


TreeNode *find_goal_node(TreeNode *root, int goal_idx) {
	int now_idx = 1; int temp;

	while (1) {//抓取Node到最精確最精細的那種。(和Delete_part_of_Tree相比起來)
		if (now_idx == goal_idx)return root;

		temp = root->leftchild->size;
		if (now_idx < goal_idx&&goal_idx <= now_idx + temp) {//now_idx<goal_idx<=now_idx+temp   數學解釋相當於: 你現在在這，你走了這一步之後，會超越你的目標。
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


void Delete_part_of_Tree(TreeNode *root, TreeNode **true_root_pos, TreeNode* fake_root, int l, int r) {//類似於find_goal_node函式。由find_goal_node觀察可發現，在跳轉的時候都是經由"大節點"去執行。所以在Delete_part_of_Tree裡面，我們要找到一個範圍要去刪掉很簡單，一樣先找到大節點再說。不過，因為只要找到大節點就好，所以不用找到像find_goal_node那麼精細。
	TreeNode *root_backup = root;//備用。因為在while的時候就會一直linked list換掉root，而我要呼叫find_goal_node時又得要找到真正真正真正的root，故備份
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

	if (root_of_subTree_to_be_deleted->parent == fake_root) {//那麼，orphan就會取而代之，成為新的真正真正的root
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

//助教提示
/*
同學們好，
關於12718這個題目，我們發現有些同學會共同有的疑問，
於是我們決定在討論區提供同學提示，幫助同學更早了解問題。

1. 關於 modulo 10007 的部分
有些同學會卡在第一、第二筆都過，而第三筆不過的狀況，
其實就是 modulo 10007 使用的時機，要過第三筆會需要同學在每次運算時就先 modulo 10007，
因為如果直到最後才 modulo 10007，就會因為在運算過程中overflow，導致輸出錯誤。

2. 關於 Delete 部分 tree的方法
我們發現大部分同學對這題的做法是用一個很大的 node array來存取每個node，
並在delete tree 時對node array 裡每個值做 update，
而這樣的作法也就會造成第四筆TLE。
這邊提供其中一種比較好的作法，
就是同學可以使用struct中的size來存取該node之下有多少node，
並用這個值來找到需要找的node，再改變pointer指向的地方，
而這種做法就可以通過第四筆。

PS. 因為前兩筆測資比較簡單，所以希望同學能先用sample input & output自己檢查問題，
只要基本概念正確，前兩筆就一定會通過。

期中考加油！

Best Regards,
TA
*/

/*
思路內容見:
https://hackmd.io/iX8v0fuRSwmacUKhEtBb_Q。
*/

/*
求助助教信:
助教好，
這是我的code http://codepad.org/uh9kc3Fn，
第二個WA，第四個TLE。
我已經抓bug連續抓了大概8小時有了...姑且不談TLE，我找不到WA錯在哪，可以請助教提示嗎?

還有TLE還能怎麼辦呢QQ?

另外我還有個小疑問，就是假如測資是這樣: 

15
-*-13-5*33+7+57
Q 1
Q 6

第一個指令"Q 1"輸出為正的就很奇怪了，明明真正是"-11"阿，請問助教是不是因為多考慮了同學的測資，
反而忽略掉本來就應該負的卻輸出正的。
*/

/*
助教回覆: 
同學你好，
你目前的CODE在OJ上是過不了的，
而問題出在size_calculation function，
其實我建議你可以在建tree的時候就一邊算size，不用另外再算。
		/*
		也就是說，我得完全按照ryona的寫法...也就是說delete掉part_of_Tree之後，不要再用遞迴去算整棵樹的size了。
		在TreeConstruction的時候就直接算size，每次delete_part_of_tree時只要重新算"有被影響到"的node的size即可。
		當然，value的部分也可以仿照看看上面兩行的做法，就可以防止TLE了。
		所以我把第二版另外儲存，這個第一版就放在這裡不動了，以便後續釐清思路。
		/*
另外，你的疑問可以參考
https://reurl.cc/3D3WrL(見資料夾內截圖)

理論上來說第一筆跟第二筆會一起過，所以你可以再用第一筆的思維思考看看
期中考加油

Best Regards,
TA
*/