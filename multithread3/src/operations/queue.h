#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <pthread.h>
#define MAX_ITEMS 20

typedef struct {
    int items[MAX_ITEMS];
    int front;
    int tail;
    int size;
    pthread_mutex_t lock;
} Queue;

void initQueue(Queue* q);
bool enqueue(Queue* q, int* value);
bool dequeue(Queue* q, int* value);

#endif