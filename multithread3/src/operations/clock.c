#include <time.h>
#include "clock.h"

long long elapsed() {
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC, &current);

    long long seconds = current.tv_sec - start.tv_sec;
    long long nanoseconds = current.tv_nsec - start.tv_nsec;

    return (seconds * 1000) + (nanoseconds / 1000000);
}