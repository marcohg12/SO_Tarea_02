#include "sync_lib.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_RACERS 5

Barrier *barrier;

void *racer(void *arg) {
  int racer_id = *(int *)arg;

  // Simulate different start times
  sleep(rand() % 3 + 1);

  printf("Competidor %d ha iniciado la carrera!\n", racer_id);

  // Simulate the race with random arrival times
  sleep(rand() % 5 + 1);

  // Wait for all racers to finish
  wait_barrier(barrier);

  // Indicate that the racer has finished the race
  printf("Competidor %d ha llegado a la meta!\n", racer_id);

  return NULL;
}

int main() {
  pthread_t threads[NUM_RACERS];
  int racer_ids[NUM_RACERS];

  // Initialize the barrier for NUM_RACERS racers
  barrier = create_barrier(NUM_RACERS);

  // Create threads representing racers
  for (int i = 0; i < NUM_RACERS; i++) {
    racer_ids[i] = i + 1;
    pthread_create(&threads[i], NULL, (void *)racer, (void *)&racer_ids[i]);
  }

  for (int i = 0; i < NUM_RACERS; i++) {
    pthread_join(threads[i], NULL);
  }

  destroy_barrier(barrier);

  printf("La carrera terminó. Todos los competidores cruzaron la meta!\n");

  return 0;
}
