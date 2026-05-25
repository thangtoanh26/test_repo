// #
// #

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int MSSV = 23 // MSSV = 24521613

int sells, products;
sem_t sem;

void* sell(void* arg) {
    while (1) {
        if (sells > products) {
            break;
        }
        sem_wait(&sem);
        sells++;
        printf("Sells: %d\n", sells);
    }
    return NULL;
}

void produce() {
    while (1) {
        if (products > sells + MSSV) {
            break;
        }
        sem_wait(&sem);
        products++;
        printf("Products: %d\n", products);
    }
    return NULL;
}

int main() {
    pthread_t sell_thread, produce_thread;
    sem_init(&sem, 0, 1);
    pthread_create(&sell_thread, NULL, sell, NULL);
    pthread_create(&produce_thread, NULL, produce, NULL);
    sells = 0;
    products = 0;

    pthread_join(sell_thread, NULL);
    pthread_join(produce_thread, NULL); 

    sem_destroy(&sem);
    return 0;
}