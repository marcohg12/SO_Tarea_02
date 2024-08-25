// --------------------------------------------------------
// Este archivo contiene la implementación de la biblioteca
// de sincronización de hilos. Contiene la implementación
// de la barrera, semáforo y R/W lock
// --------------------------------------------------------

#include "sync_lib.h"
#include <pthread.h>
#include <stdlib.h>

// --------------------------------------------------------
// BARRERA
// --------------------------------------------------------

Barrier *create_barrier(int count) {
  Barrier *barr = malloc(sizeof(Barrier));
  barr->count = count;
  pthread_mutex_init(&(barr->mutex), NULL);
  pthread_cond_init(&(barr->cond), NULL);
  return barr;
}

void wait_barrier(Barrier *b) {
  pthread_mutex_lock(&(b->mutex));
  b->count--;
  if (b->count > 0) {
    pthread_cond_wait(&(b->cond), &(b->mutex));
  }
  pthread_cond_broadcast(&(b->cond));
  pthread_mutex_unlock(&(b->mutex));
}

void destroy_barrier(Barrier *b) {
  pthread_mutex_destroy(&(b->mutex));
  pthread_cond_destroy(&(b->cond));
  free(b);
}

// --------------------------------------------------------
// SEMÁFORO
// --------------------------------------------------------

Semaphore *create_semaphore(int counter) {
  Semaphore *sem = malloc(sizeof(Semaphore));
  sem->counter = counter;
  pthread_mutex_init(&(sem->mutex), NULL);
  pthread_cond_init(&(sem->cond), NULL);
  return sem;
}

void destroy_semaphore(Semaphore *sem) {
  pthread_mutex_destroy(&(sem->mutex));
  pthread_cond_destroy(&(sem->cond));
  free(sem);
}

void wait_semaphore(Semaphore *sem) {
  pthread_mutex_lock(&(sem->mutex));
  if (sem->counter <= 0) {
    pthread_cond_wait(&(sem->cond), &(sem->mutex));
  }
  sem->counter = sem->counter - 1;
  pthread_mutex_unlock(&(sem->mutex));
}

void signal_semaphore(Semaphore *sem) {
  pthread_mutex_lock(&(sem->mutex));
  sem->counter = sem->counter + 1;
  pthread_cond_signal(&(sem->cond));
  pthread_mutex_unlock(&(sem->mutex));
}

// --------------------------------------------------------
// R/W LOCK
// --------------------------------------------------------

ReadWriteLock *create_read_write_lock() {

  ReadWriteLock *rw_lock = malloc(sizeof(ReadWriteLock));

  pthread_mutex_init(&(rw_lock->mutex), NULL);
  pthread_cond_init(&(rw_lock->cond_readers), NULL);
  pthread_cond_init(&(rw_lock->cond_writers), NULL);
  rw_lock->active_readers = 0;
  rw_lock->active_writers = 0;
  rw_lock->pending_writers = 0;

  return rw_lock;
}

void destroy_read_write_lock(ReadWriteLock *rw_lock) {
  pthread_mutex_destroy(&(rw_lock->mutex));
  pthread_cond_destroy(&(rw_lock->cond_readers));
  pthread_cond_destroy(&(rw_lock->cond_writers));
  free(rw_lock);
}

void lock_read(ReadWriteLock *rw_lock) {
  pthread_mutex_lock(&(rw_lock->mutex));
  while (rw_lock->active_writers > 0 || rw_lock->pending_writers > 0) {
    pthread_cond_wait(&(rw_lock->cond_readers), &(rw_lock->mutex));
  }
  rw_lock->active_readers++;
  pthread_mutex_unlock(&(rw_lock->mutex));
}

void unlock_read(ReadWriteLock *rw_lock) {
  pthread_mutex_lock(&(rw_lock->mutex));
  rw_lock->active_readers--;
  if (rw_lock->active_readers == 0 && rw_lock->pending_writers > 0) {
    pthread_cond_signal(&(rw_lock->cond_writers));
  }
  pthread_mutex_unlock(&(rw_lock->mutex));
}

void lock_write(ReadWriteLock *rw_lock) {
  pthread_mutex_lock(&(rw_lock->mutex));
  rw_lock->pending_writers++;
  while (rw_lock->active_readers > 0 || rw_lock->active_writers > 0) {
    pthread_cond_wait(&(rw_lock->cond_writers), &(rw_lock->mutex));
  }
  rw_lock->pending_writers--;
  rw_lock->active_writers++;
  pthread_mutex_unlock(&(rw_lock->mutex));
}

void unlock_write(ReadWriteLock *rw_lock) {
  pthread_mutex_lock(&(rw_lock->mutex));
  rw_lock->active_writers--;
  if (rw_lock->pending_writers > 0) {
    pthread_cond_signal(&(rw_lock->cond_writers));
  } else {
    pthread_cond_broadcast(&(rw_lock->cond_readers));
  }
  pthread_mutex_unlock(&(rw_lock->mutex));
}