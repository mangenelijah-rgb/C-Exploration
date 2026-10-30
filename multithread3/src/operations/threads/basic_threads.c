#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include "basic_threads.h"
#include "clock.h"

void threadList_init(ThreadList *list) {
    for (int i = 0; i < MAX_THREADS; i++) {
        list->threads[i].flags = 0;
    }
    list->used_thread_flags = 0;
    pthread_mutex_init(&list->lock, NULL);
}

int findAvailableThread(ThreadList *list) {
    for (int i = 0; i < MAX_THREADS; i++) {
        if ((list->used_thread_flags & (1 << i)) == 0) {
            return i;
        }
    }
    return -1;
}

void* threadWrapper(void *arguments) {
    ThreadTask *task = (ThreadTask *)arguments;

    if (task->function != NULL) {
        task->function(task->arguments);
    }

    task->list->threads[task->threadIndex].flags |= (1 << 0);
    free(task);
    pthread_exit(NULL);
}

void thread_init(ThreadList *list, void (*func)(void *), void *data) {
    
    pthread_t thread_id;

    ThreadTask *task = malloc(sizeof(ThreadTask));
    if (task == NULL) {
        perror("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    task->function = func;
    task->arguments = data;
    task->list = list;
    pthread_mutex_lock(&list->lock);
    task->threadIndex = findAvailableThread(list);
    if (task->threadIndex == -1) {
        perror("Could not find available thread\n");
        pthread_mutex_unlock(&list->lock);
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread_id, NULL, threadWrapper, task) != 0) {
        perror("Failed to create thread");
        pthread_mutex_unlock(&list->lock);
        free(task);
        exit(EXIT_FAILURE);
    }
    list->threads[task->threadIndex].id = thread_id;
    list->used_thread_flags |= (1 << task->threadIndex);
    pthread_mutex_unlock(&list->lock);
}

void producer(void *producerData) {
    ProducerData *data = (ProducerData *)producerData;
    FILE *file = fopen(data->filename, "w");
    Queue *q = data->q;
    if (file == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }

    srand(0);
    unsigned int i = 0;
    while (i < data->count) {
        if (!enqueue(q, i + 1)) {
            fprintf(file, "Queue full at %lld ms\n", elapsed());
            usleep(1000 * (rand() % 20)); //Sleep for a random amount from 0 to 20 milliseconds
            continue;
        }
        fprintf(file, "Enqueued %u at %lld ms\n", i++, elapsed());
        fflush(file);
        usleep(1000 * (rand() % 20)); //Sleep for a random amount from 0 to 20 milliseconds
    }
    fclose(file);
    //pthread_exit(NULL);
}

void consumer(void *consumerData) {
    ConsumerData *data = (ConsumerData *)consumerData;
    FILE *file = fopen(data->filename, "w");
    Queue *q = data->q;
    if (file == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }

    int val;
    srand(0);
    unsigned int i = 0;
    while (i < data->count) {
        if (!dequeue(q, &val)) {
            fprintf(file, "Queue empty at %lld ms\n", elapsed());
            usleep(1000 * (rand() % 20)); //Sleep for a random amount from 0 to 20 milliseconds
            continue;
        }
        fprintf(file, "Dequeued %u at %lld ms\n", val, elapsed());
        i++;
        fflush(file);
        usleep(1000 * (rand() % 20)); //Sleep for a random amount from 0 to 20 milliseconds
    }
    fclose(file);
    //pthread_exit(NULL);
}