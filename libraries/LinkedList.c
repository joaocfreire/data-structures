#include "headers/LinkedList.h"

Node* initList() {
    return NULL;
}

Node* insertFront(Node* l, int data) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = l;
    return new;
}

Node* insertBack(Node* l, int data) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    if (l == NULL) // lista vazia
        l = new;
    else {
        if (l->next == NULL) // fim da lista
            l->next = new;
        else
            insertBack(l->next, data);
    }
    return l;
}

Node* searchInList(Node* l, int data) {
    if (l == NULL || l->data == data)
        return l;
    return searchInList(l->next, data);
}

Node* removeFromList(Node* l, int data) {
    if (l == NULL) return l;
    if (l->data == data) {
        Node* aux = l;
        l = l->next;
        free(aux);
    }
    else
        l->next = removeFromList(l->next, data);
    return  l;
}

void freeList(Node* l) {
    if (l) {
        freeList(l->next);
        free(l);
    }
}

void printList(Node* l) {
    if (l) {
        printf("%d", l->data);
        if (l->next)
            printf("-> ");
            printList(l->next);
    }
}