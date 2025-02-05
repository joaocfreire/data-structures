#include "Stack.h"

Stack* create_stack() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

void push(Stack* stack, int data) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = stack->top;
    stack->top = new;
    stack->count++;
}

void pop(Stack* stack) {
    if (!stack_empty(stack)) {
        Node* aux = stack->top;
        stack->top = stack->top->next;
        stack->count--;
        free(aux);
    }
}

int top(Stack* stack) {
    if (!stack_empty(stack))
        return stack->top->data;
    return -1;
}

bool stack_empty(Stack* stack) {
    if (stack == NULL || stack->top == NULL)
        return true;
    return false;
}

void free_stack(Stack* stack) {
    while (!stack_empty(stack)) {
        Node *aux = stack->top;
        stack->top = stack->top->next;
        free(aux);
    }
    free(stack);
}

void print_stack(Stack* stack) {
    if (!stack_empty(stack)) {
        printf("Quantidade de elementos na pilha: %d\n", stack->count);
        Node* aux = stack->top;
        while (aux) {
            printf("%d", aux->data);
            if (aux->next)
                printf(" -> ");
            aux = aux->next;
        }
    }
    else
        printf("Pilha vazia");
}