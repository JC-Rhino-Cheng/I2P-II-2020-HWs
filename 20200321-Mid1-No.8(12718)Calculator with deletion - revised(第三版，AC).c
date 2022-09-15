#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable: 4996)

#define str_len (int)3e5
#define MOD 10007

typedef enum _token {
	NUM, ADD, SUB, MUL
}TokenType;

typedef struct _TreeNode {
	TokenType type;
	int size;
	long long value;
	struct _TreeNode *ltree, *rtree, *parent;
}TreeNode;

TreeNode *TreeConstruction(char *, TreeNode *); TreeNode *makeNode(char, TreeNode *);
void Delete_part_of_Tree(TreeNode *, int, int);
void Value_reCalculation(TreeNode *);
TreeNode *find_goal_node(TreeNode *, int);
void TreeDestruction(TreeNode *);
long long Query_value(int);


TreeNode *root, *root_backup;

int main() {
	int N; scanf("%d", &N);
	char expr[str_len]; scanf("%s", expr);

	root = root_backup = TreeConstruction(expr, NULL);

	while (N--) {
		char operator[3]; scanf("%s", operator);

		if (operator[0] == 'D') {
			int A, B; scanf("%d%d", &A, &B);
			Delete_part_of_Tree(root, A, B);
		}
		else if (operator[0] == 'Q') {
			int A; scanf("%d", &A);
			long long Ans = Query_value(A);
			Ans = ((Ans%10007)+10007)%10007;
			printf("%lld\n", Ans);
		}
	}

	//system("pause");
}

TreeNode *TreeConstruction(char *expr, TreeNode *parent) {
	static int pos = 0;
	char c = expr[pos++];

	TreeNode *temp = makeNode(c, parent);

	if (temp->type != NUM) temp->ltree = TreeConstruction(expr, temp);
	if (temp->type != NUM) temp->rtree = TreeConstruction(expr, temp);

	//計算size、value
	if (temp->type == NUM)temp->size = 1;//NUM類型不用再計算temp
	else {
		temp->size = (temp->ltree->size) + (temp->rtree->size) + 1;

		if (temp->type == ADD)temp->value = (temp->ltree->value + temp->rtree->value) % MOD;
		else if(temp->type==SUB)temp->value = (temp->ltree->value - temp->rtree->value) % MOD;
		else if(temp->type==MUL)temp->value = (temp->ltree->value * temp->rtree->value) % MOD;
	}

	return temp;
}


TreeNode *makeNode(char c, TreeNode *parent) {
	TreeNode *temp = (TreeNode *) malloc ( sizeof(TreeNode) );
	temp->parent = parent;
	temp->ltree = temp->rtree = NULL;

	if (isdigit(c)) {
		temp->value = c - '0';
		temp->type = NUM;
	}
	else {
		if (c == '+') temp->type = ADD;
		else if (c == '-') temp->type = SUB;
		else if (c == '*') temp->type = MUL;
	}

	return temp;
}


TreeNode *find_goal_node(TreeNode *temp_node, int goal_idx) {
	int now_index = 1; int temp;

	while (1) {
		if (now_index == goal_idx)break;

		temp = temp_node->ltree->size;
		if (goal_idx <= now_index + temp) {
			now_index++;
			temp_node = temp_node->ltree;

			continue;
		}

		now_index += temp;
		temp = temp_node->rtree->size;
		if (goal_idx <= now_index + temp) {
			now_index++;
			temp_node = temp_node->rtree;

			continue;
		}
	}

	return temp_node;
}


void Delete_part_of_Tree(TreeNode *temp_node, int l, int r) {
	int now_index = 1; int temp;

	while (1) {
		if (l <= now_index && now_index <= r)break;

		temp = temp_node->ltree->size;
		if (now_index < l && now_index + temp >= r) {
			now_index++;
			temp_node = temp_node->ltree;

			continue;
		}

		now_index += temp;
		temp = temp_node->rtree->size;
		if (now_index < l && now_index + temp >= r) {
			now_index++;
			temp_node = temp_node->rtree;

			continue;
		}
	}

	TreeNode *root_of_subTree_to_be_deleted = temp_node;
	TreeNode *Orphan = find_goal_node(root, r + 1);

	Orphan->parent = root_of_subTree_to_be_deleted->parent;

	if (Orphan->parent != NULL) {
		if (Orphan->parent->ltree == root_of_subTree_to_be_deleted) Orphan->parent->ltree = Orphan;
		else Orphan->parent->rtree = Orphan;
		
		//開始計算被影響的TreeNode所儲存的size
		TreeNode *temp_for_size_recalculation = Orphan->parent;
		while (temp_for_size_recalculation != NULL) {
			temp_for_size_recalculation->size -= (r - l) + 1;
			temp_for_size_recalculation = temp_for_size_recalculation->parent;
		}
		//free掉所有不會再用到的東西
		if (root_of_subTree_to_be_deleted->rtree == Orphan) {
			TreeDestruction(root_of_subTree_to_be_deleted->ltree);
			free(root_of_subTree_to_be_deleted);
		}
		else if (root_of_subTree_to_be_deleted->ltree == Orphan) {
			TreeDestruction(root_of_subTree_to_be_deleted->rtree);
			free(root_of_subTree_to_be_deleted);
		}
	}
	else if (Orphan->parent == NULL) {
		root = Orphan;

		//free掉所有不會再用到的東西
		if (root_of_subTree_to_be_deleted->rtree == Orphan) {
			TreeDestruction(root_of_subTree_to_be_deleted->ltree);
			free(root_of_subTree_to_be_deleted);
		}
		else if (root_of_subTree_to_be_deleted->ltree == Orphan) {
			TreeDestruction(root_of_subTree_to_be_deleted->rtree);
			free(root_of_subTree_to_be_deleted);
		}
	}

	Value_reCalculation(Orphan->parent);

	return;
}


void Value_reCalculation(TreeNode *temp_node) {
	while (temp_node != NULL) {
		if (temp_node->type == ADD)temp_node->value = ((temp_node->ltree->value) + (temp_node->rtree->value)) % MOD;
		else if (temp_node->type == SUB)temp_node->value = ((temp_node->ltree->value) - (temp_node->rtree->value)) % MOD;
		else if (temp_node->type == MUL)temp_node->value = ((temp_node->ltree->value) * (temp_node->rtree->value)) % MOD;
	
		temp_node = temp_node->parent;
	}
}


void TreeDestruction(TreeNode *temp_node) {
	if (temp_node != NULL) {
		TreeDestruction(temp_node->ltree);
		TreeDestruction(temp_node->rtree);

		free(temp_node);
	}
}

long long Query_value(int idx) {
	TreeNode *goal_node = find_goal_node(root, idx);
	return goal_node->value;
}