#ifndef BASIC_THREADS_H
#define BASIC_THREADS_H

#include <stdio.h>
#include <pthread.h>
#include "queue.h"

typedef struct {
    Queue *q;
    const char *filename;
    unsigned int count;
} ProducerData;

typedef struct {
    Queue *q;
    const char *filename;
    unsigned int count;
} ConsumerData;

void* producer(void *producerData);
void* consumer(void *consumerData);

#endif