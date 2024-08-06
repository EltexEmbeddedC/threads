#include "../include/common.h"
#include "../include/loader.h"

/* Thread function for the loader. The loader periodically adds goods to random shops */

void* loader_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&finish_lock);
        if (customers_finished == NUM_CUSTOMERS) {
            pthread_mutex_unlock(&finish_lock);
            break;
        }
        pthread_mutex_unlock(&finish_lock);

        int shop_index;
        int found_shop = 0;

        while (!found_shop) {
            shop_index = rand() % NUM_SHOPS;
            if (pthread_mutex_trylock(&shops[shop_index].lock) == 0) {
                found_shop = 1;
            }
        }
        
        printf(COLOR_YELLOW "Погрузчик пришел в магазин №%d, там было %d единиц товара, стало %d\n" COLOR_RESET,
                shop_index + 1, shops[shop_index].stock, shops[shop_index].stock + LOADER_SUPPLY);
        
        shops[shop_index].stock += LOADER_SUPPLY;
        pthread_mutex_unlock(&shops[shop_index].lock);
        
        sleep(1);
    }
    return NULL;
}