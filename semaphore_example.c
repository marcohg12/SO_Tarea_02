#include "sync_lib.h"
#include <pthread.h>
#include <stdio.h>
#define ITER 3

Semaphore *producer_sem;
Semaphore *consumer_sem;
char c;

void *produce(void *arg) {
  for (int i = 0; i < ITER; i++) {
    wait_semaphore(producer_sem);
    printf("Ingrese un caracter: ");
    scanf(" %c", &c);
    signal_semaphore(consumer_sem);
  }
  return NULL;
}

void *consume(void *arg) {
  for (int i = 0; i < ITER; i++) {
    wait_semaphore(consumer_sem);
    printf("El caracter consumido es: %c\n\n", c);
    signal_semaphore(producer_sem);
  }
  return NULL;
}

int main() {
  producer_sem = create_semaphore(1);
  consumer_sem = create_semaphore(0);

  pthread_t producer_t, consumer_t;
  pthread_create(&producer_t, NULL, (void *)produce, NULL);
  pthread_create(&consumer_t, NULL, (void *)consume, NULL);

  pthread_join(producer_t, NULL);
  pthread_join(consumer_t, NULL);

  destroy_semaphore(producer_sem);
  destroy_semaphore(consumer_sem);
  
  return 0;
}
