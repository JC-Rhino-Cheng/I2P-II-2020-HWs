#include <stdio.h>
#include <stdlib.h>


typedef struct _Node {
    int data;
    struct _Node *next;
} Node;


Node* createList(int *a, int size);
Node* copyList(Node* head);

void push_front(Node** head, int val);
void deleteElementByIdx(Node** head, int idx);
void SwapElementByIdx(Node** head, int idx1, int idx2);
