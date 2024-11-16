#include "headers/Queue.h"

Queue* createQueue() {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->first = NULL;
    q->last = NULL;
    q->count = 0;
    return q;
}

void enqueue(Queue* q, int x) {
    QueueNode* newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->data = x;
    newNode->next = NULL;
    if (queueEmpty(q)) q->first = newNode;
    else q->last->next = newNode;
    q->last = newNode;
    q->count++;
}

void dequeue(Queue* q, int* x) {
    if (!queueEmpty(q)) {
        *x = q->first->data;
        QueueNode* aux = q->first;
        q->first = q->first->next;
        free(aux);
        if (q->first == NULL) q->last = NULL;
        q->count--;
    }
    else *x = 0;
}

bool queueEmpty(Queue* q) {
    if (q == NULL || (q->first == NULL && q->last == NULL)) return true;
    return false;
}

void freeQueue(Queue* q) {
    if (!queueEmpty(q)) {
        int x;
        dequeue(q, &x);
        freeQueue(q);
    }
}

void printQueue(Queue* q) {
    if (!queueEmpty(q)) {
        printf("Quantidade de elementos na fila: %d\n\n", q->count);
        QueueNode* aux = q->first;
        while(aux) {
            printf("%d", aux->data);
            if (aux->next != NULL) printf(" -> ");
            aux = aux->next;
        }
    }
    else printf("Fila vazia");
}