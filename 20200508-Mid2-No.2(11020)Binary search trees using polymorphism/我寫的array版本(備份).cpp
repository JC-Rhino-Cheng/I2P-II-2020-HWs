#pragma warning (disable: 4996)
#include "function.h"
#include <math.h>

int inverse_array[1025];
bool idx_occupied[1025];

Array_BST::Array_BST() {//對array[1025]、用來查找index的反函數inverse_array[1025]，以及bool idx_occupied[1025]初始化
	for (int i = 0; i < 1025; i++) {
		array[i] = 0;//可從Array_BST::printf()的if判斷式，得知助教保證不會有數字為0的node
		inverse_array[i] = -1;
		idx_occupied[i] = false;
	}
	Height = 0;

	//不return任何東西
}


void Array_BST::insert(const int &val_inserted) {
	bool flag_val_exists = search(val_inserted);//先確定他這個數字確實是不在tree裡面，才放到tree裡
	
	if (!flag_val_exists) {
		int to_be_inserted_idx = -1;
		for (int i = 1; i < 1025; i++) {
			if (!idx_occupied[i]) {
				if (i != 1) {
					if (idx_occupied[i / 2]) {
						if (i % 2 == 0) {
							if (val_inserted < array[i / 2]) {
								int upper_layer_idx = find_num_of_layer(i / 2);
								for (int j = i / 2 - 1; j >= 1 << upper_layer_idx; j--) {
									if (idx_occupied[j] && val_inserted > array[j]) {
										if (array[(i / 2) / 2] == array[j / 2]) {
											if (val_inserted > array[(i / 2) / 2]) { to_be_inserted_idx = i; break; }
										}
										else { to_be_inserted_idx = i; break; }
									}
								}
								if (i / 2 == 1 << upper_layer_idx)to_be_inserted_idx = i;
							}
							else;//不能放
						}
						else if (i % 2 == 1) {
							if (val_inserted > array[i / 2]) {
								int upper_layer_idx = find_num_of_layer(i / 2);
								for (int j = i / 2 + 1; j < 1 << upper_layer_idx + 1; j++) {
									if (idx_occupied[j] && val_inserted < array[j]) {
										if (array[(i / 2) / 2] == array[j / 2]) {
											if (val_inserted < array[(i / 2) / 2]) { to_be_inserted_idx = i; break; }
										}
										else{ to_be_inserted_idx = i; break; }
									} 
								}
								if (i / 2 == (1 << upper_layer_idx + 1) - 1)to_be_inserted_idx = i;
							}
							else;
						}
					}
				}
				else if (i == 1) {
					to_be_inserted_idx = i;//可以放
				}

				if (to_be_inserted_idx != -1) {
					//變更三個陣列的內容
					array[to_be_inserted_idx] = val_inserted;
					inverse_array[val_inserted] = to_be_inserted_idx;
					idx_occupied[to_be_inserted_idx] = true;

					//計算Height
					bool flag_need_to_add_height = true;
					int layer_of_to_be_inserted_idx = find_num_of_layer(to_be_inserted_idx);
					for (int j = 1 << layer_of_to_be_inserted_idx; j < 1 << layer_of_to_be_inserted_idx + 1; j++) {
						if (idx_occupied[j] && j != to_be_inserted_idx) { flag_need_to_add_height = false; break; }
					}

					if (flag_need_to_add_height)Height++;
					break;
				}
			}
		}
	}
}


bool Array_BST::search(const int &val_to_look_up) const {
	return inverse_array[val_to_look_up] != -1 ? true : false;
}


List_BST::List_BST() {

}


void List_BST::insert(const int &) {

}


bool List_BST::search(const int &) const {
	return true;//暫時的
}


ListNode* List_BST::createLeaf(int key) const {
	ListNode *temp = new ListNode(key);
	return temp;
}


void List_BST::deleteTree(ListNode *root) {
	if (root != NULL) {
		deleteTree(root->left);
		deleteTree(root->right);

		delete root;
	}
}


int find_num_of_layer(int goal_idx) {
	int layer_of_goal_idx = -1;
	for (int temp = goal_idx; temp; layer_of_goal_idx++) 
		temp = temp >> 1;

	return layer_of_goal_idx;
}