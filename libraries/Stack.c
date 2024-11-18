#include "headers/Stack.h"

Stack* createStack() {
    Stack* new = (Stack*) malloc(sizeof(Stack));
    new->top = NULL;
    new->count = 0;
    return new;
}

void push(Stack* s, int x) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = s->top;
    s->top = newNode;
    s->count++;
}

void pop(Stack* s, int* x) {
    if (!stackEmpty(s)) {
        Node* aux = s->top;
        *x = s->top->data;
        s->top = s->top->next;
        s->count--;
        free(aux);
    }
    else *x = 0;
}

int top(Stack* s) {
    if (!stackEmpty(s)) return s->top->data;
    return -1;
}

bool stackEmpty(Stack* s) {
    if (s == NULL || s->top == NULL) return true;
    return false;
}

void freeStack(Stack* s) {
    while (!stackEmpty(s)) {
        Node *aux = s->top;
        s->top = s->top->next;
        free(aux);
    }
    free(s);
}

void printStack(Stack* s) {
    if (!stackEmpty(s)) {
        printf("Quantidade de elementos na pilha: %d\n\n", s->count);
        Node* aux = s->top;
        while (aux) {
            printf("%d", aux->data);
            if (aux->next) printf(" -> ");
            aux = aux->next;
        }
    }
    else printf("Pilha vazia");
}