#include "../include/common.h"
#include "../include/customer.h"
#include "../include/loader.h"
#include "../include/shops.h"

Shop shops[NUM_SHOPS];
pthread_t customers[NUM_CUSTOMERS];
pthread_t loader;
int customers_finished = 0;
pthread_mutex_t finish_lock = PTHREAD_MUTEX_INITIALIZER;

/* Generates a random offset within the range of -N to +N */
int random_offset(int N) {
    return (rand() % (2 * N + 1)) - N;
}

/* Run function to initialize the shops, create customer and loader threads, and wait for their completion. */
void run() {
    srand(time(NULL));
    
    for (int i = 0; i < NUM_SHOPS; i++) {
        shops[i].stock = INITIAL_STOCK + random_offset(1000);
        pthread_mutex_init(&shops[i].lock, NULL);
    }
    
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        Customer* customer = malloc(sizeof(Customer));
        customer->id = i + 1;
        customer->demand = CUSTOMER_DEMAND + random_offset(10000);
        pthread_create(&customers[i], NULL, customer_thread, customer);
    }
    
    pthread_create(&loader, NULL, loader_thread, NULL);
    
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }
    pthread_join(loader, NULL);
    
    for (int i = 0; i < NUM_SHOPS; i++) {
        pthread_mutex_destroy(&shops[i].lock);
    }
    pthread_mutex_destroy(&finish_lock);
}
