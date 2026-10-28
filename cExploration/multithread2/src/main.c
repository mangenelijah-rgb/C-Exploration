#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "basic_threads.h"

int main() {
    Queue q;
    initQueue(&q);

    ProducerData producerData1;
    producerData1.q = &q;
    producerData1.filename = "producer.txt";

    pthread_t producerId;
    if (pthread_create(&producerId, NULL, producer, &producerData1) != 0) {
        perror("Couldn\'t spin producer thread\n");
        return 1;
    }
    printf("Producer 1 ID: %lu\n", (unsigned long)producerId);

    if (pthread_join(producerId, NULL) != 0) {
        perror("Couldn\'t join producer thread\n");
        return 1;
    }
    printf("Producer 1 joined\n");

    printf("Queue state: ");
    for (int i = 0; i < q.size; i++) {
        printf("%d ", q.items[(i + q.front) % MAX_ITEMS]);
    }
    printf("\n");

    ConsumerData consumerData1;
    consumerData1.q = &q;
    consumerData1.filename = "consumer.txt";

    pthread_t consumerId;
    if (pthread_create(&consumerId, NULL, consumer, &consumerData1) != 0) {
        perror("Couldn\'t spin consumer thread\n");
        return 1;
    }
    printf("Consumer 1 ID: %lu\n", (unsigned long)consumerId);

    if (pthread_join(consumerId, NULL) != 0) {
        perror("Couldn\'t join consumer thread\n");
        return 1;
    }
    printf("Consumer 1 joined\n");

    printf("Queue state: ");
    for (int i = 0; i < q.size; i++) {
        printf("%d ", q.items[(i + q.front) % MAX_ITEMS]);
    }
    printf("\n");

    return 0;
}