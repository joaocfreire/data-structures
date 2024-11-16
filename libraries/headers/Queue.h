#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queueNode {
    int data;
    struct queueNode* next;
} QueueNode;

typedef struct queue {
    QueueNode* first;
    QueueNode* last;
    int count;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, int x);
void dequeue(Queue* q, int* x);
bool queueEmpty(Queue* q);
void freeQueue(Queue* q);
void printQueue(Queue* q);

#endif //QUEUE_H