#include <stdio.h>
#include "queue.h"
#include <stdbool.h>

void initQueue(Queue* q) {
    q->front = 0;
    q->tail = -1;
    q->size = 0;
}

bool enqueue(Queue* q, int* value) {
    if (q->size == MAX_ITEMS) return false;
    q->tail = (q->tail + 1) % MAX_ITEMS;
    q->items[q->tail] = *value;
    q->size++;
    return true;
}

bool dequeue(Queue* q, int* value) {
    if (q->size == 0) return false;
    *value = q->items[q->front];
    q->items[q->front] = 0;
    q->front = (q->front + 1) % MAX_ITEMS;
    q->size--;
    return true;
}