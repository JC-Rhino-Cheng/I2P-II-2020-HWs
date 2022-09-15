#include "function.h"

Array_BST::Array_BST() :BST() {//對array[1025]初始化
	memset(array, 0, sizeof(array));//可從Array_BST::printf()的if判斷式，得知助教保證不會有數字為0的node

	//Return nothing
}


void Array_BST::insert(const int& val) {
	if (array[1] == 0) {
		array[1] = val;
		Height = 1;
	}
	else {
		int h = 1; int cur_idx = 1;
		while (true) {
			if (array[cur_idx]) {
				if (val < array[cur_idx]) {
					cur_idx = cur_idx * 2;
					h++;
				}
				else if (val > array[cur_idx]) {
					cur_idx = cur_idx * 2 + 1;
					h++;
				}
				else if (val == array[cur_idx])return;
			}
			else {
				array[cur_idx] = val;
				if (h > Height)Height = h;
			}
		}
	}

	return;
}


bool Array_BST::search(const int &val_to_look_up) const {
	for (int i = 0; i < 1025; i++)if (array[i] == val_to_look_up)return true;

	return false;
}


List_BST::List_BST() :root(NULL) {}


void List_BST::insert(const int &val) {
	if (!root) {
		root = createLeaf(val);
		Height = 1;
	}
	else {
		ListNode *temp = root;
		int h = 1;
		bool done = false;
		while (!done) {
			if (val < temp->key) {
				if (temp->left) {
					temp = temp->left;
				}
				else { temp->left = createLeaf(val); done = true; }
				
				h++;
			}
			else if (val > temp->key) {
				if (temp->right) {
					temp = temp->right;
					
				}
				else { temp->right = createLeaf(val); done = true; }
				
				h++;
			}
			else if (val == temp->key) return;
		}

		if (h > Height)Height = h;
	}
}


bool List_BST::search(const int &goal_val) const {
	ListNode *temp = root;
	while (temp) {
		if (goal_val < temp->key)temp = temp->left;
		else if (goal_val > temp->key)temp = temp->right;
		else if (goal_val == temp->key)return true;
	}

	return false;
}


ListNode* List_BST::createLeaf(int key) const {
	return new ListNode(key);
}


void List_BST::deleteTree(ListNode *root) {
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);

		delete root;
	}
}
