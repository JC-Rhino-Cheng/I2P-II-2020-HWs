#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable: 4996)

typedef struct _BTnode {
	short datum_bit;//儲存的是: 是0還是1? 只有兩種可能。
	int ID;//ID代表題目中所給的編號。如果這個BTnode實際上是OR，儲存0。如果實際上是AND，儲存-1。
	struct _BTnode *leftchild;
	struct _BTnode *rightchild;
	struct _BTnode *parent;
}BTNode;


BTNode *TreeConstruction(BTNode **, BTNode *);
void flip(BTNode *);
void TreeDestruction(BTNode *);

BTNode *true_root = NULL;//紀錄真正的root的位置。這個是給flip函式使用，否則flip可能會繼續把true_root的parent給flip，造成runtime error。


int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int N, M; scanf("%d%d", &N, &M);
		BTNode **ID = (BTNode **)malloc(sizeof(BTNode)*N);//儲存ID=0~ID=N-1的node的指標位置

		/*BTNode fake_head;//fake_head是真正的root的parent，所以fake_head的child是真正的root。
		fake_head.leftchild= TreeConstruction(ID, &fake_head);//(1)讀入Boolean func，並把所有node的datum_bit設定為0，也一併把ID=0的node~ID=N-1的node 的 位置，儲存在一個pointer陣列裡。(2)因為只有一個child，我就隨便挑了左邊的來用。
		true_root = fake_head.leftchild;*/
		true_root = TreeConstruction(ID, true_root);


		while (M--) {
			//讀入要flip的ID，之後呼叫function把所有會被連帶影響的parent的datum_bit給改了。
			int goal_ID; scanf("%d", &goal_ID);
			flip(ID[goal_ID]);

			//之後輸出syntax tree 總root的datum_bit，記得\n
			printf("%hd\n", true_root->datum_bit);
		}

		TreeDestruction(true_root);
	}

	system("pause");
}

//讀入Boolean func(infix型態，即root-left-right)，並把所有node的datum_bit設定為0，
//也一併把ID=0的node~ID=N-1的node 的 位置，儲存在一個pointer陣列裡。
BTNode *TreeConstruction(BTNode **ID, BTNode *parent) {
	int num_in;
	char c; while (isspace(c = getchar()))continue;
	BTNode *root = NULL;

	if (c == '[') {
		scanf("%d]", &num_in);

		root = (BTNode *)malloc(sizeof(BTNode));

		root->datum_bit = 0;
		root->ID = num_in;
		root->parent = parent;
		root->leftchild = root->rightchild = NULL;

		ID[num_in] = root;

		return root;
	}
	else {
		root = (BTNode *)malloc(sizeof(BTNode));

		root->datum_bit = 0;
		root->ID = (c == '|') ? 0 : -1;
		root->parent = parent;
		root->leftchild = TreeConstruction(ID, root);
		root->rightchild = TreeConstruction(ID, root);

		return root;
	}

}


//讀入要flip的ID，之後呼叫function把所有會被連帶影響的parent的datum_bit給改了。
void flip(BTNode *the_flipped) {

	if (the_flipped->ID != 0 && the_flipped->ID != -1) {
		the_flipped->datum_bit = !(the_flipped->datum_bit);

		if (the_flipped != true_root)flip(the_flipped->parent);
	}
	else if (the_flipped->ID == 0) {//代表這個node是OR
		int original_datum_bit = the_flipped->datum_bit;
		the_flipped->datum_bit = the_flipped->leftchild->datum_bit | the_flipped->rightchild->datum_bit;

		if (original_datum_bit == the_flipped->datum_bit)return;//如果重新計算後的結果和原本一樣，那後面一定都會保持相同，就不用改了。
		else {
			if (the_flipped != true_root)flip(the_flipped->parent);
		}

	}
	else if (the_flipped->ID == -1) {//代表這個node是AND
		int original_datum_bit = the_flipped->datum_bit;
		the_flipped->datum_bit = the_flipped->leftchild->datum_bit & the_flipped->rightchild->datum_bit;

		if (original_datum_bit == the_flipped->datum_bit)return;//如果重新計算後的結果和原本一樣，那後面一定都會保持相同，就不用改了。
		else {
			if (the_flipped != true_root)flip(the_flipped->parent);
		}
	}

}

void TreeDestruction(BTNode *root) {
	if (root != NULL) {
		TreeDestruction(root->leftchild);
		TreeDestruction(root->rightchild);

		free(root);
	}
}