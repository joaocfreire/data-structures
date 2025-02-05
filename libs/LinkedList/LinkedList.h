#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* init_list();
Node* insert_front(Node* list, int data);
Node* insert_back(Node* list, int data);
Node* search_in_list(Node* list, int data);
Node* remove_from_list(Node* list, int data);
void free_list(Node* list);
void print_list(Node* list);

#endif //LINKEDLIST_H
