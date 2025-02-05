#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "../LinkedList/LinkedList.h"

typedef struct queue {
    Node* first;
    Node* last;
    int count;
} Queue;

Queue* create_queue();
void enqueue(Queue* queue, int data);
void dequeue(Queue* queue);
int front(Queue* queue);
bool queue_empty(Queue* queue);
void free_queue(Queue* queue);
void print_queue(Queue* queue);

#endif //QUEUE_H