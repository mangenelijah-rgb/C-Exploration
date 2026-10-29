#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "basic_threads.h"
#include "clock.h"

void* producer(void *producerData) {
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
    pthread_exit(NULL);
}

void* consumer(void *consumerData) {
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
    pthread_exit(NULL);
}