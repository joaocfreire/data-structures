#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stackNode {
    int data;
    struct stackNode* next;
} StackNode;

typedef struct stack {
    StackNode* top;
    int count;
} Stack;

Stack* createStack();
void push(Stack* s, int x);
void pop(Stack* s, int* x);
int top(Stack* s);
bool stackEmpty(Stack* s);
void freeStack(Stack* s);
void printStack(Stack* s);

#endif //STACK_H