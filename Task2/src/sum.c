#include "../include/sum.h"

int a = 0;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

/* Create N threads, then join them */

void create_threads() {
  pthread_t threads[N];
  int indexes[N], s;

  for (int i = 0; i < N; i++) {
    indexes[i] = i + 1;

    s = pthread_create(&threads[i], NULL, incr_sum, (void*)&indexes[i]);
    if (s != 0)
      perror("pthread_create");
  }

  for (int i = 0; i < N; i++) {
    s = pthread_join(threads[i], NULL);
    if (s != 0)
      perror("pthread_join");
  }

  printf("%d\n", a);
}

/* Increment the global variable INCR_COUNT times */

void* incr_sum(void* arg) {
  for (int i = 0; i < INCR_COUNT; i++) {
    pthread_mutex_lock(&m1);
    a++;
    pthread_mutex_unlock(&m1);
  }

  return NULL;
}
