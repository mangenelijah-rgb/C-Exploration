#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "queue.h"
#include "basic_threads.h"
#include "clock.h"

struct timespec start;

int main() {
    clock_gettime(CLOCK_MONOTONIC, &start);
    Queue q;
    initQueue(&q);
    ThreadList list;
    threadList_init(&list);

    ProducerData producerData1;
    producerData1.q = &q;
    producerData1.filename = "producer.txt";
    producerData1.count = 1000;
    
    ConsumerData consumerData1;
    consumerData1.q = &q;
    consumerData1.filename = "consumer.txt";
    consumerData1.count = 1000;

    thread_init(&list, producer, &producerData1);
    thread_init(&list, consumer, &consumerData1);

    // pthread_t producerId;
    // if (pthread_create(&producerId, NULL, producer, &producerData1) != 0) {
    //     perror("Couldn\'t spin producer thread\n");
    //     return 1;
    // }
    // printf("Producer 1 ID: %lu\n", (unsigned long)producerId);
    
    // pthread_t consumerId;
    // if (pthread_create(&consumerId, NULL, consumer, &consumerData1) != 0) {
    //     perror("Couldn\'t spin consumer thread\n");
    //     return 1;
    // }
    // printf("Consumer 1 ID: %lu\n", (unsigned long)consumerId);

    
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_mutex_lock(&list.lock);
        if ((list.used_thread_flags & (1 << i))) {
            if (pthread_join(list.threads[i].id, NULL) != 0) {
                perror("Failed to join thread\n");
                return 1;
            }
            list.used_thread_flags &= ~(1 << i);
            printf("Joined thread %d at %llu ms\n", i, elapsed());
        }
        pthread_mutex_unlock(&list.lock);
    }

    printf("Queue state: ");
    for (int i = 0; i < q.size; i++) {
        printf("%d ", q.items[(i + q.front) % MAX_ITEMS]);
    }
    printf("\n");

    return 0;
}