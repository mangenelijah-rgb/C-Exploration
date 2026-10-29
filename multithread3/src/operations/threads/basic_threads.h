#ifndef BASIC_THREADS_H
#define BASIC_THREADS_H

#include <stdio.h>
#include <pthread.h>
#include "queue.h"

typedef struct {
    Queue *q;
    const char *filename;
} ProducerData;

typedef struct {
    Queue *q;
    const char *filename;
} ConsumerData;

void* producer(void *producerData);
void* consumer(void *consumerData);

#endif