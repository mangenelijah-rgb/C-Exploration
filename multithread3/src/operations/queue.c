#include <stdio.h>
#include "queue.h"
#include <stdbool.h>
#include <pthread.h>

void initQueue(Queue* q) {
    q->front = 0;
    q->tail = -1;
    q->size = 0;
    pthread_mutex_init(&q->lock, NULL);
}

bool enqueue(Queue* q, int value) {
    pthread_mutex_lock(&q->lock);
    if (q->size == MAX_ITEMS) {
        pthread_mutex_unlock(&q->lock);
        return false;
    }
    q->tail = (q->tail + 1) % MAX_ITEMS;
    q->items[q->tail] = value;
    q->size++;
    pthread_mutex_unlock(&q->lock);
    return true;
}

bool dequeue(Queue* q, int* value) {
    pthread_mutex_lock(&q->lock);
    if (q->size == 0) {
        pthread_mutex_unlock(&q->lock);
        return false;
    }
    *value = q->items[q->front];
    q->items[q->front] = 0;
    q->front = (q->front + 1) % MAX_ITEMS;
    q->size--;
    pthread_mutex_unlock(&q->lock);
    return true;
}