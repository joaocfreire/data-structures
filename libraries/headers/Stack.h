#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "LinkedList.h"

typedef struct stack {
    Node* top;
    int count;
} Stack;

Stack* create_stack();
void push(Stack* stack, int data);
void pop(Stack* stack);
int top(Stack* stack);
bool stack_empty(Stack* stack);
void free_stack(Stack* stack);
void print_stack(Stack* stack);

#endif //STACK_H