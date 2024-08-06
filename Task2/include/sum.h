#ifndef INDEXES_H
#define INDEXES_H

#include <stdio.h>
#include <pthread.h>

#define N 5
#define INCR_COUNT 10000000

extern int a;
extern pthread_mutex_t m1;

void create_threads();
void* incr_sum(void* arg);

#endif // INDEXES_H