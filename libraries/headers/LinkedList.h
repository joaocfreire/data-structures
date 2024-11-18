#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* initList();
Node* insertFront(Node* l, int data);
Node* insertBack(Node* l, int x);
Node* searchInList(Node* l, int x);
Node* removeFromList(Node* l, int x);
void freeList(Node* l);
void printList(Node* l);

#endif //LINKEDLIST_H
