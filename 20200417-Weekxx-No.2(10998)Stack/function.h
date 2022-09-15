#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>

class ListNode{
	friend class List_stack; //make List_stack a friend
	public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
		{} //end ListNode constructor
		~ListNode() {}

    private:
		int data; //data
		ListNode* nextPtr; // next node in list
		ListNode* prevPtr;
}; //end class ListNode

class List_stack{
    public:
		List_stack();
		~List_stack();
		void push(const int &);
		void pop();
		void print();
    private:
        ListNode *head;
        ListNode *tail;
};
#endif // FUNCTION_H
/*
只要一個Class的object被宣告，
在Constructor"還沒"運作之"前"，
這個object裡面的所有該有的class裡面的data member就已經有了，而且都是fundamental type的預設值，ex: int就是-873348574.....(確切數字我不知道)。
Constructor做的事是: 
(1)根據initialiser list去執行初始化值
(2)如果還需要額外做什麼，就在function裡面implement

所以main.cpp裡面的line8，寫了: "List_stack L_stack;"
運作步驟如下: 
(01)我宣告了一個object叫做L_stack，是List_stack-class
(02)宣告L_stack的當下，它就已經有了List_stack-class裡面所有的data member，即它有ListNode *head;和ListNode *tail;(Note: 有很多子步驟，先跳過)
(03)L_stack有了ListNode *head;、ListNode *tail;之後，List_stack();才被執行，進行強制初始化。

Note: 02所說的子步驟: 
因為ListNode 也是我們自己定義的class，所以一樣，
(01)我宣告了一個object叫做head，是ListNode-class
(02)宣告head的當下，它就已經有了ListNode-class裡面所有的data member，即它有int data;、ListNode* nextPtr;、ListNode* prevPtr;
(03)head有了int data;、ListNode* nextPtr;、ListNode* prevPtr;之後，ListNode( const int &info ){}才被執行，進行強制初始化
(04)ListNode-class的tail亦然。
*/