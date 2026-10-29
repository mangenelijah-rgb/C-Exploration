#ifndef BASIC_THREADS_H
#define BASIC_THREADS_H

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include "queue.h"

#define MAX_THREADS 4

typedef struct {
    pthread_t id;
    uint8_t flags;
} ThreadStatus;

typedef struct {
    ThreadStatus threads[MAX_THREADS];
    uint8_t used_thread_flags;
    pthread_mutex_t lock;
} ThreadList;

typedef struct {
    void (*function)(void *);
    void *arguments;
    ThreadList *list;
    int threadIndex;
} ThreadTask;

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

void threadList_init(ThreadList *list);
int findAvailableThread(ThreadList *list);

void* threadWrapper(void *arguments);
void thread_init(ThreadList *list, void (*func)(void *), void *data);

void producer(void *producerData);
void consumer(void *consumerData);

#endif