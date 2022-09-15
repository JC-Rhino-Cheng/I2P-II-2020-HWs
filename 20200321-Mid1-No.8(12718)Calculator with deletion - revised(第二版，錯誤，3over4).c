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

	//開始計算size和value
	if (root->type == NUM) {
		root->size = 1;
		/*root->size不須特別計算，因為已經在makeNode時就輸入進來了，而且萬年不變*/
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
		/*temp->size回到TreeConstruction函式做處理*/
		temp->leftchild = temp->rightchild = NULL;
		temp->parent = parent;
	}
	else {
		temp->type = (c == '+') ? ADD : (c == '-') ? SUB : MUL;
		/*temp->value回到TreeConstruction函式做處理*/
		/*temp->size回到TreeConstruction函式做處理*/
		temp->leftchild = temp->rightchild = NULL;
		temp->parent = parent;
	}

	return temp;
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


	//上面找到目標後，現在開始串接為新的Tree
	TreeNode *root_of_subTree_to_be_deleted = root;
	TreeNode *temp_node = root_of_subTree_to_be_deleted->parent;
	root = root_backup;
	TreeNode *orphan = find_goal_node(root, r + 1);

	if (root_of_subTree_to_be_deleted->parent == fake_root) {//如果要刪除的subTree包含了原有的root，那麼，orphan就會取而代之，成為新的真正真正的root
		*true_root_pos = orphan;
		free(root_of_subTree_to_be_deleted);

		//在這種情況下，不用重新計算size和value。
	}
	else {
		orphan->parent = root_of_subTree_to_be_deleted->parent;

		if (root_of_subTree_to_be_deleted->parent->leftchild == root_of_subTree_to_be_deleted)
			root_of_subTree_to_be_deleted->parent->leftchild = orphan;
		else root_of_subTree_to_be_deleted->parent->rightchild = orphan;


		//在這種情況下，才需要重新計算size和value如以下所寫。其中，while是重新計算size，而Value_ReCalculate是重新計算value。
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
助教回覆:
其實我建議你可以在建tree的時候就一邊算size，不用另外再算。
		/*
		也就是說，我得完全按照ryona的寫法...也就是說delete掉part_of_Tree之後，不要再用遞迴去算整棵樹的size了。
		在TreeConstruction的時候就直接算size，每次delete_part_of_tree時只要重新算"有被影響到"的node的size即可。
		當然，value的部分也可以仿照看看上面兩行的做法，就可以防止TLE了。
		/*

理論上來說第一筆跟第二筆會一起過，所以你可以再用第一筆的思維思考看看
期中考加油
*/

//至此，OJ顯示3/4，第二筆WA。已經沒有TLE了。
/*
測資:
4
*-*44*11*-43+63
D 1 12
Q 1
D 1 2
Q 1
就戳到痛處了。

如果他已經有一次是刪掉了真正真正的root，照理來講fake_root也要跟著改動，可是我忘了改，
所以在第二次他又砍掉真正真正的root的時候，fake_root所造成的結果不要講WA了，RE都很有可能。

因為我function parameter沒有設計TreeNode** 去讀入fake_root的指標(即: &fake_root)，導致fake_root沒有辦法更動，
我又懶得重新設計function了，太麻煩，牽一髮動全身，就懶得改了。知道錯誤在哪就好。


這個code爛就爛在: 
(1)如果直接把root寫在global，不是很好嗎?你自己看看後面一堆function，都會呼叫到root，那為什麼不直接設定在global?
(2)說到底fake_root就是個爛東西。fake_root怎麼來的?不就是為了配合TreeConstruction需要收到parent參數所以多搞出來的東西嗎?
你多用一個fake_root可以是可以，但是就會讓後續處理複雜很多。
你這破腦如果當初想到line 34 一開始種樹的時候，
TreeNode *parent那。一。個。欄。位。直。接。填。入。NULL。不。是。很。好。嗎?你這破腦，這樣不就解決了嗎?
你這智障
連續debug兩天，一天用掉8小時，死破腦

*/