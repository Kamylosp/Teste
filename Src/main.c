#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "miros.h"
#include "qassert.h"

#define n_produtores 2
#define n_consumidores 2

int contador = 0, tamanho_max = 10;

thread_mutex mutex;
sem emp, full;

uint8_t gera_delay(){
	return ((rand() % 100) + 1);
}

typedef struct {
    OSThread produ;
    uint32_t stackProd[40];
} prod;

typedef struct {
    OSThread consu;
    uint32_t stackCons[40];
} cons;

prod produs[n_produtores];
cons consum[n_consumidores];

uint32_t stack_blinky1[40];
OSThread blinky1;
void produzir() {
    while (1) {
        sem_wait((void*)&emp);
        OS_delay(gera_delay());
        mutex_lock((void*)&mutex);
        if(contador<10){
        contador++;
        }
        mutex_unlock((void*)&mutex);
        sem_post((void*)&full);
    }
}

uint32_t stack_blinky2[40];
OSThread blinky2;
void consumir() {
    while (1) {
        sem_wait((void*)&full);
        OS_delay(gera_delay());
        mutex_lock((void*)&mutex);
        if(contador>0){
        contador--;
        }
        mutex_unlock((void*)&mutex);
        sem_post((void*)&emp);
    }
}

uint32_t stack_idleThread[40];

int main()
{
	srand(time(NULL));
    mutex_init((void*)&mutex);
    sem_init((void*)&emp, tamanho_max);
    sem_init((void*)&full, 0);

    OS_init(stack_idleThread, sizeof(stack_idleThread));

    for (int i = 0; i < n_produtores; i++) {
        OSThread_start(&(produs[i].produ),
        			   (2*i+1),
                       &produzir,
                       produs[i].stackProd, sizeof(produs[i].stackProd));
    }

    for (int i = 0; i < n_consumidores; i++) {
        OSThread_start(&(consum[i].consu),
        			   (2*i+2),
                       &consumir,
                       consum[i].stackCons, sizeof(consum[i].stackCons));
    }

    /*sem_destroy(&emp);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);*/
    OS_run();
    //return 0;
}
