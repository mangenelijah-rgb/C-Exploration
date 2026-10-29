#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "basic_threads.h"

void* producer(void *producerData) {
    ProducerData *data = (ProducerData *)producerData;
    FILE *file = fopen(data->filename, "w");
    Queue *q = data->q;
    if (file == NULL) {
        perror("Error opening file");
        pthread_exit(NULL);
    }

    int val;
    int i;
    int j = 60;
    srand(0);

    while (j--) {
        fprintf(file, "Number of items in queue: %d\n\n", q->size);
        fprintf(file, "============\n");

        i = (rand() % 5) + 1;
        while (i--) {
            val = (rand() % 500) + 101;
            if (!enqueue(q, &val)) {
                fprintf(file, "---->Queue full\n");
                break;
            }
            fprintf(file, "Enqueued %d\n", val);
        }
        fprintf(file, "============\n\n");
        fflush(file);
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
    int i;
    int j = 60;
    srand(0);

    while (j--) {
        fprintf(file, "Number of items in queue: %d\n\n", q->size);
        fprintf(file, "============\n");

        i = (rand() % 5) + 1;
        while (i--) {
            if (!dequeue(q, &val)) {
                fprintf(file, "---->Queue full\n");
                break;
            }
            fprintf(file, "Dequeued %d\n", val);
        }
        fprintf(file, "============\n\n");
        fflush(file);
    }
    fclose(file);
    pthread_exit(NULL);
}