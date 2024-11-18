#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "LinkedList.h"

typedef struct queue {
    Node* first;
    Node* last;
    int count;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, int x);
void dequeue(Queue* q, int* x);
bool queueEmpty(Queue* q);
void freeQueue(Queue* q);
void printQueue(Queue* q);

#endif //QUEUE_H