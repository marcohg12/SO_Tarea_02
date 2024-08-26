#include <pthread.h>
#include <stdio.h>

int money_in_account = 10000;
pthread_mutex_t  mutex;

void *withdraw(void *arg) {

  int amount = *(int *)arg;

  pthread_mutex_lock(&mutex);

  if (money_in_account - amount >= 0) {
    if (amount == 10000) {
      sleep(1);
    }
    money_in_account -= amount;
  }

  pthread_mutex_unlock(&mutex);

  return NULL;
}

void mutex_example() {

  pthread_t thread1, thread2;
  int amount1 = 10000, amount2 = 9000;

  pthread_mutex_init(&mutex, NULL);
  pthread_create(&thread1, NULL, withdraw, &amount1);
  pthread_create(&thread2, NULL, withdraw, &amount2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Dinero en la cuenta: %d\n", money_in_account);

  pthread_mutex_destroy(&mutex);
}