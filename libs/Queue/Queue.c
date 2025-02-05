#include "Queue.h"

Queue* create_queue() {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last = NULL;
    queue->count = 0;
    return queue;
}

void enqueue(Queue* queue, int data) {
    Node* new = (Node*) malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    if (queue_empty(queue))
        queue->first = new;
    else
        queue->last->next = new;
    queue->last = new;
    queue->count++;
}

void dequeue(Queue* queue) {
    if (!queue_empty(queue)) {
        Node* aux = queue->first;
        queue->first = queue->first->next;
        free(aux);
        if (queue->first == NULL)
            queue->last = NULL;
        queue->count--;
    }
}

int front(Queue* queue) {
    if (!queue_empty(queue))
        return queue->first->data;
    return -1;
}

bool queue_empty(Queue* queue) {
    if (queue == NULL || (queue->first == NULL && queue->last == NULL))
        return true;
    return false;
}

void aux_free_queue(Node* node) {
    if (node != NULL) {
        aux_free_queue(node->next);
        free(node);
    }
}

void free_queue(Queue* queue) {
    if (queue != NULL) {
        aux_free_queue(queue->first);
        free(queue);
    }
}

void print_queue(Queue* queue) {
    if (!queue_empty(queue)) {
        printf("Quantidade de elementos na fila: %d\n", queue->count);
        Node* aux = queue->first;
        while (aux) {
            printf("%d", aux->data);
            if (aux->next != NULL)
                printf(" -> ");
            aux = aux->next;
        }
    }
    else
        printf("Fila vazia");
}