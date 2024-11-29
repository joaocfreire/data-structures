#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "LinkedList.h"

typedef struct stack {
    Node* top;
    int count;
} Stack;

Stack* createStack();
void push(Stack* s, int x);
void pop(Stack* s);
int top(Stack* s);
bool stackEmpty(Stack* s);
void freeStack(Stack* s);
void printStack(Stack* s);

#endif //STACK_H