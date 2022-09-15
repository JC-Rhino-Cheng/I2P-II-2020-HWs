#ifndef function_h
#define function_h

#include <iostream>
#include <math.h>
#pragma warning (disable: 4996)
using namespace std;

class BST{
public:
	BST() :Height(0) {}
	virtual ~BST() {}
	virtual void insert(const int &) = 0;
	virtual bool search(const int &) const = 0;
	virtual void print() const = 0;
	int height() const { return Height; }

protected:
	int Height;//�Ū��ܡA��0�C�u��root���ܡA��1�C
};

class Array_BST : public BST{
public:
	Array_BST();
	virtual ~Array_BST() {}
	virtual void insert(const int &) override; //�`�N!!!root�O�Q�x�s�bindex1!!!!!�ĥ�1-based�������覡�C
	virtual bool search(const int &) const override;
	virtual void print() const override{
		int k = pow(2, height());
		for (int i = 1; i <= k - 1; i++)
			if (array[i]) cout << array[i] << " ";
    }

private:
	int array[1025];
};

class ListNode {
	friend class List_BST;

public:
	ListNode(const int &info) :key(info), left(NULL), right(NULL) {}

private:
	int key;
	ListNode *left;
	ListNode *right;
};

class List_BST : public BST{
public:
	List_BST();
	virtual ~List_BST() {
		deleteTree(root);
    }
	virtual void insert(const int &) override;
	virtual bool search(const int &) const override;
	virtual void print() const override{
		for (int i = 1; i <= Height; i++) printGivenLevel(root, i);
    }

private:
	ListNode *root;
	ListNode* createLeaf(int key) const; //���N�OcreateNode�Ӥw�A�u���L�]���C��creat�@�w�Ocreate���l�A�ҥH�٬�createLeaf
	void deleteTree(ListNode *root);

	void printGivenLevel(ListNode* Ptr, int level) const {
		if (Ptr == NULL) return;
		if (level == 1) cout << Ptr->key << " ";
		else if (level > 1) {
			printGivenLevel(Ptr->left, level - 1);
			printGivenLevel(Ptr->right, level - 1);
        }
    }
};


#endif 


/*
�u�}����:
I 30
I 45
I 15
I 52
I 7
I 55
I 38
I 22
I 3
I 10
I 25
I 18
I 42
I 48
I 35
I 29
P

*/