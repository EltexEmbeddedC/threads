#ifndef INDEXES_H
#define INDEXES_H

#include <stdio.h>
#include <pthread.h>

#define N 5

void create_threads();
void* print_index(void* arg);

#endif // INDEXES_H