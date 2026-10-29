#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>

extern struct timespec start;

long long elapsed();

#endif