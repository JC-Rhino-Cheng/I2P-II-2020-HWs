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
�u�n�@��Class��object�Q�ŧi�A
�bConstructor"�٨S"�B�@��"�e"�A
�o��object�̭����Ҧ��Ӧ���class�̭���data member�N�w�g���F�A�ӥB���Ofundamental type���w�]�ȡAex: int�N�O-873348574.....(�T���Ʀr�ڤ����D)�C
Constructor�����ƬO: 
(1)�ھ�initialiser list�h�����l�ƭ�
(2)�p�G�ٻݭn�B�~������A�N�bfunction�̭�implement

�ҥHmain.cpp�̭���line8�A�g�F: "List_stack L_stack;"
�B�@�B�J�p�U: 
(01)�ګŧi�F�@��object�s��L_stack�A�OList_stack-class
(02)�ŧiL_stack����U�A���N�w�g���FList_stack-class�̭��Ҧ���data member�A�Y����ListNode *head;�MListNode *tail;(Note: ���ܦh�l�B�J�A�����L)
(03)L_stack���FListNode *head;�BListNode *tail;����AList_stack();�~�Q����A�i��j���l�ơC

Note: 02�һ����l�B�J: 
�]��ListNode �]�O�ڭ̦ۤv�w�q��class�A�ҥH�@�ˡA
(01)�ګŧi�F�@��object�s��head�A�OListNode-class
(02)�ŧihead����U�A���N�w�g���FListNode-class�̭��Ҧ���data member�A�Y����int data;�BListNode* nextPtr;�BListNode* prevPtr;
(03)head���Fint data;�BListNode* nextPtr;�BListNode* prevPtr;����AListNode( const int &info ){}�~�Q����A�i��j���l��
(04)ListNode-class��tail��M�C
*/