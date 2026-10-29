#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#define MAX_ITEMS 20

typedef struct {
    int items[MAX_ITEMS];
    int front;
    int tail;
    int size;
} Queue;

void initQueue(Queue* q);
bool enqueue(Queue* q, int* value);
bool dequeue(Queue* q, int* value);

#endif