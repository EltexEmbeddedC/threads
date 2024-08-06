#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_SHOPS 5
#define NUM_CUSTOMERS 3
#define INITIAL_STOCK 10000
#define CUSTOMER_DEMAND 100000
#define LOADER_SUPPLY 5000

#define COLOR_CYAN "\x1b[36m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"

/* Structure representing a shop with a stock of goods and a mutex lock for synchronization */
typedef struct {
    int stock;
    pthread_mutex_t lock;
} Shop;

/* Structure representing a customer with an ID and a demand for goods */
typedef struct {
    int id;
    int demand;
} Customer;

extern Shop shops[NUM_SHOPS];
extern pthread_t customers[NUM_CUSTOMERS];
extern pthread_t loader;
extern int customers_finished;
extern pthread_mutex_t finish_lock;

#endif // COMMON_H