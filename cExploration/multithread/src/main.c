#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

int main() {
    Queue q;
    initQueue(&q);

    int val = 0;
    int i = 0;
    int seed;
    scanf("%d", &seed);
    srand(seed);
    int j = 60;

    while (j--) {
        printf("Number of items in queue: %d\n\n", q.size);
        printf("============\n");
        i = (rand() % 5) + 1;
        while (i--) {
            val = (rand() % 500) + 101;
            if (!enqueue(&q, &val)) {
                printf("---->Queue full\n");
                break;
            }
            printf("Enqueued %d\n", val);
        }
        printf("\n");
        i = (rand() % 20) + 1;
        while (i--) {
            if (!dequeue(&q, &val)) {
                printf("---->Queue empty\n");
                break;
            }
            printf("Dequeued %d\n", val);
        }
        printf("============\n\n");
    }


    return 0;
}