#include "../include/common.h"
#include "../include/customer.h"

/* Thread function for a customer. Each customer tries to acquire goods from random shops until their demand is met */

void* customer_thread(void* arg) {
    Customer* customer = (Customer*) arg;
    while (customer->demand > 0) {
        int shop_index;
        int found_shop = 0;

        while (!found_shop) {
            shop_index = rand() % NUM_SHOPS;
            if (pthread_mutex_trylock(&shops[shop_index].lock) == 0) {
                found_shop = 1;
            }
        }
        
        int taken = shops[shop_index].stock < customer->demand ? shops[shop_index].stock : customer->demand;
        printf(COLOR_CYAN "Покупатель №%d с потребностью %d пришел в магазин №%d, в нем было %d единиц товара, забрал %d, осталось %d\n" COLOR_RESET,
                customer->id, customer->demand, shop_index + 1, shops[shop_index].stock, taken, shops[shop_index].stock - taken);
        
        shops[shop_index].stock -= taken;
        customer->demand -= taken;
        
        pthread_mutex_unlock(&shops[shop_index].lock);
        
        sleep(2);
    }
    pthread_mutex_lock(&finish_lock);
    customers_finished++;
    pthread_mutex_unlock(&finish_lock);
    return NULL;
}
